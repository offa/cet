/*
 * cet - Container Environment Test
 *
 * Copyright (C) 2020-2022  offa
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

        template <class Container, std::enable_if_t<std::is_base_of_v<TestStep, typename Container::value_type>, int> = 0>
        Result executeSteps(const Container& steps) const
        {
            const auto failedSteps = std::count_if(std::cbegin(steps), std::cend(steps), [this](const auto& step) {
                try
                {
                    const auto result = step.execute();
                    reporter_->printResult(result, step.describe());
                    return result != Result::Pass;
                }
                catch (const std::exception& ex)
                {
                    reporter_->printError(ex.what());
                }
                return true;
            });

            return failedSteps == 0 ? Result::Pass : Result::Fail;
        }

    private:
        std::unique_ptr<Reporter> reporter_;
    };


    template <class... StepLists>
    Result executeAll(const cet::StepExecutor& executor, StepLists... stepLists)
    {
        std::size_t failed{0};
        auto collect = [&failed, &executor](const auto& steps) {
            failed += (executor.executeSteps(steps) != cet::Result::Pass);
        };
        (collect(std::forward<StepLists>(stepLists)), ...);

        return (failed == 0 ? Result::Pass : Result::Fail);
    }

}
