#include "account.h"

std::mutex mtx;

void Account::enter()
{
    while(true)
    {
        std::string username, password;
        std::cout << "Введите имя пользователя: ";
        std::cin >> username;
        std::cout << "Введите пароль: ";
        std::cin >> password;
        auto [success, id] = manager_request_.requestEnter(username, password);
        if (success)
        {
            username_ = username;
            password_ = password;
            id_ = id;
            std::cout << "Вход успешный! Ваш ID: " << id << std::endl;
            mainMenu();
        }
        else
        {
            std::cout << "Неверное имя пользователя или пароль. Попробуйте снова." << std::endl;
        }
    }
}

void Account::registration()
{
    while(true)
    {
        std::string username, password;
        std::cout << "Введите имя пользователя: ";
        std::cin >> username;
        std::cout << "Введите пароль: ";
        std::cin >> password;
        int id = manager_request_.requestRegister(username, password);
        if (id != -1)
        {
            username_ = username;
            password_ = password;
            id_ = id;
            std::cout << "Регистрация успешная! Ваш ID: " << id << std::endl;
            mainMenu();
        }
        else
        {
            std::cout << "Имя пользователя уже существует. Попробуйте снова." << std::endl;
        }
    }
}

void Account::mainMenu()
{
    std::thread listenServerThread(listenServer, 1);
    while(true)
    {
        std::cout << "Главное меню:" << std::endl;
        std::cout << "1. Открыть чат" << std::endl;
        std::cout << "2. Выйти" << std::endl;
        int choice = 0;
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                std::cout << "Вы выбрали открыть чат." << std::endl;
                chatMenu();
            }
            case 2:
            {
                std::cout << "Вы выбрали выход." << std::endl;
                return; // Выход из главного меню
            }
            default:
            {
                std::cout << "Неверный выбор. Пожалуйста, выберите 1 или 2." << std::endl;
                break;
            }
        }
    }
}

void Account::chatMenu()
{
    mtx.lock();
    for(const auto& message : messages_)
    {
        std::cout << message << std::endl;
    }
    mtx.unlock();
    std::string message = "a";
    std::cout << "Введите 'выход' для выхода из чата." << std::endl;
    while(message != "выход")
    {
        std::cout << "Введите сообщение: ";
        std::cin.ignore(); // Очистка буфера ввода
        std::getline(std::cin, message);
        manager_request_.requestSendMessage(id_, message);
        mtx.lock();
        messages_.push_back(message);
        mtx.unlock();
    }
}

void Account::listenServer()
{
    while(true)
    {
        // Здесь можно добавить код для получения сообщений от сервера
        // и добавления их в messages_
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Имитация ожидания сообщений от сервера
        mtx.lock();
        messages_.push_back("Новое сообщение от сервера!"); // Имитация получения нового сообщения от сервера
        mtx.unlock();
    }
}