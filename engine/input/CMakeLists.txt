add_library(input
  input.cpp
)

find_package(SDL2 REQUIRED)

target_include_directories(input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${SDL2_INCLUDES})
target_link_libraries(input PRIVATE SDL2::SDL2)

