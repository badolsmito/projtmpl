/*
ProjTmpl easily sets up a software project based on a modifiable template
Copyright (C) 2022  Pedro Francisco Carlos Braz

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

// TODO: Add notice when interacting with the program as described in
// https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html#SEC4
// TODO: Add success/fail messages based on the absence/presence of errors returned
// at run-time

#define FMT_HEADER_ONLY 
#include "fmt/core.h"
#include "fmt/color.h"
#include "argh.h"
#include "toml.hpp"

#include <cstdlib>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char **argv) {

    auto data = toml::parse("../config/main.toml");
    std::vector<std::string> directories = toml::find<std::vector<std::string>(data, "directories");
    
    for (const auto &i : directories) {
        fs::create_directory(i);
        fmt::print(fg(fmt::color::light_green), "Directory {} created!\n", i);
    }

    return 0;
}