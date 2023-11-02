find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_library(audio
  audio.cpp
)

target_include_directories(audio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
target_link_libraries(audio PUBLIC SDL2::SDL2 SDL2_mixer::SDL2_mixer)
