
add_executable(Testing test_main.cpp)

target_link_libraries(Testing
  PRIVATE
    Catch2::Catch2WithMain
)

target_include_directories(Testing
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

add_test(NAME Physics_tests COMMAND $<TARGET_FILE:Testing>)
