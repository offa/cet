add_library(cet-config Config.cpp)
target_link_libraries(cet-config PRIVATE yaml-cpp::yaml-cpp)

add_library(cet-reporter StreamReporter.cpp)

add_executable(cet Main.cpp)
target_link_libraries(cet
    PRIVATE
        cet-config
        cet-reporter
        argparse::argparse
        )
