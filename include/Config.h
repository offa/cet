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

#pragma once

#include <vector>
#include <filesystem>

namespace cet
{
    class Config
    {
    public:
        using PathList = std::vector<std::filesystem::path>;

        Config(const PathList& files, const PathList& directories)
            : files_(files), directories_(directories)
        {
        }

        const PathList& getFiles() const
        {
            return files_;
        }

        const PathList& getDirectories() const
        {
            return directories_;
        }

    private:
        PathList files_;
        PathList directories_;
    };

    Config fromYaml(const std::string& yaml);
    Config fromYamlFile(const std::string& fileName);
}
