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
#include "Reporter.h"
#include <algorithm>
#include <type_traits>
#include <memory>

namespace cet
{

    class StepExecutor
    {
    public:
        explicit StepExecutor(std::unique_ptr<Reporter> reporter)
            : reporter_(std::move(reporter))
        {
        }

        template <class C, std::enable_if_t<std::is_base_of_v<TestStep, typename C::value_type>, int> = 0>
        Result executeSteps(const C& steps)
        {
            std::size_t failedSteps{0};

            std::for_each(std::cbegin(steps), std::cend(steps), [this, &failedSteps](const auto& step) {
                const auto result = step.execute();

                if (result != Result::Pass)
                {
                    ++failedSteps;
                }

                reporter_->printResult(result, step.describe());
            });

            return failedSteps == 0 ? Result::Pass : Result::Fail;
        }

    private:
        std::unique_ptr<Reporter> reporter_;
    };
}
