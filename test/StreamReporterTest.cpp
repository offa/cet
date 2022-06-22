/*
 * cet - Container Environment Test
 *
 * Copyright (C) 2020-2022  offa
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

#include "StreamReporter.h"
#include <sstream>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Passed test format", "[StreamReporterTest]")
{
    std::ostringstream oss;
    cet::StreamReporter reporter{oss};
    reporter.printResult(cet::Result::Pass, "test case description");

    CHECK(oss.str() == " [PASS] test case description\n");
}

TEST_CASE("Failed test format", "[StreamReporterTest]")
{
    std::ostringstream oss;
    cet::StreamReporter reporter{oss};
    reporter.printResult(cet::Result::Fail, "this failed");

    CHECK(oss.str() == " [FAIL] this failed\n");
}

TEST_CASE("Error format", "[StreamReporterTest]")
{
    std::ostringstream oss;
    cet::StreamReporter reporter{oss};
    reporter.printError("failed by an error");

    CHECK(oss.str() == " [ERROR] failed by an error\n");
}
