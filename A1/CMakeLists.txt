cmake_minimum_required(VERSION 3.17)
project(A1)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(Maps)

add_executable(A1
        Maps/caribbean.map
        Maps/LOTR2.map
        Maps/solar.map
        Maps/sudamerica.map
        Map.cpp
        Map.h
        MapDriver.cpp
        Orders.h
        Orders.cpp
        OrdersDriver.cpp
        Player.h
        Player.cpp
        PlayerDriver.cpp
        Cards.cpp
        Cards.h
        CardsDriver.cpp
        MapLoader.cpp
        MapLoaderDriver.cpp)
