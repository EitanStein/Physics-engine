add_executable(Physics-Engine main.cpp)

target_link_libraries(Physics-Engine
  PRIVATE

)

target_include_directories(Physics-Engine
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_subdirectory(logging)
add_subdirectory(visualization)