cmake_minimum_required(VERSION 2.8)
project(logTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)

find_package(Threads REQUIRED)
include_directories(${CMAKE_SOURCE_DIR})
set(SOURCES
    "logTest.cpp"
    "buffer.cpp"
    "log.cpp"
)

add_executable(logTest ${SOURCES})

target_link_libraries(logTest
    ${CMAKE_THREAD_LIBS_INIT}
)