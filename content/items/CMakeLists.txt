add_library(items
    heart.cpp
    axeitem.cpp
    sworditem.cpp
)

target_include_directories(items PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(items PUBLIC engine)
