/*
 * cet - Container Environment Test
 *
 * Copyright (C) 2020-2024  offa
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
#include <string>

namespace cet
{

    class Reporter
    {
    public:
        virtual ~Reporter() = default;

        virtual void printResult(Result result, const std::string& description) = 0;
        virtual void printError(const std::string& message) = 0;
    };

}
