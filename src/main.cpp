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

#include "toml.hpp"
#include "argh.h"

#include <cstdlib>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char **argv) {

    std::cout << "This program is licensed under the GPLv2.\n"
              << "For more information and the terms of this license, visit <https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html>";

    argh::parser cmdl(argv);
    char inpt;
    if(!cmdl[{"-ao", "--allow-overwrite"}]) {
        std::cout << "\n\nBy using this program, the overwriting of certain folders and files may occur.\nDo you still wish to proceed?(y/n)";
        std::cin >> inpt;
        if (inpt == 'y') {}
        else { return 1; } // To guarantee folder and file safety, anything other than 'y' will have the program exit.
    }

    auto data = toml::parse("/usr/local/bin/main.toml");
    std::string template_name;
    if (argc < 2) {
        template_name = "default";
    }
    else {
        template_name = argv[1];
    }
    const auto tmplt = toml::find(data, template_name);

    /*
        This piece of block essentially extracts the directories list in the toml file and loops over it, creating
        directories with the corresponding name.
    */
    std::vector<std::string> directories = toml::get<std::vector<std::string>>(toml::find(tmplt, "directories"));
    for (const auto &i : directories) {
        fs::create_directory(i);
        std::cout << "Directory " << i << " created!\n";
    }

    std::vector<std::array<std::string, 2>> files = toml::get<std::vector<std::array<std::string, 2>>>(toml::find(tmplt, "files"));
    for (const auto &i : files) {
        std::ofstream j(i[0]); // Creates a file with the first item of i, which is the name for the file
        j << i[1]; // The actual contents get written into that file.
        j.close();
        std::cout << "File " << i[0] << "created!\n";
    }

    std::vector<std::string> commands = toml::get<std::vector<std::string>>(toml::find(tmplt, "commands"));
    for (const auto &i : commands) {
        system(i.data());
        std::cout << "Command " << i <<" executed!\n";
    }
    return 0;
}