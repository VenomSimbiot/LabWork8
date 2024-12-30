#include <iostream>
#include "../include/dialog.h"
#include <fstream>

int count = 0;

dialog zapdialog();
date zapdate();
vtime zaptime();
bool chechDate(date d, date n);
bool chechTime(vtime d, vtime n);
dialog *newarr(dialog *arr, int N, bool create, int del);
void dialogToFile(dialog d);



long long int vvod(std::string text){
    std::cout << text;
    std::string newint;
    long long int num;
    while (true)
    {
        bool m = false, fi = false;
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
                fi = true;
            }
            
        }
        
        if (fi)
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

bool alphabetSort(std::string a, std::string b){
    int min = a.length() < b.length() ? a.length() : b.length();
    int g, h;

    for (int i = 0; i < min; i++)
    {
        g = a[i];
        h = b[i]; 
        if (g < h)
        {
            return true;
        }
        else if (g > h)
        {
            return false;
        }
    }
    return false;
}

bool dateSort(date a, date b){
    if (a.year < b.year)
    {
        return true;
    }
    else if(a.year == b.year and a.mounth < b.mounth){
        return true;
    }
    else if(a.year == b.year and a.mounth == b.mounth and a.day < b.day){
        return true;
    }
    return false;
}

dialog* arrayWhile(){
    int N = 0;
    int fi = 1;
    dialog *arr = new dialog[1];
    std::cout << "Введите поиск по какой переменной будет производиться: 1 - дата, 2 - код города, 3 - название города, 4 - время разговора, 5 - тариф, 6 - номер телефона: \n";
    int k = 0;
    while (k < 1 or k > 6)
    {
        k = vvod("Введите число от 1 до 6: ");
    }
    int b;
    date n;
    std::string m;
    vtime v;
    if (k != 1 and k != 3 and k != 4)
    {
        b = vvod("Введите значение которое мы ищем: ");
    }
    else if (k == 1)
    {
        std::cout << "Введите значение которое мы ищем: \n";
        n = zapdate();
    }
    else if(k == 3){
        std::cout << "Введите значение которое мы ищем: ";
        std::cin >> m;
    }
    else{
        std::cout << "Введите значение которое мы ищем: \n";
        v = zaptime();
    }

    while (fi != 0)
    {
        arr[N] = zapdialog();
        switch (k)
        {
        case 1:
            if (chechDate(arr[N].Date, n))
            {
                fi = 0;
            }
            break;
        case 2:
            if (arr[N].code == b)
            {
                fi = 0;
            }
            break;
        case 3:
            if (arr[N].cityName == m)
            {
                fi = 0;
            }
            break;
        case 4:
            if (chechTime(arr[N].Time, v))
            {
                fi = 0;
            }
            break;
        case 5:
            if (arr[N].tarif == b)
            {
                fi = 0;
            }
            break;
        case 6:
            if (arr[N].number == b)
            {
                fi = 0;
            }
            break;
        }
        if (fi != 0)
        {
            N++;
            dialog *arr2 = newarr(arr, N, true, 0);
            delete[] arr;
            arr = arr2;
            delete[] arr2;
        }
        
    }
    return arr;
    
}

dialog* newarr(dialog* arr, int N, bool create, int del){
    dialog* newarray = new dialog[1];
    if (create)
    {
        newarray = new dialog[N + 1];
        for (int i = 0; i < N; i++)
        {
            newarray[i] = arr[i];
        }
        count++;
        return newarray;
    }
    else{
        newarray = new dialog[N - 1];
        int k = 0;
        for (int i = 0; i < N; i++)
        {
            if (i != del)
            {
                newarray[k] = arr[i];
                k++;
            }
        }
        count--;
        return newarray;
    }
}

bool chechDate(date d, date n){
    int k = 0;
    if (d.day != n.day)
    {
        k++;
    }
    if (d.mounth != n.mounth)
    {
        k++;
    }
    if (d.year != n.year)
    {
        k++;
    }

    if (k == 0)
    {
        return true;
    }
    else{
        return false;
    }
}

