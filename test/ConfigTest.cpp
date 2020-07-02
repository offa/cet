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

#include "Config.h"
#include <catch2/catch.hpp>

using namespace Catch::Matchers;

TEST_CASE("Parse config files entries", "[ConfigTest]")
{
    const auto config = cet::fromYaml("files:\n - /tmp/file1\n - /tmp/dir/file2");
    const auto files = config.getFiles();

    CHECK(files.size() == 2);
    CHECK_THAT(files[0], Equals("/tmp/file1"));
    CHECK_THAT(files[1], Equals("/tmp/dir/file2"));
}

TEST_CASE("Parse config files returns empty if no entries", "[ConfigTest]")
{
    const auto config = cet::fromYaml("# Nothing");
    const auto files = config.getFiles();

    CHECK(files.size() == 0);
}

TEST_CASE("Parse config directories entries", "[ConfigTest]")
{
    const auto config = cet::fromYaml("directories:\n - /tmp/dir/x/\n - /tmp/dir2/y\n - /tmp/dir_3/zzzz");
    const auto files = config.getDirectories();

    CHECK(files.size() == 3);
    CHECK_THAT(files[0], Equals("/tmp/dir/x/"));
    CHECK_THAT(files[1], Equals("/tmp/dir2/y"));
    CHECK_THAT(files[2], Equals("/tmp/dir_3/zzzz"));
}

TEST_CASE("Parse config directories returns empty if no entries", "[ConfigTest]")
{
    const auto config = cet::fromYaml("# Nothing");
    const auto dirs = config.getDirectories();

    CHECK(dirs.size() == 0);
}

TEST_CASE("Parse config with multiple types", "[ConfigTest]")
{
    const auto config = cet::fromYaml("files:\n - file1\n - file2\n - file3\n"
                                      "directories:\n - dir1\n - dir2\n");

    const auto files = config.getFiles();
    CHECK(files.size() == 3);
    CHECK_THAT(files[0], Equals("file1"));
    CHECK_THAT(files[1], Equals("file2"));
    CHECK_THAT(files[2], Equals("file3"));

    const auto dirs = config.getDirectories();
    CHECK(dirs.size() == 2);
    CHECK_THAT(dirs[0], Equals("dir1"));
    CHECK_THAT(dirs[1], Equals("dir2"));
}
