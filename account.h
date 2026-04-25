#pragma once

#include "manager_request.h"
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

class Account
{
    private:
    struct Message
    {
        int id;
        std::vector<std::string> messages;
    };
    struct Contact
    {
        int id;
        std::string username;
    };
    private:
    std::vector<Message> messages_;
    std::vector<Contact> contacts_;
    ManagerRequest manager_request_;
    std::string username_;
    std::string password_;
    int id_;

    public:
    void enter();
    void registration();

    private:
    void mainMenu();
    void chatMenu();
    void openChat(int chatId);
    void createChat();
    void listenServer();
};