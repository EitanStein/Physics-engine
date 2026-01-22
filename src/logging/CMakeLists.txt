add_library(logging_module INTERFACE)

target_link_libraries(logging_module
  INTERFACE
    spdlog::spdlog
)

target_include_directories(logging_module
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

