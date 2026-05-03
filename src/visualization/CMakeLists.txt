add_executable(Visual-Debug visual_debug.cpp)

if (MSVC)
    target_compile_options(Visual-Debug PRIVATE /W4)
else()
    target_compile_options(Visual-Debug PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(Visual-Debug
  PRIVATE
    SFML::Graphics
    SFML::Window
    logging_module
    physics_module

)

target_include_directories(Visual-Debug
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)
