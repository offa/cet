/*
 * cet - Container Environment Test
 *
 * Copyright (C) 2020-2025  offa
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

#include "Version.h"
#include "Config.h"
#include "FileSystemSteps.h"
#include "EnvStep.h"
#include "StepExecutor.h"
#include "StreamReporter.h"
#include <vector>
#include <optional>
#include <argparse/argparse.hpp>

namespace
{
    std::optional<std::string> parseArguments(const std::vector<std::string>& args)
    {
        argparse::ArgumentParser argParser{"cet", cet::version()};
        argParser.add_argument("config").default_value(std::string{"cet.yml"});

        try
        {
            argParser.parse_args(args);
        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what() << "\n"
                      << argParser;
            return {};
        }
        return argParser.get<std::string>("config");
    }

    std::optional<cet::Config> loadConfig(const std::string& fileName)
    {
        try
        {
            return cet::fromYamlFile(fileName);
        }
        catch (const std::exception& ex)
        {
            std::cout << "ERROR: " << ex.what() << "\n";
            return {};
        }
    }

    constexpr int toExitCode(cet::Result result)
    {
        return result == cet::Result::Pass ? 0 : 1;
    }

}

int main(int argc, char* argv[])
{
    auto args = parseArguments({argv, argv + argc});

    if (!args)
    {
        return 1;
    }

    const auto config = loadConfig(*args);

    if (!config)
    {
        return 1;
    }

    const cet::StepExecutor executor{std::make_unique<cet::StreamReporter>(std::cout)};
    return toExitCode(cet::executeAll(executor, config->getFiles(), config->getDirectories(), config->getEnvs()));
}
