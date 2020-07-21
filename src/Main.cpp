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

#include "Version.h"
#include "Config.h"
#include "FileSystemSteps.h"
#include "EnvStep.h"
#include "StepExecutor.h"
#include "StreamReporter.h"
#include <optional>
#include <argparse/argparse.hpp>

namespace
{
    std::optional<argparse::ArgumentParser> parseArguments(int argc, char* argv[])
    {
        argparse::ArgumentParser argParser{"cet"};
        argParser.add_argument("config").default_value(std::string{"cet.yml"});
        argParser.add_argument("--version").default_value(false).implicit_value(true);

        try
        {
            argParser.parse_args(argc, argv);
        }
        catch (const std::runtime_error& ex)
        {
            std::cout << ex.what() << "\n"
                      << argParser;
            return {};
        }
        return argParser;
    }

    template <class... Results>
    constexpr int getExitCode(Results... results)
    {
        return ((results == cet::Result::Pass) && ...) ? 0 : 1;
    }

    template <class... StepLists>
    int execute(cet::StepExecutor& e, StepLists... stepLists)
    {
        return getExitCode((e.executeSteps(stepLists), ...));
    }
}

int main(int argc, char* argv[])
{
    auto args = parseArguments(argc, argv);

    if (!args)
    {
        return 1;
    }

    if (args->get<bool>("--version"))
    {
        std::cout << "cet v" << cet::version() << "\n";
        return 0;
    }

    const auto config = cet::fromYamlFile(args->get<std::string>("config"));

    cet::StepExecutor executor{std::make_unique<cet::StreamReporter>(std::cout)};
    return execute(executor, config.getFiles(), config.getDirectories(), config.getEnvs());
}
