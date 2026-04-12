cmake_minimum_required(VERSION 3.15)
project(DiscordBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find DPP library
find_package(dpp REQUIRED)

# Create executable
add_executable(${PROJECT_NAME} bot.cpp)

# Link DPP library
target_link_libraries(${PROJECT_NAME} dpp)

# Optional: Add pthread for Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

# Copy .env file to build directory (optional)
add_custom_target(copy_env ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/.env"
    "${CMAKE_CURRENT_BINARY_DIR}/.env"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/.env"
)
