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
}

TEST_CASE("Execute executes steps", "[StepExecutorTest]")
{
    std::vector<StepMock> steps{2};
    REQUIRE_CALL(steps[0], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[1], execute()).RETURN(cet::Result::Pass);

    cet::StepExecutor se;
    se.executeSteps(steps);
}

TEST_CASE("Execute returns successful if all steps are successful", "[StepExecutorTest]")
{
    std::vector<StepMock> steps{3};
    REQUIRE_CALL(steps[0], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[1], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[2], execute()).RETURN(cet::Result::Pass);

    cet::StepExecutor se;
    CHECK(se.executeSteps(steps) == cet::Result::Pass);
}

TEST_CASE("Execute returns failure if one step failed", "[StepExecutorTest]")
{
    std::vector<StepMock> steps{3};
    REQUIRE_CALL(steps[0], execute()).RETURN(cet::Result::Pass);
    REQUIRE_CALL(steps[1], execute()).RETURN(cet::Result::Fail);
    REQUIRE_CALL(steps[2], execute()).RETURN(cet::Result::Pass);

    cet::StepExecutor se;
    CHECK(se.executeSteps(steps) == cet::Result::Fail);
}
