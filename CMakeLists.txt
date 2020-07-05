cmake_minimum_required(VERSION 3.12.0)


project(cet VERSION 0.0.1)
message(STATUS "~~~ ${PROJECT_NAME} v${PROJECT_VERSION} ~~~")

option(UNITTEST "Build Unit Tests" ON)
message(STATUS "Unit Tests : ${UNITTEST}")


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


if( CMAKE_BUILD_TYPE )
    message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")
else()
    message(STATUS "Build Type : None")
endif()


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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    message(STATUS "GCC < 9.0 requires '-lstdc++fs' for std::filesystem support")
    add_link_options(-lstdc++fs)
endif()


include("${CMAKE_BINARY_DIR}/conan_paths.cmake" OPTIONAL)

find_package(yaml-cpp REQUIRED)
find_package(argparse REQUIRED)

include_directories("include")
add_subdirectory(src)


if( UNITTEST )
    enable_testing()
    add_subdirectory("test")
endif()
