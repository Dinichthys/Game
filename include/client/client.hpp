#pragma once

#include <sstream>

#include "object.hpp"

#include "image/image.hpp"

#include "server/server.hpp"

namespace client {

static const std::string kClientImageFileName = "data/Guy.png";

enum Direction {
    kInvalid,
    kLeft,
    kRight,
    kUp,
    kDown
};

enum MethodType {
    kDraw,
    kAction,
    kAnimate,
    kSetPos,
    kReceive
};

static const std::string kDrawStr    = "Draw";
static const std::string kActionStr  = "Action";
static const std::string kAnimateStr = "Animate";
static const std::string kSetPosStr  = "SetPos";
static const std::string kReceiveStr = "Receive";

static const std::map<std::string, MethodType> kStrToMethod {
    {kDrawStr, kDraw},
    {kActionStr, kAction},
    {kAnimateStr, kAnimate},
    {kSetPosStr, kSetPos},
    {kReceiveStr, kReceive},
};

class Client : public Object {
    private:
        size_t id_;

    public:
        Client(const math::Vec2u &pos)
            :Object(pos), id_(0) {
            image_.LoadImageFromFile(kClientImageFileName);
        };

        ~Client() = default;

        void SetID(size_t id) {
            id_ = id;
        };

        virtual void Draw(sf::RenderWindow &window) override;

        virtual void Action() override;

        virtual void Animate() override;

        virtual game::map::Type GetType() const {
            return game::map::Type::kClient;
        };

        virtual void SetPos(math::Vec2u new_pos) override;

    private:
        void Move();
};

class ServerClient : public Object, public server::Client {
    private:
        Direction direction_;
        bool analyzed_;
        size_t counter_frames_;

        std::string received_msg_;

    public:
        ServerClient(const math::Vec2u &pos)
            :Object(pos), server::Client(), direction_(Direction::kInvalid), analyzed_(false), counter_frames_(0) {};

        ~ServerClient() = default;

        virtual void SetServer(server::Server *server) override;

        virtual void SendMsg(std::string_view msg, std::string_view) override {
            std::string method;
            std::istringstream str(msg.data());
            str >> method;

            MethodType type = kStrToMethod.at(method);
            switch (type) {
                case kDraw :
                    Draw();
                    break;
                case kAction :
                    Action();
                    break;
                case kAnimate :
                    Animate();
                    break;
                case kSetPos :
                    SetPos(str);
                    break;
                case kReceive :
                    received_msg_ = {(std::istreambuf_iterator<char>(str)),
                                      std::istreambuf_iterator<char>()};
                    break;
                default:
                    break;
            }
        };

        virtual void Draw(sf::RenderWindow &) {};
        virtual void Draw();

        virtual void Action() override;

        virtual void Animate() override;

        virtual void SetPos(std::istringstream &str);

        virtual game::map::Type GetType() const override {
            return game::map::Type::kClient;
        };

    private:
        void Move();
};

};
