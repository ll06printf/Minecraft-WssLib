add_library(MSSLib STATIC
        MSSLib/Provider.cpp
        include/Provider.h
        include/Events.h
)

target_include_directories(MSSLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)