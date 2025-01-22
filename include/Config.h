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

#pragma once

#include "FileSystemSteps.h"
#include "EnvStep.h"
#include <vector>

namespace cet
{
    class Config
    {
    public:
        Config(const std::vector<FileStep>& files, const std::vector<DirectoryStep>& directories, const std::vector<EnvStep>& envs);

        const std::vector<FileStep>& getFiles() const;
        const std::vector<DirectoryStep>& getDirectories() const;
        const std::vector<EnvStep>& getEnvs() const;

    private:
        std::vector<FileStep> files_;
        std::vector<DirectoryStep> directories_;
        std::vector<EnvStep> envs_;
    };

    Config fromYaml(const std::string& yaml);
    Config fromYamlFile(const std::string& fileName);
}
