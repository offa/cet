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

#include "Config.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using Catch::Matchers::Message;
using Catch::Matchers::ContainsSubstring;

TEST_CASE("Parse config throws on empty config", "[ConfigTest]")
{
    CHECK_THROWS_MATCHES(cet::fromYaml(""), std::runtime_error, Message("Configuration is empty"));
    CHECK_THROWS_MATCHES(cet::fromYaml("# empty"), std::runtime_error, Message("Configuration is empty"));
}

TEST_CASE("Parse config files entries", "[ConfigTest]")
{
    const auto config = cet::fromYaml("files:\n - /tmp/file1\n - /tmp/dir/file2");
    const auto& files = config.getFiles();

    CHECK(files.size() == 2);
    CHECK_THAT(files[0].describe(), ContainsSubstring("/tmp/file1"));
    CHECK_THAT(files[1].describe(), ContainsSubstring("/tmp/dir/file2"));
}

TEST_CASE("Parse config directories entries", "[ConfigTest]")
{
    const auto config = cet::fromYaml("directories:\n - /tmp/dir/x/\n - /tmp/dir2/y\n - /tmp/dir_3/zzzz");
    const auto& dirs = config.getDirectories();

    CHECK(dirs.size() == 3);
    CHECK_THAT(dirs[0].describe(), ContainsSubstring("/tmp/dir/x/"));
    CHECK_THAT(dirs[1].describe(), ContainsSubstring("/tmp/dir2/y"));
    CHECK_THAT(dirs[2].describe(), ContainsSubstring("/tmp/dir_3/zzzz"));
}

TEST_CASE("Parse config envs entries", "[ConfigTest]")
{
    const auto config = cet::fromYaml("envs:\n - AAA\n - BBB_BBB\n - name: CCC\n");
    const auto& envs = config.getEnvs();

    CHECK(envs.size() == 3);
    CHECK(envs[0].getName() == "AAA");
    CHECK(envs[1].getName() == "BBB_BBB");
    CHECK(envs[2].getName() == "CCC");
}

TEST_CASE("Parse config env entries with value", "[ConfigTest]")
{
    const auto config = cet::fromYaml("envs:\n - name: AAA\n   value: 123\n - name: BBB\n   value: ccc\n");
    const auto& envs = config.getEnvs();

    CHECK(envs.size() == 2);
    CHECK(envs[0].getName() == "AAA");
    CHECK(*envs[0].getValue() == "123");
    CHECK(envs[1].getName() == "BBB");
    CHECK(*envs[1].getValue() == "ccc");
}

TEST_CASE("Parse config with multiple types", "[ConfigTest]")
{
    const auto config = cet::fromYaml("files:\n - file1\n - file2\n - file3\n"
                                      "directories:\n - dir1\n - dir2\n"
                                      "envs:\n - ENV_1\n - name: ENV_2\n   value: env2 value");

    const auto& files = config.getFiles();
    CHECK(files.size() == 3);
    CHECK_THAT(files[0].describe(), ContainsSubstring("file1"));
    CHECK_THAT(files[1].describe(), ContainsSubstring("file2"));
    CHECK_THAT(files[2].describe(), ContainsSubstring("file3"));

    const auto& dirs = config.getDirectories();
    CHECK(dirs.size() == 2);
    CHECK_THAT(dirs[0].describe(), Catch::Matchers::ContainsSubstring("dir1"));
    CHECK_THAT(dirs[1].describe(), Catch::Matchers::ContainsSubstring("dir2"));

    const auto& envs = config.getEnvs();
    CHECK(envs.size() == 2);
    CHECK(envs[0].getName() == "ENV_1");
    CHECK(envs[1].getName() == "ENV_2");
    CHECK(*envs[1].getValue() == "env2 value");
}
