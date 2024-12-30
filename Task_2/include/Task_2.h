#include <iostream>
#include "airport.h"
#include <fstream>
#include <string>

class task_2{
private:
    int count = 0;
public: 
    task_2(bool istest){
        if (istest == false)
        {
            std::cout << "Добро пожаловать в программу для создания расписания вылета самолетов\n";
            system(">> airport.txt");
            std::ifstream file("airport.txt");
            std::string line;
            file >> line;
            file.close();
            int n, k;
            airport *arr;
            if (line == "")
            {
                std::cout << "Каким образом вы хотите создать расписание?\n";
                std::cout << "1 - ввести N элементов\n2 - вводить пока в одном из элементов одна из колонок не будет равна нужному значению\n";
                k = -1;
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
                
            }
            else{
                arr = fileToArr();
            }
            n = 0;
            while (n != -1)
            {
                sortByTime(arr);
                allArrToFile(arr);
                std::cout << "Что вы хотите сделать?\n";
                std::cout << "1 - Вывести все расписание полетов\n2 - Добавить новый элемент\n3 - Редактировать элементы с значением одной из колонок\n4 - Удалить элементы с значением одной из колонок\n5 - Найти элементы с значением одной из колонок\n6 - выход\n";
                k = -1;
                while (k < 1 or k > 6)
                {
                    k = vvod("Введите число от 1 до 6: ");
                }
                switch (k){
                case 1:
                    vivod(arr, count);
                    break;
                case 2:
                    arr = dopoln(arr, count);
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
                    n = -1;
                    file.close();
                    break;
                }
            }
            
        }
        
    }

    

    airport* findel(airport* arr, int N, int task){
        std::cout << "Введите поиск по какой переменной будет производиться: 1 - номер рейса, 2 - тип самолета, 3 - название города, 4 - час вылета, 5 - минута вылета: \n";
        int k = 0;
        while (k < 1 or k > 5)
        {
            k = vvod("Введите число от 1 до 5: ");
        }
        int b;
        std::string m;
        if (k == 1 or k == 4 or k == 5)
        {
            b = vvod("Введите значение которое мы ищем: ");
        }
        else{
            std::cout << "Введите значение которое мы ищем: "; std::cin >> m;
        }
        int ggg = 0;
        for (int i = 0; i < N; i++)
        {
            int t = 0;
            switch (k)
            {
            case 1:
                if (arr[i].raceNum == b)
                {
                    t++;
                }
                break;
            case 2:
                if (arr[i].PlaneType == m)
                {
                    t++;
                }
                break;
            case 3:
                if (arr[i].Place == m)
                {
                    t++;
                }
                break;
            case 4:
                if (arr[i].hour == b)
                {
                    t++;
                }
                break;
            case 5:
                if (arr[i].minute == b)
                {
                   t++;
                }
                break;
            }
            if (t != 0)
            {   
                ggg++;
                if (task == 3)
                {
                    std::cout << "Редактируем элемент под номером " << i + 1 << "\n";
                    arr[i] = zapairport();
                    allArrToFile(arr);
                }
                else if(task == 4){
                    airport* arr2 = newarr(arr, N, false, i);
                    delete[] arr;
                    arr = arr2;
                    allArrToFile(arr);
                }
                else if (task == 5)
                {
                    std::cout << i + 1 << " | ";
                    std::cout << arr[i].raceNum << " | " << arr[i].PlaneType << " | ";
                    std::cout << arr[i].Place << " | " << arr[i].hour << ":";
                    if (arr[i].minute < 10)
                    {
                        std::cout << "0";
                    }
                    std::cout <<arr[i].minute;
                    std::cout << std::endl;
                }
            }
            
        }
        if (ggg == 0)
        {
            std::cout << "Ни одного такого элемента не найдено";
        }
        return arr;
    }
    

    airport* arrayN(int n){
        std::fstream file("airport.txt");
        airport *arr = new airport[n];
        for (int i = 0; i < n; i++)
        {
            std::cout << "Ввод в базу " << i + 1 << " полета\n";
            arr[i] = zapairport();
            file << airportToString(arr[i]);
        }
        file.close();
        count = n;
        return arr;
    }
    
    std::string airportToString(airport a){
        std::string b = "";
        b += std::to_string(a.raceNum) + " " + a.PlaneType + " " + a.Place + " " + std::to_string(a.hour) + " " + std::to_string(a.minute) + "\n";
        return b;        
    }

    airport* fileToArr(){
        int n = 0;
        std::ifstream file("airport.txt");
        while (file)
        {
            std::string line;
            getline(file, line);
            n++;
        }
        n--;
        file.close();
        file.open("airport.txt");
        airport *arr = new airport[n];
        for (int i = 0; i < n; i++)
        {
            std::string line;
            getline(file, line);
            arr[i] = stringToAirport(line);
        }
        file.close();
        count = n;
        return arr;
    }

    airport stringToAirport(std::string a){
        airport b;
        int k = 0, q = 0;
        std::string c = "";
        for (int i = 0; i < a.length(); i++)
        {
            if (a[i] != ' ')
            {
                c += a[i];
                q++;
            }

            if(a[i] == ' ' or i == (a.length() - 1)){
                if (k == 0)
                {
                    b.raceNum = std::stoll(c);
                }
                else if(k == 1){
                    b.PlaneType = c;
                }
                else if (k == 2)
                {
                    b.Place = c;
                }
                else if (k == 3)
                {
                    b.hour = std::stoi(c);
                }
                else{
                    b.minute = std::stoi(c);
                }

                c = "";
                q = 0;
                k++;
            }
        }
        return b;
    }

