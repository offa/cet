/*
 * cet - Container Environment Test
 *
 * Copyright (C) 2020-2021  offa
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

#include <string>

namespace cet::test
{
    class GuardedEnv
    {
    public:
        GuardedEnv(const std::string& name, const std::string& value)
            : name_(name), value_(value)
        {
            setEnv(value_);
        }

        ~GuardedEnv()
        {
            clearEnv();
        }

        GuardedEnv(const GuardedEnv&) = delete;
        GuardedEnv(GuardedEnv&&) = delete;

        void reset(const std::string& newValue)
        {
            value_ = newValue;
            setEnv(value_);
        }


        GuardedEnv& operator=(const GuardedEnv&) = delete;
        GuardedEnv& operator=(GuardedEnv&&) = delete;

    private:
        void setEnv(const std::string& newValue);
        void clearEnv();

        std::string name_;
        std::string value_;
    };
}
