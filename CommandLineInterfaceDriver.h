#ifndef COMMAND_LINE_INTERFACE_DRIVER_H
#define COMMAND_LINE_INTERFACE_DRIVER_H

#include <string>
#include <iostream>
#include "WeatherController.h"

class CommandLineInterfaceDriver {
public:
    CommandLineInterfaceDriver();
    ~CommandLineInterfaceDriver();

    int start();

private:
    //communicates with the OpenWeather api and simulates db
    WeatherController* weatherController;

    void displayMenu();
    void showWeatherForCity();
};


#endif
