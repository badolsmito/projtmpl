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
// TODO: Guards preventing the overwriting of files and folders without intention. Use command-line arguments to allow it.

#define FMT_HEADER_ONLY 
#include "fmt/core.h"
#include "fmt/color.h"
#include "toml.hpp"

#include <cstdlib>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char **argv) {

    auto data = toml::parse("/usr/local/bin/main.toml");
    
    const auto tmplt = toml::find(data, argv[1]);

    /*
        This piece of block essentially extracts the directories list in the toml file and loops over it, creating
        directories with the corresponding name.
    */
    std::vector<std::string> directories = toml::get<std::vector<std::string>>(toml::find(tmplt, "directories"));
    for (const auto &i : directories) {
        fs::create_directory(i);
        fmt::print(fg(fmt::color::light_green), "Directory {} created!\n", i);
    }

    std::vector<std::array<std::string, 2>> files = toml::get<std::vector<std::array<std::string, 2>>>(toml::find(tmplt, "files"));
    for (const auto &i : files) {
        std::ofstream j(i[0]); // Creates a file with the first item of i, which is the name for the file
        j << i[1]; // The actual contents get written into that file.
        j.close();
        fmt::print(fg(fmt::color::light_green), "File {} created!\n", i[0]);
    }

    std::vector<std::string> commands = toml::get<std::vector<std::string>>(toml::find(tmplt, "commands"));
    for (const auto &i : commands) {
        system(i.data());
        fmt::print(fg(fmt::color::light_green), "Command {} executed!\n", i);
    }
    return 0;
}