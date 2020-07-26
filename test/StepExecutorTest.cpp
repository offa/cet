/*
 * cet - Container Environment Test
 *
 * Copyright (C) 2020  offa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "StepExecutor.h"
#include <vector>
#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

namespace
{
    class StepMock : public cet::TestStep
    {
    public:
        MAKE_MOCK0(execute, cet::Result(), const override);
        MAKE_MOCK0(describe, std::string(), const override);
    };


    class IgnoreReporter : public cet::Reporter
    {
        void printResult([[maybe_unused]] cet::Result result, [[maybe_unused]] const std::string& description) override
        {
        }

        void printError([[maybe_unused]] const std::string& message) override
        {
        }
    };


    class ReporterMock : public cet::Reporter
    {
        MAKE_MOCK2(printResult, void(cet::Result, const std::string&), override);
        MAKE_MOCK1(printError, void(const std::string&), override);
    };


    class ReporterAdapter : public cet::Reporter
    {
    public:
        explicit ReporterAdapter(std::shared_ptr<ReporterMock> mockImpl)
            : impl(mockImpl)
        {
        }

        void printResult(cet::Result result, const std::string& description) override
        {
            impl->printResult(result, description);
        }

        void printError(const std::string& message) override
        {
            impl->printError(message);
        }

    private:
        std::shared_ptr<ReporterMock> impl;
    };

}

TEST_CASE("Execute executes steps", "[StepExecutorTest]")
{
    std::vector<StepMock> steps{2};
    REQUIRE_CALL(steps[0], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[0], describe()).RETURN("");
    REQUIRE_CALL(steps[1], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[1], describe()).RETURN("");

    cet::StepExecutor se{std::make_unique<IgnoreReporter>()};
    se.executeSteps(steps);
}

TEST_CASE("Execute returns successful if all steps are successful", "[StepExecutorTest]")
{
    std::vector<StepMock> steps{3};
    REQUIRE_CALL(steps[0], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[0], describe()).RETURN("");
    REQUIRE_CALL(steps[1], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[1], describe()).RETURN("");
    REQUIRE_CALL(steps[2], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[2], describe()).RETURN("");

    cet::StepExecutor se{std::make_unique<IgnoreReporter>()};
    CHECK(se.executeSteps(steps) == cet::Result::Pass);
}

TEST_CASE("Execute returns failure if one step failed", "[StepExecutorTest]")
{
    std::vector<StepMock> steps{3};
    REQUIRE_CALL(steps[0], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[0], describe()).RETURN("");
    REQUIRE_CALL(steps[1], execute()).RETURN(cet::Result::Fail);
    REQUIRE_CALL(steps[1], describe()).RETURN("");
    REQUIRE_CALL(steps[2], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[2], describe()).RETURN("");

    cet::StepExecutor se{std::make_unique<IgnoreReporter>()};
    CHECK(se.executeSteps(steps) == cet::Result::Fail);
}

TEST_CASE("Execute prints steps with result", "[StepExecutorTest]")
{
    std::vector<StepMock> steps{2};
    REQUIRE_CALL(steps[0], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[0], describe()).RETURN("abc");
    REQUIRE_CALL(steps[1], execute()).RETURN(cet::Result::Fail);
    REQUIRE_CALL(steps[1], describe()).RETURN("def");

    auto reporter = std::make_shared<ReporterMock>();
    REQUIRE_CALL(*reporter, printResult(cet::Result::Pass, "abc"));
    REQUIRE_CALL(*reporter, printResult(cet::Result::Fail, "def"));

    cet::StepExecutor se{std::make_unique<ReporterAdapter>(reporter)};
    se.executeSteps(steps);
}

TEST_CASE("Execute catches exception thrown by step", "[StepExecutorTest]")
{
    std::vector<StepMock> steps{1};
    REQUIRE_CALL(steps[0], execute()).THROW(std::runtime_error{"intentional thrown"});

    auto reporter = std::make_shared<ReporterMock>();
    REQUIRE_CALL(*reporter, printError("intentional thrown"));

    cet::StepExecutor se{std::make_unique<ReporterAdapter>(reporter)};
    CHECK(se.executeSteps(steps) == cet::Result::Fail);
}

TEST_CASE("Execute catches exception and continues steps", "[StepExecutorTest]")
{
    std::vector<StepMock> steps{3};
    REQUIRE_CALL(steps[0], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[0], describe()).RETURN("");
    REQUIRE_CALL(steps[1], execute()).THROW(std::runtime_error{"intentional"});
    REQUIRE_CALL(steps[2], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[2], describe()).RETURN("");

    cet::StepExecutor se{std::make_unique<IgnoreReporter>()};
    CHECK(se.executeSteps(steps) == cet::Result::Fail);
}
