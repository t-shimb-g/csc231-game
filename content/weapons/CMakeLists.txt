add_library(weapons
    bite.cpp
    cleaver.cpp
)

target_include_directories(weapons PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(weapons PUBLIC engine events)