    airport* sortByTime(airport*& arr){
        
        for (int j = 0; j < count; j++)
        {
            for (int i = 0; i < count - 1; i++)
            {
                if (arr[i].hour > arr[i + 1].hour)
                {
                    airport nice = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = nice;
                }
                else if(arr[i].hour == arr[i+1].hour){
                    if (arr[i].minute > arr[i + 1].minute)
                    {
                        airport nice = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = nice;
                    }
                }
            }
        }
        return arr;
    }

    airport* arrayWhile(){
        std::fstream file("airport.txt");
        int N = 0;
        int fi = 1;
        airport *arr = new airport[1];
        std::cout << "Введите поиск по какой переменной будет производиться: 1 - номер рейса, 2 - тип самолета, 3 - название города, 4 - час вылета, 5 - минута вылета: \n";
        int k = 0;
        while (k < 1 or k > 5)
        {
            k = vvod("Введите число от 1 до 5: ");
        }
        int b;
        std::string m;
        if (k == 1 or k == 4 or k == 5)
        {
            b = vvod("Введите значение которое мы ищем: ");
        }
        else{
            std::cout << "Введите значение которое мы ищем: "; std::cin >> m;
        }

        while (fi != 0)
        {
            arr[N] = zapairport();
            file << airportToString(arr[N]);
            switch (k)
            {
            case 1:
                if (arr[N].raceNum == b)
                {
                    fi = 0;
                }
                break;
            case 2:
                if (arr[N].PlaneType == m)
                {
                    fi = 0;
                }
                break;
            case 3:
                if (arr[N].Place == m)
                {
                    fi = 0;
                }
                break;
            case 4:
                if (arr[N].hour == b)
                {
                    fi = 0;
                }
                break;
            case 5:
                if (arr[N].minute == b)
                {
                   fi = 0;
                }
                break;
            }
            if (fi != 0)
            {
                N++;
                airport *arr2 = newarr(arr, N, true, 0);
                delete[] arr;
                arr = arr2;
                delete[] arr2;
            }
            
        }
        file.close();
        return arr;
        
    }

    void allArrToFile(airport* arr){
        std::ofstream file("airport.txt");
        for (int i = 0; i < count; i++)
        {
            file << airportToString(arr[i]);
        }
        file.close();
    }

    airport* newarr(airport* arr, int N, bool create, int del){
        airport *arr2;
        if (create)
        {
            arr2 = new airport[N + 1];
            for (int i = 0; i < N; i++)
            {
                arr2[i] = arr[i];
            }
            count++;
        }
        else{
            arr2 = new airport[N - 1];
            int k = 0;
            for (int i = 0; i < N; i++)
            {
                if (i != del)
                {
                    arr2[k] = arr[i];
                    k++;
                }
            }
            count--;
        }
        
        return arr2;
    }

    airport zapairport(){
        airport airport1;
        long long int racenum = -1;
        while (racenum < 1)
        {
            racenum = vvod("Введите номер рейса: ");
            if (racenum < 0)
            {
                std::cout << "Минимальный номер рейса - 1\n";
            }
        }
        airport1.raceNum = racenum;
        std::cout << "Введите тип самолета: ";std::cin >> airport1.PlaneType;
        std::cout << "Введите название города: ";std::cin >> airport1.Place;
        int hour = -1;
        while (hour < 0 or hour > 23)
        {
            hour = vvod("Введите час в который отправляется самолет: ");
            if (hour < 0)
            {
                std::cout << "Минимальный час - 0\n";
            }
            else if (hour > 23)
            {
                std::cout << "Максимальный час - 23\n";
            }
        }
        airport1.hour = hour;
        int minute = -1;
        while (minute < 0 or minute > 59)
        {
            minute = vvod("Введите минуту в которую отправляется самолет: ");
            if (minute < 0)
            {
                std::cout << "Минимальная минута - 0\n";
            }
            else if (minute > 59)
            {
                std::cout << "Максимальная минута - 59\n";
            }
        }
        airport1.minute = minute;
        return airport1;
    }

    airport* dopoln(airport *arr, int n){
        airport *arr2 = newarr(arr, n, true, 0);
        arr2[n] = zapairport();
        delete[] arr;
        arr = arr2;
        std::ofstream file("airport.txt", std::ios::app);
        file << airportToString(arr[n]);
        file.close();
        return arr;
    }



    long long int vvod(std::string text){ //O(n^2)
        std::cout << text;
        std::string newint;
        long long int num;
        while (true)
        {
            bool m = false, k = false;
            std::cin >> newint;
            if (newint[0] == '-')
            {
                m = true;
                newint[0] = '0';
            }
            
            for (int i = 0; i < newint.length(); i++)
            {
                
                if ((newint[i] < 48 or newint[i] > 57))
                {
                    k = true;
                }
                
            }
            
            if (k)
            {
                std::cout << "Вводите только числа\n" << text;
                continue;
            }
            else{
                num = std::stoll(newint);
                if(m){
                    num = -num;
                }
                break;
            }
        }
        return num;
    }

    

    void vivod(airport* arr, int n){
        std::cout << "Расписание полетов: \n";
        std::cout << "№ | Номер рейса | Тип самолета | Название города | Время вылета\n";
        for (int i = 0; i < n; i++)
        {
            std::cout << i + 1 << " | ";
            std::cout << arr[i].raceNum << " | " << arr[i].PlaneType << " | ";
            std::cout << arr[i].Place << " | " << arr[i].hour << ":";
            if (arr[i].minute < 10) 
            {
                std::cout << "0";
            }
            std::cout <<arr[i].minute;
            std::cout << std::endl;
        }
    }
};