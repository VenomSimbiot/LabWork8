#pragma once
#include "time.h"
#include "date.h"
#include <iostream>

typedef struct{
        date Date;
        long long int code;
        char cityName[80];
        vtime Time;
        long long int tarif;
        long long int number;
        long long int sum;
}dialog;