add_executable(Physics-Engine main.cpp)

if (MSVC)
    target_compile_options(Physics-Engine PRIVATE /W4)
else()
    target_compile_options(Physics-Engine PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address -fno-omit-frame-pointer)
    target_link_libraries(Physics-Engine PRIVATE -fsanitize=address)
endif()

target_link_libraries(Physics-Engine
  PRIVATE
    logging_module
    physics_module
)

target_include_directories(Physics-Engine
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_subdirectory(core)
add_subdirectory(logging)
add_subdirectory(visualization)