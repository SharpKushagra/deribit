#include "api_client.hpp"
#include "ws_market_stream.hpp"
#include <iostream>
#include <thread>

int main() {
    std::string client_id = "oWXQh13A";     // ⬅️ Replace here
    std::string client_secret = "uScQMrHUNuAo3_hYkMY3yZObnTTuSxSuWx8cjd6kwLA"; // ⬅️ Replace here

    APIClient api(client_id, client_secret);

    // Try an initial test API call
    auto orderbook = api.getOrderBook("BTC-PERPETUAL");
    if (orderbook.contains("result")) {
        std::cout << "Order Book:\n" << orderbook.dump(2) << "\n";
    } else {
        std::cerr << "Failed to fetch order book.\n";
    }

    std::cout << "Starting Deribit Streaming Demo...\n";

    // Start market stream in a separate thread
    std::thread stream_thread([]() {
        start_deribit_market_stream("BTC-PERPETUAL");
    });

    stream_thread.join();

    return 0;
}
