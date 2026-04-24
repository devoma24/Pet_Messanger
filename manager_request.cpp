#include "manager_request.h"

std::pair<bool, int> ManagerRequest::requestEnter(std::string username, std::string password)
{
    std::cout << "Вы выбрали вход в учетную запись." << std::endl;
    return kernel_.validateUserData(username, password);
}

int ManagerRequest::requestRegister(std::string username, std::string password)
{
    std::cout << "Вы выбрали регистрацию." << std::endl;
    return kernel_.saveUserData(username, password);
}

void ManagerRequest::requestSendMessage(int id, std::string& message)
{
    std::cout << "Вы выбрали отправку сообщения." << std::endl;
    kernel_.saveMessage(id, message);
}