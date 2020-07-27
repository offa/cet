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
#include "GuardedEnv.h"
#include <catch2/catch.hpp>

TEST_CASE("Env step without value", "[EnvStepTest]")
{
    cet::EnvStep es{"ENV_VAR_0"};
    CHECK(es.getName() == "ENV_VAR_0");
    CHECK(es.getValue().has_value() == false);
}

TEST_CASE("Env step with value", "[EnvStepTest]")
{
    cet::EnvStep es{"ENV_VAR_0", "env_value_0"};
    CHECK(es.getName() == "ENV_VAR_0");
    CHECK(*es.getValue() == "env_value_0");
}

TEST_CASE("Env step describes step", "[EnvStepTest]")
{
    cet::EnvStep noValue{"ENV_VAR_1"};
    CHECK(noValue.describe() == "Env exists: ENV_VAR_1");

    cet::EnvStep withValue{"ENV_VAR_2", "value2"};
    CHECK(withValue.describe() == "Env exists: ENV_VAR_2 = 'value2'");
}

TEST_CASE("Env step tests existence of env", "[EnvStepTest]")
{
    cet::EnvStep ex{"UNIT_TEST_ENV_STEP_VAR_1"};
    CHECK(ex.execute() == cet::Result::Fail);
    cet::test::GuardedEnv env{"UNIT_TEST_ENV_STEP_VAR_1", "test"};
    CHECK(ex.execute() == cet::Result::Pass);
}

TEST_CASE("Env step with value tests existence of env with value", "[EnvStepTest]")
{
    cet::test::GuardedEnv env{"UNIT_TEST_ENV_STEP_VAR_2", "<wrong value>"};

    cet::EnvStep ex{"UNIT_TEST_ENV_STEP_VAR_2", "correct value"};
    CHECK(ex.execute() == cet::Result::Fail);
    env.reset("correct value");
    CHECK(ex.execute() == cet::Result::Pass);
}
