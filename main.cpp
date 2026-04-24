#include <iostream>
#include "account.h"

void startMenu()
{
    Account account;
    while(true)
    {
        std::cout << "Добро пожаловать!" << std::endl;
        std::cout << "1. Войти в учетную запись" << std::endl;
        std::cout << "2. Зарегистрироваться" << std::endl;
        std::cout << "3. Выйти" << std::endl;
        int choice = 0;
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                std::cout << "Вы выбрали вход в учетную запись." << std::endl;
                account.enter();
                break;
            }
            case 2:
            {
                std::cout << "Вы выбрали регистрацию." << std::endl;
                account.registration();
                break;
            }
            case 3:
            {
                std::cout << "Вы выбрали выход." << std::endl;
                // Здесь можно добавить код для выхода
                return;
            }
            default:
            {
                std::cout << "Неверный выбор. Пожалуйста, выберите 1, 2 или 3." << std::endl;
                break;
            }
        }
    }
}


int main()
{
    startMenu();
    return 0;
}