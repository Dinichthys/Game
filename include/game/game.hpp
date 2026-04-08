#pragma once

#include <vector>
#include <unistd.h>
#include <set>

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

#include "map.hpp"

namespace game {

static const size_t kAnimationFramesNum = 10;
static const size_t kAnimationTimePerFrameUSec = 30000;
static const size_t kTimePerFrameUSec = 30000;

class Game {
    private:
        std::vector<client::Client *> clients_;
        std::vector<client::Box *> boxes_;
        std::vector<client::Bomb *> bombs_;

        std::set<image::Image *>top_level_;

        std::vector<std::vector<client::Object *>> map_;

    public:
        Game()
            :clients_(), boxes_(), bombs_(), top_level_() {
            for (size_t y = 0; y < map::kMapHeight; y++) {
                for (size_t x = 0; x < map::kMapWidth; x++) {
                    switch(map::kMap[x + y * map::kMapWidth]) {
                        case map::Type::kBomb : {
                            map_.push_back({new client::Bomb({x, y})});
                            bombs_.push_back(dynamic_cast<client::Bomb *>(map_.back().back()));
                            break;
                        };
                        case map::Type::kClient : {
                            map_.push_back({new client::Client({x, y})});
                            clients_.push_back(dynamic_cast<client::Client *>(map_.back().back()));
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

        void AddClient(client::Client *c) {
            c->SetGame(this);
            map_[c->GetX() + c->GetY() * map::kMapWidth].push_back(c);
            clients_.push_back(c);
        };

        void AddBox(client::Box *b) {
            b->SetGame(this);
            map_[b->GetX() + b->GetY() * map::kMapWidth].push_back(b);
            boxes_.push_back(b);
        };

        void AddBomb(const math::Vec2u &pos) {
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

        map::Type GetType(const math::Vec2u &pos) const {
            return map_[pos.x_ + pos.y_* map::kMapWidth].back()->GetType();
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

        std::vector<client::Client *> &GetClients() {
            return clients_;
        };

        std::vector<client::Box *> &GetBoxes() {
            return boxes_;
        };

        void GenerateBoxes(size_t number);

        void GenerateClients();

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
                    for (size_t i = 0; i < clients_.size(); i++) {
                        if (clients_[i] == o) {
                            clients_.erase(clients_.begin() + i);
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

        void Move(client::Object *o, math::Vec2s &shift) {
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
