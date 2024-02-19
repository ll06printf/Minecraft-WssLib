add_library(WSSLib STATIC
        WSSLib/Provider.cpp
        include/Provider.h
        include/Events.h
        WSSLib/Controller.cpp
        include/Controller.h
        WSSLib/Rule.cpp
        include/Rule.h
        WSSLib/WSSProvider.cpp
        include/WSSProvider.h
)

target_include_directories(WSSLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)