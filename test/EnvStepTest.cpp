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

#include "EnvStep.h"
#include <catch2/catch.hpp>

TEST_CASE("Env step describes step", "[EnvStepTest]")
{
    cet::EnvStep es{"ENV_VAR_1"};
    CHECK(es.describe() == "Env exists: ENV_VAR_1");
}

TEST_CASE("Env step tests existence of env", "[EnvStepTest]")
{
    cet::EnvStep ex{"UNIT_TEST_ENV_STEP_VAR_1"};
    CHECK(ex.execute() == cet::Result::Fail);
    setenv("UNIT_TEST_ENV_STEP_VAR_1", "test", 1);
    CHECK(ex.execute() == cet::Result::Pass);
}

TEST_CASE("Env steps from names", "[EnvStepTest]")
{
    using namespace Catch::Matchers;
    const std::vector<std::string> names{"ENV_1", "ENV_2"};
    const auto steps = cet::envStepsFromNames(names);

    CHECK(steps.size() == 2);
    CHECK_THAT(steps[0].describe(), Contains("ENV_1"));
    CHECK_THAT(steps[1].describe(), Contains("ENV_2"));
}

TEST_CASE("Env steps from names returns empty if no names", "[EnvStepTest]")
{
    const auto steps = cet::envStepsFromNames({});
    CHECK(steps.size() == 0);
}
