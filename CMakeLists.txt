cmake_minimum_required(VERSION 3.12.0)

project(cet VERSION 0.0.5)
message(STATUS "~~~ ${PROJECT_NAME} v${PROJECT_VERSION} ~~~")

option(UNITTEST "Build Unit Tests" ON)
message(STATUS "Unit Tests : ${UNITTEST}")


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


if( CMAKE_BUILD_TYPE )
    message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")
else()
    message(STATUS "Build Type : None")
endif()

if( NOT MSVC )
    add_compile_options(-Wall
                        -Wextra
                        -pedantic
                        -pedantic-errors
                        -Werror
                        -Wshadow
                        -Wold-style-cast
                        -Wnull-dereference
                        -Wnon-virtual-dtor
                        -Woverloaded-virtual
                        )
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    message(STATUS "GCC < 9.0 requires 'stdc++fs' for std::filesystem support")
    link_libraries(stdc++fs)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    message(STATUS "Clang < 9.0 requires 'c++fs' for std::filesystem support")
    link_libraries(c++fs)
endif()

include(Template)

include("${CMAKE_BINARY_DIR}/conan_paths.cmake" OPTIONAL)

find_package(yaml-cpp REQUIRED)
find_package(argparse REQUIRED)

if (NOT TARGET yaml-cpp::yaml-cpp)
    add_library(yaml-cpp::yaml-cpp INTERFACE IMPORTED)
    target_link_libraries(yaml-cpp::yaml-cpp INTERFACE yaml-cpp)
endif()

include_directories("include")
add_subdirectory(src)


if( UNITTEST )
    enable_testing()
    add_subdirectory("test")
endif()
