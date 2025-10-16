cmake_minimum_required(VERSION 3.16)
project(websocket_trading_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Find Boost with required components
# find_package(Boost REQUIRED COMPONENTS system thread)
# find_package(OpenSSL REQUIRED)

# link_directories(${OPENSSL_LIBRARIES})

# Main executable
add_executable(trading_engine
    src/main.cpp
)

# Include directories
target_include_directories(trading_engine PRIVATE)

# Link Boost and pthread
# target_link_libraries(main PRIVATE Boost::filesystem Boost::system)

