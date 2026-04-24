#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>

class Kernel
{
    public:
    int saveUserData(const std::string& username, const std::string& password);
    std::pair<bool, int> validateUserData(const std::string& username, const std::string& password);
    void saveMessage(int id, const std::string& message);
};