bool chechTime(vtime d, vtime n){
    int k = 0;
    if (d.hours != n.hours)
    {
        k++;
    }
    if (d.minutes != n.minutes)
    {
        k++;
    }

    if (k == 0)
    {
        return true;
    }
    else{
        return false;
    }
}

dialog zapdialog(){
    dialog dialog1;
    dialog1.Date = zapdate();
    dialog1.code = vvod("Введите код города: ");
    std::string lalala;
    while (true)
    {
        std::cout << "Введите название города: ";std::cin >> lalala;
        
        if (lalala.length() <= 80)
        {
            int m = 0;
            for (int i = 0; i < lalala.length(); i++)
            {
                if(lalala[i] >47 and lalala[i] < 58){
                    m++;
                }
            }
            if (m > 0)
            {
                std::cout << "Нет цифрам в городах!\n";
            }
            else{
                break;
            }
            
        }
        else{
            std::cout << "Не больше 80 символов\n";
        }
    }
    for (int i = 0; i < lalala.length(); i++)
    {
        dialog1.cityName[i] = lalala[i];
    }
    for (int i = 0; i < 80 - lalala.length(); i++)
    {
        dialog1.cityName[i + lalala.length()] = '0';
    }
    dialog1.Time = zaptime();
    long long int tarif = -1;
    while (tarif < 0)
    {
        tarif = vvod("Введите тариф по которому шел разговор: ");
        if (tarif < 0)
        {
            std::cout << "Минимальный тариф - 0\n";
        }
    }
    dialog1.tarif = tarif;
    long long int number = -1;
    while (number < 0)
    {
        number = vvod("Введите номер телефона по которому шел разговор: ");
        if (number < 0)
        {
            std::cout << "Минимальный номер телефона - 0\n";
        }
    }
    dialog1.number = number;
    dialog1.sum = (dialog1.Time.hours * 60 + dialog1.Time.minutes)*tarif;
    return dialog1;
}

dialog* dopoln(dialog* &arr, int n){
    dialog *arr2 = newarr(arr, n, true, 0);
    arr2[n] = zapdialog();
    delete[] arr;
    arr = arr2;
    delete[] arr2;
    dialogToFile(arr[n]);
    return arr;
}

vtime zaptime(){
    vtime t1;
    int hours = -1, minutes = -1;
    while (hours < 0)
    {
        hours = vvod("Введите сколько часов проговорил человек: ");
        if (hours < 0)
        {
            std::cout << "Минимум 0 часов\n";
        }
    }
    while (minutes < 0 or minutes > 59)
    {
        minutes = vvod("Введите сколько минут проговорил человек: ");
        if (minutes < 0)
        {
            std::cout << "Минимум 0 минут\n";
        }
        else if(minutes > 59){
            std::cout << "Максимум 59 минут\n";
        }
    }
    t1.hours = hours;
    t1.minutes = minutes;
    return t1;
}

date zapdate(){
    std::cout << "Ввод даты в которую велся данный диалог: \n";
    int day = -1, mounth = -1, year;
    while(day < 1 or day > 31){
        day = vvod("Введите день: ");
        if (day < 1 or day > 31)
        {
            std::cout << "День должен быть числом от 1 до 31\n";
        }
    }
    while(mounth < 1 or mounth > 12){
        mounth = vvod("Введите месяц: ");
        if (mounth < 1 or mounth > 31)
        {
            std::cout << "Месяц должен быть числом от 1 до 12\n";
        }
    }
    year = vvod("Введите год: ");
    date d1;
    d1.day = day;
    d1.mounth = mounth;
    d1.year = year;
    return d1;
}

void dateVivod(date Date){
    std::cout << Date.day << "." << Date.mounth << "." << Date.year;
}

void timeVivod(vtime Time){
    std::cout << Time.hours << " ч " << Time.minutes << " мин";
}

