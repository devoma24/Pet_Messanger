#pragma once

#include <iostream>
#include <string>
#include <map>
#include "kernel.h"

class ManagerRequest
{
    private:
    Kernel kernel_;
    public:
    std::pair<bool, int> requestEnter(std::string username, std::string password);
    int requestRegister(std::string username, std::string password);
    void requestSendMessage(int id, std::string& message);
};