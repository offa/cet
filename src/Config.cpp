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
        template <class T, class ConverterFn>
        std::vector<T> convertElements(const YAML::Node& node, ConverterFn converter)
        {
            std::vector<T> elements;
            std::transform(node.begin(), node.end(), std::back_inserter(elements), converter);
            return elements;
        }

        template <class T>
        std::vector<T> toSteps(const YAML::Node& node)
        {
            return convertElements<T>(node, [](const auto& value) { return T{value.template as<std::string>()}; });
        }

        std::vector<EnvStep> parseEnvSteps(const YAML::Node& node)
        {
            return convertElements<EnvStep>(node, [](const auto& element) {
                if (element.IsScalar())
                {
                    return EnvStep{element.template as<std::string>()};
                }

                EnvStep step{element["name"].template as<std::string>()};

                if (element["value"])
                {
                    step.setValue(element["value"].template as<std::string>());
                }
                return step;
            });
        }

        Config fromYamlNode(const YAML::Node& node)
        {
            return Config{toSteps<FileStep>(node["files"]),
                          toSteps<DirectoryStep>(node["directories"]),
                          parseEnvSteps(node["envs"])};
        }
    }

    Config::Config(const std::vector<FileStep>& files, const std::vector<DirectoryStep>& directories, const std::vector<EnvStep>& envs)
        : files_(files), directories_(directories), envs_(envs)
    {
    }

    const std::vector<FileStep>& Config::getFiles() const
    {
        return files_;
    }

    const std::vector<DirectoryStep>& Config::getDirectories() const
    {
        return directories_;
    }

    const std::vector<EnvStep>& Config::getEnvs() const
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
