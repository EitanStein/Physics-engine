add_library(physics_module 
      collision/detect/circle_circle.cpp
      collision/detect/circle_rect.cpp
      collision/detect/rect_rect.cpp
      collision/resolve.cpp 
      collision/dispatch.cpp)

if (MSVC)
    target_compile_options(physics_module PRIVATE /W4)
else()
    target_compile_options(physics_module PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(physics_module
  PRIVATE
    spdlog::spdlog
)

target_include_directories(physics_module
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

