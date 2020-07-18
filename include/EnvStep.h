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

#include "TestStep.h"
#include <vector>
#include <algorithm>
#include <cstdlib>

namespace cet
{
    class EnvStep : public TestStep
    {
    public:
        explicit EnvStep(const std::string& name)
            : name_(name)
        {
        }

        Result execute() const override
        {
            if (std::getenv(name_.c_str()))
            {
                return Result::Pass;
            }
            return Result::Fail;
        }

        std::string describe() const override
        {
            return "Env exists: " + name_;
        };

    private:
        std::string name_;
    };

    std::vector<EnvStep> envStepsFromNames(const std::vector<std::string>& names)
    {
        std::vector<EnvStep> result;
        result.reserve(names.size());
        std::transform(names.cbegin(), names.cend(), std::back_inserter(result), [](const auto& e) { return EnvStep{e}; });
        return result;
    }
}
