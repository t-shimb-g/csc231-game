add_library(events
    updatefov.cpp
    hit.cpp
    die.cpp
    thrust.cpp
    swing.cpp
)

target_include_directories(events PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(events PUBLIC engine)
