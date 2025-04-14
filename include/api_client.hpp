#pragma once
#include <string>
#include <nlohmann/json.hpp>

class APIClient {
public:
    APIClient();
    nlohmann::json getOrderBook(const std::string& instrument);
};
