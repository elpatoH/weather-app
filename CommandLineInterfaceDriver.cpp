#include "CommandLineInterfaceDriver.h"


using namespace std;

/* PUBLIC */

//constructor definition
CommandLineInterfaceDriver::CommandLineInterfaceDriver(){
    //weatherController talks directly with OpenWeather
    weatherController = new WeatherController;
}

CommandLineInterfaceDriver::~CommandLineInterfaceDriver(){
    delete this->weatherController;
}

int CommandLineInterfaceDriver::start() {
    //efficient input
    bool running = true;
    ios::sync_with_stdio(0);
    cin.tie(0);


    cout << "Welcome to the weather app!" << endl;
    while (running) {
        //start input
        this->displayMenu();
        string input;
        getline(cin, input);

        if (input == "1") {
            this->showWeatherForCity();
        } else if (input == "2") {
            this->weatherController->showFavorites();
        } else if (input == "3") {
            cout << "Exiting the weather app. Goodbye!" << endl;
            running = false;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}

/* PRIVATE */

void CommandLineInterfaceDriver::displayMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. Find weather for city." << endl;
    cout << "2. Show favorites list." << endl;
    cout << "3. Exit" << endl;
}

//display weather for current city picked
void CommandLineInterfaceDriver::showWeatherForCity() {
    //get city name
    string cityName;
    cout << "Type name of a city: ";
    getline(cin, cityName);
    cout << endl;

    //display city data
    bool error = this->weatherController->showSpecificCity(cityName);
    if (error){
        return;
    }

    //ask if user wants to save to favorites
    string saveCity;
    cout << "\nWould you like to save this city as favorite? (\"1\" = yes): ";
    getline(cin, saveCity);
    cout << endl;
    if (saveCity == "1"){
        this->weatherController->setFavorite(cityName);
    }
}