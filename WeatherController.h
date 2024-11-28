#ifndef WEATHER_CONTROLLER_H
#define WEATHER_CONTROLLER_H

#include <string>
#include <iostream>
#include <array>
#include <ctime>
#include <algorithm>
#include "HTTPSController.h"

class WeatherController{
public:

    WeatherController();
    ~WeatherController();

    void showSpecificCity(std::string city);
    void setFavorite(std::string city);
    void showFavorites();

private:
    //num of current elements in favorites vector
    int numElements;
    //holds favorite cities names
    std::vector<std::string>* favorites;

    //curl wrapper class
    HttpsController* https;

    std::string encodeCityName(std::string& city);
};

#endif