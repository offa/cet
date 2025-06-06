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

#include "StreamReporter.h"
#include <ostream>

namespace cet
{
    StreamReporter::StreamReporter(std::ostream& stream)
        : stream_(stream)
    {
    }

    void StreamReporter::printResult(Result result, const std::string& description)
    {
        stream_ << (result == Result::Pass ? " [PASS] " : " [FAIL] ") << description << "\n";
    }

    void StreamReporter::printError(const std::string& message)
    {
        stream_ << " [ERROR] " << message << "\n";
    }
}
