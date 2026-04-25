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
    std::cout << "Ваши чаты." << std::endl;
    for(int i = 0; i < messages_.size(); ++i)
    {
        std::cout << i + 1 << ". ";
        for(const auto& contact: contacts_)
        {
            if(contact.id == messages_[i].id)
            {
                std::cout << contact.username;
                break;
            }
        }
    }

    while(true)
    {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Открыть чат" << std::endl;
        std::cout << "2. Создать новый чат" << std::endl;
        std::cout << "3. Вернуться в главное меню" << std::endl;
        int choice = 0;
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                std::cout << "Введите номер чата, который хотите открыть: ";
                int chatChoice = 0;
                std::cin >> chatChoice;
                openChat(chatChoice - 1); // Открыть выбранный чат
                break;
            }
            case 2:
            {
                createChat(); // Создать новый чат
                break;
            }
            case 3:
            {
                return; // Вернуться в главное меню
            }
            default:
            {
                std::cout << "Неверный выбор. Пожалуйста, выберите 1, 2 или 3." << std::endl;
                break;
            }
        }

    }
}

void Account::openChat(int chatId)
{
    if(chatId < 0 || chatId >= messages_.size())
    {
        std::cout << "Неверный номер чата. Пожалуйста, выберите существующий чат." << std::endl;
        return;
    }
    std::cout << "Открыт чат с " << contacts_[chatId].username << "." << std::endl;
    for(const auto& message: messages_[chatId].messages)
    {
        std::cout << message << std::endl;
    }
    while(true)
    {
        std::cout << "Введите сообщение (или 'exit' для выхода из чата): ";
        std::string message;
        std::cin.ignore(); // Очистить буфер ввода
        std::getline(std::cin, message);
        if(message == "exit")
        {
            return; // Выход из чата
        }
        mtx.lock();
        messages_[chatId].messages.push_back(message); // Добавить сообщение в чат
        mtx.unlock();
    }
}

void Account::createChat()
{
    std::cout << "Существующие контакты:" << std::endl;
    for(const auto& contact: contacts_)
    {
        std::cout << contact.id << ". " << contact.username << std::endl;
    }
    while(true)
    {
        std::cout << "Введите ID контакта, с которым хотите создать чат: ";
        int contactId = 0;
        std::cin >> contactId;
        auto it = std::find_if(contacts_.begin(), contacts_.end(), [contactId](const Contact& contact) {
            return contact.id == contactId;
        });
        if(it == contacts_.end())
        {
            std::cout << "Неверный ID контакта. Пожалуйста, выберите существующий контакт." << std::endl;
            return;
        }

        messages_.push_back({contactId, {}}); // Создать новый чат с выбранным контактом
        std::cout << "Чат с " << it->username << " успешно создан!" << std::endl;
        return;
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
        //messages_.push_back("Новое сообщение от сервера!"); // Имитация получения нового сообщения от сервера
        mtx.unlock();
    }
}