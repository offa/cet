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

#include <argparse/argparse.hpp>

int main(int argc, char* argv[])
{
    argparse::ArgumentParser argParser{"cet"};
    argParser.add_argument("config").default_value(std::string{"cet.yml"});

    try
    {
        argParser.parse_args(argc, argv);
    }
    catch (const std::runtime_error& ex)
    {
        std::cout << ex.what() << "\n";
        std::cout << argParser;
        return 1;
    }

    return 0;
}
