cmake_minimum_required(VERSION 3.19)
project(MySpider C)

set(CMAKE_CXX_STANDARD 14)

include_directories(core/includes)
include_directories(include)
include_directories(include/curl)
include_directories(include/liburi)
include_directories(include/libuv)
include_directories(include/libuv/uv)
include_directories(include/libxml)
include_directories(include/pcre)
include_directories(include/cspider)

add_executable(MySpider sample/main.c)
