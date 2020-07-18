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
#include <algorithm>
#include <yaml-cpp/yaml.h>

namespace cet
{
    namespace
    {
        Config::PathList toPathList(const YAML::Node& node)
        {
            Config::PathList paths;
            std::transform(node.begin(), node.end(), std::back_inserter(paths),
                           [](const auto& value) { return value.template as<std::string>(); });
            return paths;
        }

        std::vector<std::string> toStringList(const YAML::Node& node)
        {
            std::vector<std::string> strings;
            std::transform(node.begin(), node.end(), std::back_inserter(strings),
                           [](const auto& value) { return value.template as<std::string>(); });
            return strings;
        }

        Config fromYamlNode(const YAML::Node& node)
        {
            return Config{toPathList(node["files"]), toPathList(node["directories"]), toStringList(node["envs"])};
        }
    }

    Config::Config(const PathList& files, const PathList& directories, const std::vector<std::string>& envs)
        : files_(files), directories_(directories), envs_(envs)
    {
    }

    const Config::PathList& Config::getFiles() const
    {
        return files_;
    }

    const Config::PathList& Config::getDirectories() const
    {
        return directories_;
    }

    const std::vector<std::string> Config::getEnvs() const
    {
        return envs_;
    }


    Config fromYaml(const std::string& yaml)
    {
        const YAML::Node node = YAML::Load(yaml);
        return fromYamlNode(node);
    }

    Config fromYamlFile(const std::string& fileName)
    {
        const YAML::Node node = YAML::LoadFile(fileName);
        return fromYamlNode(node);
    }

}
