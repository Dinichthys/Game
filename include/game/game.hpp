#pragma once

#include <vector>
#include <unistd.h>
#include <set>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "client/object.hpp"
#include "client/client.hpp"
#include "client/wall.hpp"
#include "client/free.hpp"
#include "client/box.hpp"
#include "client/bomb.hpp"
#include "client/fire.hpp"

#include "server/server.hpp"

#include "map.hpp"

namespace game {

static const size_t kAnimationFramesNum = 10;
static const size_t kAnimationTimePerFrameUSec = 30000;
static const size_t kTimePerFrameUSec = 30000;

static const std::string kGamePrefix = "game";

enum MethodType {
    kAddClient,
    kImage,
    kAddTopLevelImage,
    kEraseTopLevelImage,
    kMove,
    kGetType,
    kGetBoxesNum,
    kGetBoxPos,
    kAddBomb
};

static const std::string kAddClientStr          = "AddClient";
static const std::string kImageStr              = "Image";
static const std::string kAddTopLevelImageStr   = "AddTopLevelImage";
static const std::string kEraseTopLevelImageStr = "EraseTopLevelImage";
static const std::string kMoveStr               = "Move";
static const std::string kGetTypeStr            = "GetType";
static const std::string kGetBoxesNumStr        = "GetBoxesNum";
static const std::string kGetBoxPosStr          = "GetBoxPos";
static const std::string kAddBombStr            = "AddBomb";

static const std::map<std::string, MethodType> kStrToMethod {
    {kAddClientStr, kAddClient},
    {kImageStr, kImage},
    {kAddTopLevelImageStr, kAddTopLevelImage},
    {kEraseTopLevelImageStr, kEraseTopLevelImage},
    {kMoveStr, kMove},
    {kGetTypeStr, kGetType},
    {kGetBoxesNumStr, kGetBoxesNum},
    {kGetBoxPosStr, kGetBoxPos},
    {kAddBombStr, kAddBomb},
};

class Game : public server::Plugin {
    private:
        std::map<size_t, client::Client *> clients_;
        std::vector<client::Box *> boxes_;
        std::vector<client::Bomb *> bombs_;

        std::set<image::Image *>top_level_;

        std::vector<std::vector<client::Object *>> map_;

    public:
        Game()
            :server::Plugin(), clients_(), boxes_(), bombs_(), top_level_() {
            for (size_t y = 0; y < map::kMapHeight; y++) {
                for (size_t x = 0; x < map::kMapWidth; x++) {
                    switch(map::kMap[x + y * map::kMapWidth]) {
                        case map::Type::kBomb : {
                            map_.push_back({new client::Bomb({x, y})});
                            bombs_.push_back(dynamic_cast<client::Bomb *>(map_.back().back()));
                            break;
                        };
                        case map::Type::kFire : {
                            map_.push_back({new client::Fire({x, y})});
                            break;
                        };
                        case map::Type::kBox : {
                            map_.push_back({new client::Box({x, y})});
                            boxes_.push_back(dynamic_cast<client::Box *>(map_.back().back()));
                            break;
                        };
                        case map::Type::kFree : {
                            map_.push_back({new client::Free({x, y})});
                            break;
                        };
                        case map::Type::kWall : {
                            map_.push_back({new client::Wall({x, y})});
                            break;
                        };
                        default :
                            break;
                    }
                    map_.back()[0]->SetGame(this);
                }
            }
        };

        ~Game() {
            for (auto &elems : map_) {
                for (auto elem : elems) {
                    delete elem;
                }
            }
        };

        virtual std::string GetPrefix() {
            return kGamePrefix;
        };

        virtual void SendMsg(std::string_view msg, size_t sender) {
            std::string method;
            std::istringstream str(msg.data());
            str >> method;

            MethodType type = kStrToMethod.at(method);
            switch (type) {
                case kAddClient :
                    AddClient(str, sender);
                    break;
                case kImage :
                    UpdateImage(str, sender);
                    break;
                case kAddTopLevelImage :
                    AddTopLevelImage(clients_[sender]->GetImage());
                    break;
                case kEraseTopLevelImage :
                    EraseTopLevelImage(clients_[sender]->GetImage());
                    break;
                case kMove :
                    Move(str, sender);
                    break;
                case kGetType :
                    GetType(str, sender);
                    break;
                case kGetBoxesNum :
                    GetBoxesNum(sender);
                    break;
                case kGetBoxPos :
                    GetBoxPos(str, sender);
                    break;
                case kAddBomb :
                    AddBomb(str);
                    break;
                default:
                    break;
            };
        };

        void AddClient(std::istringstream &str, size_t sender) {
            math::Vec2u pos;
            str >> pos.x_ >> pos.y_;

            client::Client *c = new client::Client(pos);
            c->SetID(sender);
            c->SetGame(this);
            map_[pos.x_ + pos.y_ * map::kMapWidth].push_back(c);
            clients_[sender] = c;
        };

        void UpdateImage(std::istringstream &str, size_t sender) {
            clients_[sender]->UpdateTexture(str);
        };

        void AddBox(client::Box *b) {
            b->SetGame(this);
            map_[b->GetX() + b->GetY() * map::kMapWidth].push_back(b);
            boxes_.push_back(b);
        };

        void AddBomb(std::istringstream &str) {
            math::Vec2u pos;
            str >> pos.x_ >> pos.y_;
            client::Bomb *b = new client::Bomb(pos);
            b->SetGame(this);
            map_[pos.x_ + pos.y_* map::kMapWidth].push_back(b);
            bombs_.push_back(b);
        };

