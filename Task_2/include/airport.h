#include <iostream>

typedef union{
        int hour;
        int minute;
}Union;

typedef struct{
        long long int raceNum;
        std::string PlaneType;
        std::string Place;
        Union Time;
}airport;

