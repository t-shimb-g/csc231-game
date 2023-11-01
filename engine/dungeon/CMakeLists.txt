add_library(dungeon
  builder.cpp
  decorator.cpp
  door.cpp
  room.cpp
  tile.cpp
  fov.cpp
  fog.cpp
  pathfinding.cpp
  dungeon.cpp
)

target_include_directories(dungeon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dungeon PUBLIC util graphics)
