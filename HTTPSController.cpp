#include "HTTPSController.h"

using json = nlohmann::json;

//constructor
HttpsController::HttpsController(){
    this->curl = curl_easy_init();
    if (!this->curl){
        throw std::runtime_error("ERROR initializing CURL.");
    }

}

HttpsController::~HttpsController() {
    if (this->curl) {
        curl_easy_cleanup(this->curl);
    }
}

/* PUBLIC */

//do a get request to the given URL. Returns json response parsed with nlohmann::json
json HttpsController::getRequest(std::string &url)
{
    std::string response;

    //init CURL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    //make request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        throw std::runtime_error("CURL error: " + std::string(curl_easy_strerror(res)));
    }

    //parse request
    try {
        return json::parse(response);
    } catch (const json::parse_error& e) {
        throw std::runtime_error("JSON parse error: " + std::string(e.what()));
    }
}

/* PRIVATE */

//CURL callback
size_t HttpsController::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}