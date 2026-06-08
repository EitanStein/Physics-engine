cmake_minimum_required(VERSION 3.28) 
project(MISDistributedRouting LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

include(CTest)
enable_testing()
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        6ee0826dcae55ed1e06b2c5701981221e979e1e6 #3.15.0
    FIND_PACKAGE_ARGS CONFIG
)
FetchContent_MakeAvailable(Catch2)


FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        0fa201c969e48ecc253581c5841ce73f44d42f49 #3.0.2
    FIND_PACKAGE_ARGS COMPONENTS Graphics Window CONFIG     
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        486b55554f11c9cccc913e11a87085b2a91f706f #1.16.0
    FIND_PACKAGE_ARGS CONFIG
)
FetchContent_MakeAvailable(spdlog)

add_subdirectory(src)
add_subdirectory(tests)
