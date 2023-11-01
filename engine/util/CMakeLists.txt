add_library(util
  randomness.cpp
  grid.cpp
  timer.cpp
  vec.cpp
)

target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