        void AddTopLevelImage(image::Image *image) {
            top_level_.insert(image);
        };
        void EraseTopLevelImage(image::Image *image) {
            top_level_.erase(image);
        };

        void GetType(std::istringstream &str, size_t sender) {
            math::Vec2u pos;
            str >> pos.x_ >> pos.y_;
            std::ostringstream msg;
            msg << client::kReceiveStr << ' ' << map_[pos.x_ + pos.y_* map::kMapWidth].back()->GetType();
            server_->SendMsg(sender, msg.str(), kGamePrefix);
        };

        void GetBoxesNum(size_t sender) {
            server_->SendMsg(sender, client::kReceiveStr + " " + std::to_string(boxes_.size()), kGamePrefix);
        };

        void GetBoxPos(std::istringstream &str, size_t sender) {
            size_t idx;
            str >> idx;
            std::ostringstream msg;
            auto pos = boxes_[idx]->GetPos();
            msg << client::kReceiveStr << ' ' << pos.x_ << ' ' << pos.y_;
            server_->SendMsg(sender, msg.str(), kGamePrefix);
        };

        void Animate(sf::RenderWindow &window) {
            for (size_t i = 0; i < kAnimationFramesNum; i++) {
                for (auto &elems : map_) {
                    for (auto elem : elems) {
                        elem->Animate();
                    }
                }
                Draw(window);

                window.display();

                usleep(kAnimationTimePerFrameUSec);
            }
        };

        void Draw(sf::RenderWindow &window) {
            window.clear();
            DrawMap(window);
            DrawTopLevel(window);
        };

        void Action() {
            for (auto &elems : map_) {
                for (auto elem : elems) {
                    elem->Action();
                }
            }
        };

        std::vector<client::Box *> &GetBoxes() {
            return boxes_;
        };

        void GenerateBoxes(size_t number);

        void RemoveObj(client::Object *o) {
            math::Vec2u pos = o->GetPos();
            auto &slot = map_[pos.x_ + pos.y_ * map::kMapWidth];
            for (size_t i = 0; i < slot.size(); i++) {
                if (slot[i] == o) {
                    slot.erase(slot.begin() + i);
                    break;
                }
            }

            auto type = o->GetType();

            switch(type) {
                case game::map::Type::kBox : {
                    for (size_t i = 0; i < boxes_.size(); i++) {
                        if (boxes_[i] == o) {
                            boxes_.erase(boxes_.begin() + i);
                            break;
                        }
                    }
                    break;
                }
                case game::map::Type::kBomb : {
                    for (size_t i = 0; i < bombs_.size(); i++) {
                        if (bombs_[i] == o) {
                            bombs_.erase(bombs_.begin() + i);
                            break;
                        }
                    }
                    break;
                }
                case game::map::Type::kClient : {
                    for (const auto &[key, value] : clients_) {
                        if (value== o) {
                            clients_.erase(key);
                            break;
                        }
                    }
                    break;
                }
                default : {
                    break;
                }
            }

            delete o;
        };

        void Move(std::istringstream &str, size_t sender) {
            math::Vec2s shift;
            str >> shift.x_ >> shift.y_;
            client::Object *o = clients_[sender];
            math::Vec2u pos = o->GetPos();
            auto &slot = map_[pos.x_ + pos.y_ * map::kMapWidth];
            for (size_t i = 0; i < slot.size(); i++) {
                if (slot[i] == o) {
                    slot.erase(slot.begin() + i);
                    break;
                }
            }
            auto &new_slot = map_[pos.x_ + shift.x_ + (pos.y_ + shift.y_) * map::kMapWidth];
            new_slot.push_back(o);
            o->SetPos({pos.x_ + shift.x_, pos.y_ + shift.y_});
        };

        bool Boom(const math::Vec2u &pos) {
            if (pos.x_ >= map::kMapWidth || pos.y_ >= map::kMapHeight) {
                return false;
            }

            auto &elem = map_[pos.x_ + pos.y_ * map::kMapWidth];
            auto type = elem.back()->GetType();

            switch(type) {
                case game::map::Type::kBox : {
                    auto b = elem.back();
                    for (size_t i = 0; i < boxes_.size(); i++) {
                        if (boxes_[i] == b) {
                            boxes_.erase(boxes_.begin() + i);
                            break;
                        }
                    }
                    elem.erase(elem.end() - 1);
                    elem.push_back(new client::Fire(pos));
                    elem.back()->SetGame(this);
                    delete b;
                    return false;
                }
                case game::map::Type::kBomb : case game::map::Type::kClient : case game::map::Type::kWall : {
                    return false;
                }
                case game::map::Type::kFire : {
                    return true;
                }
                case game::map::Type::kFree : {
                    elem.push_back(new client::Fire(pos));
                    elem.back()->SetGame(this);
                    return true;
                }
            }

            return false;
        };

    private:
        void DrawMap(sf::RenderWindow &window) {
            for (auto &elems : map_) {
                for (auto &elem : elems) {
                    elem->Draw(window);
                }
            }
        };

        void DrawTopLevel(sf::RenderWindow &window) {
            for (auto &image : top_level_) {
                image->Draw(window);
            }
        };
};

static const size_t kElemSize = 50;

static const size_t kWindowWidth = kElemSize * map::kMapWidth;
static const size_t kWindowHeight = kElemSize * map::kMapHeight;

void RunGame();

};
