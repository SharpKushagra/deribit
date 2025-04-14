#pragma once

#include <string>
#include <nlohmann/json.hpp>

class APIClient {
public:
    APIClient(const std::string& client_id, const std::string& client_secret); // ✅ Constructor
    nlohmann::json getOrderBook(const std::string& instrument);

private:
    std::string client_id_;
    std::string client_secret_;
};