void vivod(dialog* arr, int n){
    std::cout << "Телефонная книга: \n";
    std::cout << "№ | Дата | Код города | Название города | Время разговора | Тариф | Цена за звонок | Номер телефона\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << i + 1 << " | ";
        dateVivod(arr[i].Date);
        std::cout << " | " << arr[i].code << " | ";
        for (int j = 0; j < 80; j++)
        {
            if (arr[i].cityName[j] == '0')
            {
                break;
            }
            else{
                std::cout << arr[i].cityName[j];
            }
        }
        std::cout << " | ";
        timeVivod(arr[i].Time);
        std::cout << " | " << arr[i].tarif << " | " << arr[i].sum << " | " << arr[i].number;
        std::cout << std::endl;
    }
}

void dialogToFile(dialog d){
    std::ofstream file("dialog.dat", std::ios::binary | std::ios::app);
    file.write((char*)(&d.Date.day), sizeof(d.Date.day));
    file.write((char*)(&d.Date.mounth), sizeof(d.Date.mounth));
    file.write((char*)(&d.Date.year), sizeof(d.Date.year));
    file.write((char*)(&d.code), sizeof(d.code));
    file.write((char*)(&d.cityName), sizeof(d.cityName));
    file.write((char*)(&d.Time.hours), sizeof(d.Time.hours));
    file.write((char*)(&d.Time.minutes), sizeof(d.Time.minutes));
    file.write((char*)(&d.tarif), sizeof(d.tarif));
    file.write((char*)(&d.number), sizeof(d.number));
    file.write((char*)(&d.sum), sizeof(d.sum));
    file.close();
    file.open("dialog.dat", std::ios::binary | std::ios::in);
    /* dateVivod(d.Date);
    timeVivod(d.Time);
    std::cout  << std::to_string( d.code) << d.cityName  << std::to_string(d.tarif) << std::to_string(d.number) << std::to_string(d.sum) << std::endl; */
}

dialog* fileToArr(){
    dialog *arr;
    dialog d;
    int n = 0;
    std::ifstream file("dialog.dat", std::ios::binary | std::ios::in);
    while (file)
    {
        file.read((char*)(&d.Date.day), sizeof(d.Date.day));
        file.read((char*)(&d.Date.mounth), sizeof(d.Date.mounth));
        file.read((char*)(&d.Date.year), sizeof(d.Date.year));
        file.read((char*)(&d.code), sizeof(d.code));
        file.read((char*)(&d.cityName), sizeof(d.cityName));
        file.read((char*)(&d.Time.hours), sizeof(d.Time.hours));
        file.read((char*)(&d.Time.minutes), sizeof(d.Time.minutes));
        file.read((char*)(&d.tarif), sizeof(d.tarif));
        file.read((char*)(&d.number), sizeof(d.number));
        file.read((char*)(&d.sum), sizeof(d.sum));
        n++;
    }
    n--;
    count = n;
    file.close();
    arr = new dialog[n];
    int i = 0;
    file.open("dialog.dat", std::ios::binary | std::ios::in);
    while (file)
    {
        file.read((char*)(&d.Date.day), sizeof(d.Date.day));
        file.read((char*)(&d.Date.mounth), sizeof(d.Date.mounth));
        file.read((char*)(&d.Date.year), sizeof(d.Date.year));
        file.read((char*)(&d.code), sizeof(d.code));
        file.read((char*)(&d.cityName), sizeof(d.cityName));
        file.read((char*)(&d.Time.hours), sizeof(d.Time.hours));
        file.read((char*)(&d.Time.minutes), sizeof(d.Time.minutes));
        file.read((char*)(&d.tarif), sizeof(d.tarif));
        file.read((char*)(&d.number), sizeof(d.number));
        file.read((char*)(&d.sum), sizeof(d.sum));
        if (i <= n)
        {
            arr[i] = d;
        }
        i++;
    }
    return arr;
}

