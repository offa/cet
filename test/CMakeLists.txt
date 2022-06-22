find_package(Catch2 REQUIRED)
find_package(trompeloeil REQUIRED)

add_library(TestLibs INTERFACE)
target_link_libraries(TestLibs INTERFACE Catch2::Catch2WithMain trompeloeil::trompeloeil)

add_library(TestSupport $<$<NOT:$<BOOL:${WIN32}>>:GuardedEnv.cpp> $<$<BOOL:${WIN32}>:GuardedEnvWin.cpp>)

add_executable(ConfigTest ConfigTest.cpp)
target_link_libraries(ConfigTest
    PRIVATE
        cet-config
        cet-steps
        yaml-cpp::yaml-cpp
        Catch2::Catch2WithMain
        trompeloeil::trompeloeil
        )
add_test(ConfigTest ConfigTest)

add_executable(StepsTest FileSystemStepsTest.cpp StepExecutorTest.cpp EnvStepTest.cpp)
target_link_libraries(StepsTest PRIVATE TestLibs TestSupport cet-steps)
add_test(StepsTest StepsTest)

add_executable(ReporterTest StreamReporterTest.cpp)
target_link_libraries(ReporterTest PRIVATE TestLibs cet-reporter)
add_test(ReporterTest ReporterTest)



add_custom_target(unittest ConfigTest
                    COMMAND StepsTest
                    COMMAND ReporterTest

                    COMMENT "Running unittests\n\n"
                    VERBATIM
                    )
