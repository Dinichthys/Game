#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>

namespace server {

class Server;

class Client {
protected:
    Server *server_;
    size_t id_;

public:
    Client() {};

    virtual ~Client() {};

    virtual void SendMsg(std::string_view msg, std::string_view sender) = 0;

    virtual void SetServer(Server *server) {
        server_ = server;
    };

    void SetClientID(size_t id) {
        id_ = id;
    };

    Server *GetServer() {
        return server_;
    };
};

class Plugin {
protected:
    Server *server_;

public:
    Plugin()
        :server_(nullptr) {};

    virtual std::string GetPrefix() = 0;
    virtual void SendMsg(std::string_view msg, size_t sender) = 0;

    void SetServer(Server *server) {
        server_ = server;
    };

    Server *GetServer() {
        return server_;
    };
};

class Server {
private:
    std::map<std::string, Plugin *> plugins_;
    std::vector<Client *> clients_;

public:
    Server()
        :clients_() {};

    ~Server() {
        for (auto c : clients_) {
            delete c;
        }
    };

    void SendMsg(size_t receiver, std::string_view msg, std::string_view sender) {
        std::cerr << msg << std::endl;
        clients_[receiver]->SendMsg(msg, sender);
    };

    void SendMsg(std::string_view receiver, std::string_view msg, size_t sender) {
        std::cerr << msg << std::endl;
        plugins_[receiver.data()]->SendMsg(msg, sender);
    };

    size_t AddClient(Client *client) {
        clients_.push_back(client);
        client->SetClientID(clients_.size() - 1);
        client->SetServer(this);
        return clients_.size() - 1;
    };

    void AddPlugin(Plugin *plugin) {
        plugins_[plugin->GetPrefix()] = plugin;
        plugin->SetServer(this);
    };
};

};
