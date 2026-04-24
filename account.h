#pragma once

#include "manager_request.h"
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

class Account
{
    private:
    std::vector<std::string> messages_;
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
    void listenServer();
};