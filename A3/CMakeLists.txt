cmake_minimum_required(VERSION 3.17)
project(A3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Maps)

add_executable(A3
        Maps/caribbean.map
        Maps/LOTR2.map
        Maps/solar.map
        Maps/sudamerica.map
        Cards.cpp
        Cards.h
        CardsDriver.cpp
        GameEngine.cpp
        GameEngine.h
        GameEngineDriver.cpp
        GameObservers.cpp
        GameObservers.h
        Map.cpp
        Map.h
        MapDriver.cpp
        MapLoader.cpp
        MapLoader.h
        MapLoaderDriver.cpp
        Orders.cpp
        Orders.h
        OrdersDriver.cpp
        Player.cpp
        Player.h
        PlayerDriver.cpp)
