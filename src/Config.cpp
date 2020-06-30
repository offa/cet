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
    Config fromYaml(const std::string& yaml)
    {
        const YAML::Node node = YAML::Load(yaml);

        Config::PathList files;
        const auto filesEntry = node["files"];
        std::transform(filesEntry.begin(), filesEntry.end(), std::back_inserter(files), [](const auto& value) { return value.template as<std::string>(); });


        Config::PathList dirs;
        const auto directoriesEntry = node["directories"];
        std::transform(directoriesEntry.begin(), directoriesEntry.end(), std::back_inserter(dirs), [](const auto& value) { return value.template as<std::string>(); });

        return Config{files, dirs};
    }
}
