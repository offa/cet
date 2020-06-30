add_library(cet-config Config.cpp)
target_link_libraries(cet-config PRIVATE yaml-cpp::yaml-cpp)

add_executable(cet Main.cpp)
target_link_libraries(cet PRIVATE cet-config argparse::argparse)
