find_package(Catch2 REQUIRED)

add_library(TestMain TestMain.cpp)
target_link_libraries(TestMain PUBLIC Catch2::Catch2)


add_executable(ConfigTest ConfigTest.cpp)
target_link_libraries(ConfigTest PRIVATE TestMain cet-config)
add_test(ConfigTest ConfigTest)

add_custom_target(unittest ConfigTest
                    COMMENT "Running unittests\n\n"
                    VERBATIM
                    )
