#define BOOST_ASIO_USE_IO_SERVICE  // <== FIX FOR BOOST 1.70+

#include "ws_market_stream.hpp"
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include "ws_market_stream.hpp"
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json.hpp>
#include <iostream>

// Define the client type
typedef websocketpp::client<websocketpp::config::asio_client> ws_client;

void start_deribit_market_stream(const std::string& instrument_name) {
    ws_client client;

    try {
        client.init_asio();
        client.set_open_handler([&](websocketpp::connection_hdl hdl) {
            nlohmann::json msg = {
                {"jsonrpc", "2.0"},
                {"id", 1},
                {"method", "public/subscribe"},
                {"params", {
                    {"channels", { "book." + instrument_name + ".raw" }}
                }}
            };
            client.send(hdl, msg.dump(), websocketpp::frame::opcode::text);
        });

        client.set_message_handler([](websocketpp::connection_hdl, ws_client::message_ptr msg) {
            try {
                auto j = nlohmann::json::parse(msg->get_payload());
                if (j.contains("params")) {
                    std::cout << "Market Update: " << j["params"]["data"].dump(2) << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
            }
        });

        websocketpp::lib::error_code ec;
        auto con = client.get_connection("wss://test.deribit.com/ws/api/v2", ec);
        if (ec) {
            std::cerr << "Connect error: " << ec.message() << std::endl;
            return;
        }

        client.connect(con);
        client.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
