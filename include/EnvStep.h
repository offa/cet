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

#include "TestStep.h"
#include <optional>

namespace cet
{
    class EnvStep : public TestStep
    {
    public:
        explicit EnvStep(const std::string& name, std::optional<std::string> value = {});

        Result execute() const override;
        std::string describe() const override;

        std::string getName() const;
        std::optional<std::string> getValue() const;
        void setValue(const std::string& value);

    private:
        std::string name_;
        std::optional<std::string> value_;
    };
}
