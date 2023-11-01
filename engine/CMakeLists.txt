project(engine)

add_subdirectory(util)
add_subdirectory(graphics)
add_subdirectory(dungeon)
add_subdirectory(input)
add_subdirectory(audio)

add_library(engine
  action.cpp
        entity.cpp
        entities.cpp
  camera.cpp
  engine.cpp
  event.cpp
  events.cpp
  settings.cpp
  weapon.cpp
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine PUBLIC util graphics dungeon input audio)
