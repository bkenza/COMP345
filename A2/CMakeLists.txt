cmake_minimum_required(VERSION 3.17)
project(A2)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(Maps)

add_executable(A2
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
        PlayerDriver.cpp
        GameObservers.h
        GameObservers.cpp)
