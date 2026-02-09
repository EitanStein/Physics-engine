add_library(physics_module collision/detect.cpp collision/resolve.cpp)

target_link_libraries(physics_module
  PRIVATE
    spdlog::spdlog
)

target_include_directories(physics_module
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

