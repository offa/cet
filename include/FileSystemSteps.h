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

#include "TestStep.h"
#include <filesystem>
#include <vector>
#include <algorithm>

namespace cet
{
    class FileStep : public TestStep
    {
    public:
        explicit FileStep(std::filesystem::path file);

        Result execute() const override;
        std::string describe() const override;

    private:
        std::filesystem::path file_;
    };


    class DirectoryStep : public TestStep
    {
    public:
        explicit DirectoryStep(std::filesystem::path file);

        Result execute() const override;
        std::string describe() const override;

    private:
        std::filesystem::path file_;
    };

}
