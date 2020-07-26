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

#include "EnvStep.h"
#include <cstdlib>

namespace cet
{
    EnvStep::EnvStep(const std::string& name, std::optional<std::string> value)
        : name_(name), value_(value)
    {
    }

    Result EnvStep::execute() const
    {
        if (const auto envValue = std::getenv(name_.c_str()); envValue != nullptr)
        {
            if (value_)
            {
                return envValue == *value_ ? Result::Pass : Result::Fail;
            }
            return Result::Pass;
        }
        return Result::Fail;
    }

    std::string EnvStep::describe() const
    {
        std::string msg = "Env exists: " + name_;

        if (value_)
        {
            msg += " = '" + value_.value() + "'";
        }
        return msg;
    }

    std::string EnvStep::getName() const
    {
        return name_;
    }

    std::optional<std::string> EnvStep::getValue() const
    {
        return value_;
    }

    void EnvStep::setValue(const std::string& value)
    {
        value_ = value;
    }
}
