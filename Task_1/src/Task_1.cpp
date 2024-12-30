#include <iostream>
#include "../include/functions.h"
#include <fstream>


void task_1(){
    system(">> dialog.dat");
    std::cout << "Добро пожаловать в программу для создания книги записей телефонных разговоров\n";
    std::ifstream file("dialog.dat");
    std::string line;
    file >> line;
    file.close();
    int n;
    dialog *arr;
    int k = -1;
    if (line == ""){
        std::cout << "Каким образом вы хотите создать телефонную книгу?\n";
        std::cout << "1 - ввести N элементов\n2 - вводить пока в одном из элементов одна из колонок не будет равна нужному значению\n";
        while (k < 1 or k > 2)
        {
            k = vvod("Введите 1 или 2: ");
        }
        switch (k)
        {
        case 1:
            n = -1;
            while (n < 1)
            {
                n = vvod("Введите количество элементов (> 0): ");
            }
            arr = arrayN(n);
            break;
        case 2:
            arr = arrayWhile();
            break;
        }
        for (int i = 0; i < count; i++)
        {
            dialogToFile(arr[i]);
        }
        
    }
    else{
        arr = fileToArr();
    }
    n = 0;
    while (n != -1)
    { 
        std::cout << "=======================================\n";
        std::cout << "Что вы хотите сделать?\n";
        std::cout << "1 - Вывести всю телефонную книгу\n2 - Добавить новый элемент в книгу\n3 - Редактировать элементы с значением одной из колонок\n4 - Удалить элементы с значением одной из колонок\n5 - Найти элементы с значением одной из колонок\n6 - Сортировать по одному из полей\n7 - выход\n";
        k = 0;
        while (k < 1 or k > 7)
        {
            std::cout << "Введите число от 1 до 7\n";
            k = vvod("Ввод: ");
        }
        switch (k){
        case 1:
            vivod(arr, count);
            break;
        case 2:
            dopoln(arr, count);
            break;
        case 3:
            arr = findel(arr, count, 3);
            break;
        case 4:
            arr = findel(arr, count, 4);
            break;
        case 5:
            arr = findel(arr, count, 5);
            break;
        case 6:
            arr = bobblesort(arr, count);
            break;
        case 7:
            n = -1;
            break;
        }
    }
    
}