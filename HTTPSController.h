#ifndef HTTPS_CONTROLLER_H
#define HTTPS_CONTROLLER_H

#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <curl/curl.h>

class HttpsController{
public:
    HttpsController();
    ~HttpsController();

    //abstraction for http get request
    nlohmann::json getRequest(std::string& url);

private:
    CURL* curl;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response);
};

#endif