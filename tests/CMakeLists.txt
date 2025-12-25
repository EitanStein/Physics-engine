
add_executable(Testing test_main.cpp)

target_link_libraries(Testing
  PRIVATE
    Catch2::Catch2WithMain
)

add_test(NAME Physics_tests COMMAND $<TARGET_FILE:Testing>)
