find_package(Catch2 REQUIRED)

add_library(TestMain TestMain.cpp)
target_link_libraries(TestMain PUBLIC Catch2::Catch2)


add_executable(ConfigTest ConfigTest.cpp)
target_link_libraries(ConfigTest PRIVATE TestMain cet-config yaml-cpp::yaml-cpp)
add_test(ConfigTest ConfigTest)

add_executable(FileSystemStepsTest FileSystemStepsTest.cpp)
target_link_libraries(FileSystemStepsTest PRIVATE TestMain)
add_test(FileSystemStepsTest FileSystemStepsTest)


add_custom_target(unittest ConfigTest
                    COMMAND FileSystemStepsTest

                    COMMENT "Running unittests\n\n"
                    VERBATIM
                    )
