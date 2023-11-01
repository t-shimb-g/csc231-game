add_library(graphics
  graphics.cpp
  sprite.cpp
  animatedsprite.cpp
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(graphics PUBLIC util PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)
