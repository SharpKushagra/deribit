#include "api_client.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
#include <curl/curl.h>

using json = nlohmann::json;

APIClient::APIClient(const std::string& client_id, const std::string& client_secret)
    : client_id_(client_id), client_secret_(client_secret) {}

// Helper function to receive CURL response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

json APIClient::getOrderBook(const std::string& instrument) {
    std::string url = "https://test.deribit.com/api/v2/public/get_order_book?instrument_name=" + instrument;

    CURL* curl = curl_easy_init();
    std::string response_data;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            try {
                return json::parse(response_data);
            } catch (...) {
                std::cerr << "Failed to parse response as JSON.\n";
            }
        } else {
            std::cerr << "CURL request failed: " << curl_easy_strerror(res) << "\n";
        }
    }

    return json::object(); // Return empty object on failure
}
