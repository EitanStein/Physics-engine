
add_executable(Testing test_main.cpp)

if (MSVC)
    target_compile_options(Testing PRIVATE /W4)
else()
    target_compile_options(Testing PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address -fno-omit-frame-pointer)
    target_link_libraries(Testing PRIVATE -fsanitize=address)
endif()

target_link_libraries(Testing
  PRIVATE
    logging_module
    Catch2::Catch2WithMain
    physics_module
)

target_include_directories(Testing
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_test(NAME Physics_tests COMMAND $<TARGET_FILE:Testing>)
