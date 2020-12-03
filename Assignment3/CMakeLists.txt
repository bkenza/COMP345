cmake_minimum_required(VERSION 3.17)
project(Assignment3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment3
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
        mainGameLoopDriver.cpp
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
        PlayerDriver.cpp PlayerStrategies.cpp PlayerStrategies.h)
