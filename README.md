# CPP-Cmake-Catch2 project template
A skeleton project using [Cookiecutter](https://github.com/cookiecutter/cookiecutter) to quickly generate a ready to go Cpp project using [Cmake](https://cmake.org/) for build generation and [Catch2](https://github.com/catchorg/Catch2) pour unit testing.

Project is initialized as follow:
  - A library named using the provided project name:
    - Support for Static or Dynamic library
    - Support for import/export macro needed for dynamic library import/export
    - Support for pre-compiled headers
    - Support for project namespace
    - Support for header `#include` guards
    - Main Warnings are enabled
    - C++17 project
  - An `App` folder for the executable application:
    - Generated library added as a dependency
    - C++17 project
  - An `Tests` folder with proper linkage
    - Generated library added as a dependency
    - Initialization of `Catch2` provided
    - C++17 project
  - A ready to go Git project
    - Automatically init the project
    - Automatically add [Catch2](https://github.com/catchorg/Catch2) as a sub-module
    - `.gitignore` setup for C++, *Cmake*, Clangd, SublimeText, VsCode
  - A cleaning tool in `Tool` folder (should be ran from project folder)
    - Clean *Cmake* files
    - Clean Clangd files
  - SublimeText setup for C++ and *Cmake*
    - A `.sublime-project`
    - Support for *clangd* enabled using [LSP](https://github.com/sublimelsp/LSP)
    - Support for *clang* formatting with a `.clang-format`
  - A project README file pre-filled for you
    - Instructions about the build process step by step
    - Instructions about how to run tests and application


## Getting started
(1) First install [Cookiecutter](https://github.com/cookiecutter/cookiecutter) using instructions on their [website](https://cookiecutter.readthedocs.io/en/1.7.2/) or using the following commands:

```bash
# On Arch Linux
sudo pacman -S python-cookiecutter

# On any system using pipX
pipx install cookiecutter
```

(2) Download this repository:
```bash
git clone https://github.com/JeremyBois/CppCmakeCatch2-cookiecutter.git
```

(3) Generate a skeleton project using the command line:
```bash
cookiecutter <path_to_local_repository>
```
Some question will be asked (like the project name) that will be used to build the project template as describe [in the introduction](#cpp-cmake-catch2-project-template).

(4) Enjoy !

