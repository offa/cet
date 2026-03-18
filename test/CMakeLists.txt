find_package(Catch2 REQUIRED)
find_package(trompeloeil REQUIRED)

add_library(TestSupport $<$<NOT:$<BOOL:${WIN32}>>:GuardedEnv.cpp> $<$<BOOL:${WIN32}>:GuardedEnvWin.cpp>)

function(add_test_suite name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} PRIVATE Catch2::Catch2WithMain trompeloeil::trompeloeil)
    add_test(${name} ${name})

    # Workaround for catch2 #3076
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "22")
        target_compile_options(${name} PRIVATE -Wno-c2y-extensions)
    endif()
endfunction()

add_test_suite(ConfigTest ConfigTest.cpp)
target_link_libraries(ConfigTest
    PRIVATE
        cet-config
        cet-steps
        yaml-cpp::yaml-cpp
        )

add_test_suite(StepsTest FileSystemStepsTest.cpp StepExecutorTest.cpp EnvStepTest.cpp)
target_link_libraries(StepsTest PRIVATE TestSupport cet-steps)

add_test_suite(ReporterTest StreamReporterTest.cpp)
target_link_libraries(ReporterTest PRIVATE cet-reporter)


add_custom_target(unittest ConfigTest
                    COMMAND StepsTest
                    COMMAND ReporterTest

                    COMMENT "Running unittests\n\n"
                    VERBATIM
                    )
