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
#include <algorithm>

namespace cet
{
    FileStep::FileStep(std::filesystem::path file)
        : file_(file)
    {
    }

    Result FileStep::execute() const
    {
        if (std::filesystem::is_regular_file(file_))
        {
            return Result::Pass;
        }
        return Result::Fail;
    }

    std::string FileStep::describe() const
    {
        return "File exists: " + file_.string();
    }


    DirectoryStep::DirectoryStep(std::filesystem::path file)
        : file_(file)
    {
    }

    Result DirectoryStep::execute() const
    {
        if (std::filesystem::is_directory(file_))
        {
            return Result::Pass;
        }
        return Result::Fail;
    }

    std::string DirectoryStep::describe() const
    {
        return "Directory exists: " + file_.string();
    }

}
