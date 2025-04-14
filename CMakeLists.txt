cmake_minimum_required(VERSION 3.10)
project(deribit_trading_system)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories("${CMAKE_SOURCE_DIR}/third_party/json/single_include")
include_directories("${CMAKE_SOURCE_DIR}/third_party/websocketpp")
include_directories("${CMAKE_SOURCE_DIR}/third_party/asio/asio/include")

# Find required libraries
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED)

# Define executable and source files
add_executable(deribit
    main.cpp                     # main is in project root
    src/api_client.cpp
    src/ws_market_stream.cpp
    # src/order_manager.cpp     # <- Uncomment this only if the file exists
)

# Link libraries
target_link_libraries(deribit
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
    ws2_32
)