dialog* findel(dialog* arr, int N, int task){
    std::cout << "Введите поиск по какой переменной будет производиться: 1 - дата\n 2 - код города\n 3 - название города\n 4 - время разговора\n 5 - тариф\n 6 - номер телефона: \n";
    int k = 0;
    while (k < 1 or k > 6)
    {
        k = vvod("Введите число от 1 до 6: ");
    }
    int b;
    date n;
    std::string m;
    vtime v;
    if (k != 1 and k != 3 and k != 4)
    {
        b = vvod("Введите значение которое мы ищем: ");
    }
    else if (k == 1)
    {
        std::cout << "Введите значение которое мы ищем: \n";
        n = zapdate();
    }
    else if(k == 3){
        std::cout << "Введите значение которое мы ищем: ";
        std::cin >> m;
    }
    else{
        std::cout << "Введите значение которое мы ищем: \n";
        v = zaptime();
    }
    int ggg = 0;
    for (int i = 0; i < N; i++)
    {
        int t = 0;
        switch (k)
        {
        case 1:
            if (chechDate(arr[i].Date, n))
            {
                t++;
            }
            break;
        case 2:
            if (arr[i].code == b)
            {
                t++;
            }
            break;
        case 3:
            if (arr[i].cityName == m)
            {
                t++;
            }
            break;
        case 4:
            if (chechTime(arr[i].Time, v))
            {
                t++;
            }
            break;
        case 5:
            if (arr[i].tarif == b)
            {
                t++;
            }
            break;
        case 6:
            if (arr[i].number == b)
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
                arr[i] = zapdialog();
            }
            else if(task == 4){
                dialog* arr2 = newarr(arr, N, false, i);
                delete[] arr;
                arr = arr2;
            }
            else if (task == 5)
            {
                std::cout << i + 1 << " | ";
                dateVivod(arr[i].Date);
                std::cout << " | " << arr[i].code << " | " << arr[i].cityName << " | ";
                timeVivod(arr[i].Time);
                std::cout << " | " << arr[i].tarif << " | " << arr[i].sum << " | " << arr[i].number;
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

dialog* arrayN(int n){
    dialog *arr = new dialog[n];
    for (int i = 0; i < n; i++)
    {
        std::cout << "=======================================\n";
        std::cout << "Ввод в базу " << i + 1 << " номера телефона\n";
        arr[i] = zapdialog();
    }
    count = n;
    return arr;
}

dialog* bobblesort(dialog *arr, int N){
    std::cout << "Введите сортировка по какой переменной будет производиться: 1 - дата, 2 - код города, 3 - название города, 4 - время разговора, 5 - тариф, 6 - номер телефона: \n";
    int k = 0;
    while (k < 1 or k > 6)
    {
        k = vvod("Введите число от 1 до 6: ");
    }   
    dialog QQQ;
    switch (k)
    {
    case 1:
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count - 1; j++)
            {
                if (dateSort(arr[j].Date, arr[j+1].Date))
                {
                    QQQ = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = QQQ;
                }
            }
        }
        break;
    case 2:
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count - 1; j++)
            {
                if (arr[j].code < arr[j + 1].code)
                {
                    QQQ = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = QQQ;
                }
            }
        }
        break;
    case 3:
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count - 1; j++)
            {
                if (alphabetSort(arr[j].cityName, arr[j + 1].cityName))
                {
                    QQQ = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = QQQ;
                }
            }
        }
        break;
    case 4:
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count - 1; j++)
            {
                if ((arr[j].Time.hours*60 + arr[j].Time.minutes) < (arr[j + 1].Time.hours*60 + arr[j + 1].Time.minutes))
                {
                    QQQ = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = QQQ;
                }
            }
        }
    case 5:
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count - 1; j++)
            {
                if (arr[j].tarif < arr[j + 1].tarif)
                {
                    QQQ = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = QQQ;
                }
            }
        }
        break;
    case 6:
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count - 1; j++)
            {
                if (arr[j].number < arr[j + 1].number)
                {
                    QQQ = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = QQQ;
                }
            }
        }
        break;
    }
    return arr;
}