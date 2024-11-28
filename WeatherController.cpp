#include "WeatherController.h"

using namespace std;

/* PUBLIC */

//constructor definition
WeatherController::WeatherController(){
    this->favorites = new std::vector<std::string>(3, "");
    this->https = new HttpsController();
    this->numElements = 0;
}

WeatherController::~WeatherController(){
    delete this->favorites;
    delete this->https;
}

//display data for specific city
bool WeatherController::showSpecificCity(std::string city){
    std::string encodedCity = this->encodeCityName(city);
    //define url
    std::string url = "https://api.openweathermap.org/data/2.5/weather?q=" + encodedCity + "&appid=8a3b630c28355377800ceb05ba2e4e28";

    //make request
    nlohmann::json response = this->https->getRequest(url);

    //if city not found
    if (response["cod"] == "404"){
        cout << "Sorry, city not found.\n";
        cout << "Press any key to continue.";
        cin.get();
        return 1;
    }

    try
    {
        //convert temp to celsius
        double temperature = response["main"]["temp"].get<double>() - 273.15;
        double humidity = response["main"]["humidity"];
        double pressure = response["main"]["pressure"];
        double windSpeed = response["wind"]["speed"];
        std::string weatherDescription = response["weather"][0]["description"];
        std::string stationName = response["name"];

        //display
        std::cout << "City: " << city << " (" << stationName << ")" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Temperature: " << temperature << " °C" << std::endl;
        std::cout << "Humidity: " << humidity << " %" << std::endl;
        std::cout << "Pressure: " << pressure << " hPa" << std::endl;
        std::cout << "Weather: " << weatherDescription << std::endl;
        std::cout << "Wind Speed: " << windSpeed << " m/s" << std::endl;
    }
    catch (nlohmann::json::exception& e)
    {
        throw std::runtime_error("Error in weather controller: " + std::string(e.what()) + "\n");
    }
    return 0;
}

//given a city sets one of the 3 slots for favorite cities
//simulate a post request to a database
void WeatherController::setFavorite(string city){
    //find duplicate city
    for (const auto& favorite : *favorites) {
        if (favorite == city) {
            cout << "City " << city << " is already in favorites list.";
            return;
        }
    }

    //loop around if favorites vector is filled
    if (this->numElements >= 3){
        this->numElements = 0;
    }

    //set new favorite
    this->favorites->at(this->numElements) = city;
    this->numElements++;
}

//shows all favorite cities
//simulates a get request to a database
void WeatherController::showFavorites(){
    for (int i = 0; i < this->favorites->size(); i++){
        if (this->favorites->at(i) != ""){
            cout << "\nFavorite #" << i+1 << ". ";
            this->showSpecificCity(this->favorites->at(i));
        }
    }
    cout << "\nPress any key to continue.";
    cin.get();
}

//encodes the city string in case there is empty space for example "san diego" -> "san%20diego"
std::string WeatherController::encodeCityName(std::string& city)
{
    std::string encodedCity = "";
    
    for (char c : city) {
        if (c == ' ') {
            encodedCity += "%20";
        } else {
            encodedCity += c;
        }
    }
    return encodedCity;
}
