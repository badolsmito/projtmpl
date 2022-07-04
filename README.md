# ProjTmpl

ProjTmpl is a tool that allows the quick and easy set up of projects using an easy-to-configure TOML file for templates.  
You can create your own templates by adding a table with the name that you wish to use and add the variables found in default  
and change their values. To use your template, simply pass its name as an argument when using ProjTmpl.  

## Dependencies

ProjTmpl uses the following dependencies:
  - [{fmt}](https://github.com/fmtlib/fmt) for I/O
  - [toml11](https://github.com/ToruNiina/toml11) for parsing and working with TOML files

If you do not have {fmt} installed in your system, you will have to install it manually. Note that I'm developing on Ubuntu 22.

## License

ProjTmpl is licensed under the GPLv2