add_executable(Visual-Debug visual_debug.cpp)

target_link_libraries(Visual-Debug
  PRIVATE
    SFML::Graphics
    SFML::Window

)

target_include_directories(Visual-Debug
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)
