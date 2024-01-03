cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(log-test)

enable_language(C)
set(CMAKE_C_STANDARD 17)

string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

add_definitions("-DLOG_ENABLE_INFO_MSG")
add_definitions("-DLOG_ENABLE_EVENT_MSG")
add_definitions("-DLOG_ENABLE_ERROR_MSG")

add_executable(${CMAKE_PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/main.c
    ${CMAKE_SOURCE_DIR}/logs.c
)
