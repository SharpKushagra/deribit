#include "api_client.hpp"
#include <curl/curl.h>
#include <sstream>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* out) {
    out->append((char*)contents, size * nmemb);
    return size * nmemb;
}

APIClient::APIClient() {}

nlohmann::json APIClient::getOrderBook(const std::string& instrument) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::ostringstream url;
        url << "https://test.deribit.com/api/v2/public/get_order_book?instrument_name=" << instrument;
        curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            return nlohmann::json::parse(response);
        }
    }
    return {};
}
