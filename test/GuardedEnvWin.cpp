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


#include "GuardedEnv.h"
#include <cstdlib>

namespace cet::test
{
    void GuardedEnv::setEnv(const std::string& newValue)
    {
        ::_putenv_s(name_.c_str(), newValue.c_str());
    }

    void GuardedEnv::clearEnv()
    {
        ::_putenv_s(name_.c_str(), "");
    }

}
