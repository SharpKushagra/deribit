#include "api_client.hpp"
#include "ws_market_stream.hpp"
#include <iostream>
#include <thread>

int main() {
    std::cout << "Starting Deribit Streaming Demo...\n";
    std::thread stream_thread([]() {
        start_deribit_market_stream("BTC-PERPETUAL");
    });
    stream_thread.join();
    return 0;
}
