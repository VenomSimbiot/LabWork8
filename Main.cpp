#include <iostream>
#include "Task_1/include/Task_1.h"
#include "Task_2/include/Task_2.h"

int main(){
    std::cout << "Лабораторная работа №8 студента группы 453502 Филиповского Владислава Вадимовича\n";
    std::cout << "Вариант 5\n";
    std::string sc = "0";
    while(sc != "1"){
        std::cout << "Какое задание запустить?:\n1 - Телефонная книга\n2 - Расписание полетов\n";
        std::string k = "-1";
        while (k != "1" and k != "2")
        {
            std::cout << "Введите 1 или 2: ";
            std::cin >> k;
        }
        if (k == "1")
        {
            task_1();
        }
        else{
            task_2(false);
        }
        std::cout << "Введите 1 для выхода и что либо другое для перезапуска: "; std::cin >> sc;
    }
    
    return 0;
}