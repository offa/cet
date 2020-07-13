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

#include "FileSystemSteps.h"
#include <catch2/catch.hpp>

TEST_CASE("File step describes step", "[FileSystemStepsTests]")
{
    cet::FileStep fs{"/tmp/x"};
    CHECK(fs.describe() == "File exists: /tmp/x");
}

TEST_CASE("File steps from paths", "[FileSystemStepsTests]")
{
    using namespace Catch::Matchers;
    const std::vector<std::filesystem::path> paths{"a.txt", "b.txt", "c.txt"};
    const auto steps = cet::fileStepsFromPaths(paths);

    CHECK(steps.size() == 3);
    CHECK_THAT(steps[0].describe(), Contains("a.txt"));
    CHECK_THAT(steps[1].describe(), Contains("b.txt"));
    CHECK_THAT(steps[2].describe(), Contains("c.txt"));
}

TEST_CASE("File steps from paths returns empty if no paths", "[FileSystemStepsTests]")
{
    const auto steps = cet::fileStepsFromPaths({});
    CHECK(steps.size() == 0);
}

TEST_CASE("Directory step describes step", "[FileSystemStepsTests]")
{
    cet::DirectoryStep ds{"/tmp/y/z"};
    CHECK(ds.describe() == "Directory exists: /tmp/y/z");
}

TEST_CASE("Directory steps from paths", "[FileSystemStepsTests]")
{
    using namespace Catch::Matchers;
    const std::vector<std::filesystem::path> paths{"/a/b/c", "./x/", "dir_z"};
    const auto steps = cet::directoryStepsFromPaths(paths);

    CHECK(steps.size() == 3);
    CHECK_THAT(steps[0].describe(), Contains("/a/b/c"));
    CHECK_THAT(steps[1].describe(), Contains("./x/"));
    CHECK_THAT(steps[2].describe(), Contains("dir_z"));
}

TEST_CASE("Directory steps from paths returns empty if no paths", "[FileSystemStepsTests]")
{
    const auto steps = cet::directoryStepsFromPaths({});
    CHECK(steps.size() == 0);
}
