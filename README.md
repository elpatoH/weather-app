# Weather Application
This Weather Application is a C++ command-line tool that fetches and displays 
weather information for specific cities using the OpenWeather API.

### Features
* Fetch weather data for any city using the OpenWeather API.
* Current temperature (in Celsius).
* Humidity percentage.
* Atmospheric pressure (in hPa).
* Wind speed (in m/s).
* Weather description.

### Dependencies
1. **[libcurl](https://curl.se/libcurl/):**  
   For making HTTP requests to the OpenWeather API.

2. **[nlohmann/json](https://github.com/nlohmann/json):**  
   For parsing JSON responses from the OpenWeather API.

### Installing Dependencies
1. Install Homebrew: [https://brew.sh](https://brew.sh)
2. Install the dependencies:
```bash
brew install curl
brew install nlohmann-json
```

### Build
1. Clone repo
```bash
git clone something
cd weather-app
```
2. Compile using make
```bash
make
```
3. run
```bash
./weatherApp
```

### Clean
```bash
make clean
```

### Communication Flow

main -> CommandLineInterfaceDriver -> WeatherController <-> HTTPSController <-> OpenWeather API
