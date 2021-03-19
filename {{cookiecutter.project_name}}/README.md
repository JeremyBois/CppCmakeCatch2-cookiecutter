# {{ cookiecutter.project_name }}

Welcome to {{ cookiecutter.project_name }}  a {{ cookiecutter.author }}'s project !

## Getting started !
### Building this project
Using *make* as a build tool the following commands can be used to generate the build files:
```bash
# DEFAULT behavior
# Lib + App
cmake -G "Unix Makefiles" -B "./build" -S "."

# Lib + App + Tests
cmake -G "Unix Makefiles" -B "./build" -S "." -D {{ cookiecutter.project_name_upper }}_BUILD_TESTING=ON
```

Default build target is `Release` but this can be change by explicitly setting the required build type using `-D CMAKE_BUILD_TYPE=Debug` or `-D CMAKE_BUILD_TYPE=Debug` when calling *Cmake*
```bash
# DEFAULT behavior
# Lib + App as Release
cmake -G "Unix Makefiles" -B "./build" -S "." -D CMAKE_BUILD_TYPE=Release

# Lib + App as Debug
cmake -G "Unix Makefiles" -B "./build" -S "." -D CMAKE_BUILD_TYPE=Debug
```

Default library target type is `Static` but this can be changed by explicitly setting the required libray target type using `-D {{ cookiecutter.project_name_upper }}_BUILD_SHARED_LIBS=ON` or `-D {{ cookiecutter.project_name_upper }}_BUILD_SHARED_LIBS=OFF` when calling *Cmake*
```bash
# DEFAULT behavior
# Lib as STATIC library + App
cmake -G "Unix Makefiles" -B "./build" -S "." -D {{ cookiecutter.project_name_upper }}_BUILD_SHARED_LIBS=OFF

# Lib as SHARED library + App
cmake -G "Unix Makefiles" -B "./build" -S "." -D {{ cookiecutter.project_name_upper }}_BUILD_SHARED_LIBS=ON
```


*Cmake* can also be used to run the build using the tool setup in the last step (here `make`) as follow:
```bash
# Incremental build
cmake --build build

# Build from scratch
cmake --build build --clean-first
```



Targets are all moved to the `bin` folder structured and the folder structure is based on `CMAKE_BUILD_TYPE` and target folder name and name.

### Developing using Clangd
If you are using [Clangd](https://clangd.llvm.org/) with *sublime-text* or *vsCode*, the following command will automatically generate the required `compile_commands.json` for you:
```bash
# Lib + App + compile_commands.json
cmake -G "Unix Makefiles" -B "./build" -S "." -D CMAKE_EXPORT_COMPILE_COMMANDS=ON -D {{ cookiecutter.project_name_upper }}_BUILD_TESTING=OFF && compdb -p ./build list > compile_commands.json && cp compile_commands.json ./build/compile_commands.json

# Lib + App + Tests + compile_commands.json
cmake -G "Unix Makefiles" -B "./build" -S "." -D CMAKE_EXPORT_COMPILE_COMMANDS=ON -D {{ cookiecutter.project_name_upper }}_BUILD_TESTING=ON && compdb -p ./build list > compile_commands.json && cp compile_commands.json ./build/compile_commands.json
```


### Running generated targets
To run the application just select one of the following options assuming you are at the project root folder:
```bash
# Run the Debug build with or without valgrind memory checks
./bin/Debug/App/{{ cookiecutter.project_name }}-app
valgrind ./bin/Debug/App/{{ cookiecutter.project_name }}-app

# Run the Release build with or without valgrind memory checks
./bin/Release/App/{{ cookiecutter.project_name }}-app
valgrind ./bin/Release/App/{{ cookiecutter.project_name }}-app
```

Tests use [Catch2](https://github.com/catchorg/Catch2) a modern test suite. To run it you can use the following commands assuming you are at the project root.

```bash
# Run Debug target with or without valgrind memory checks
./bin/Debug/Tests/{{ cookiecutter.project_name }}-testing
valgrind ./bin/Debug/Tests/{{ cookiecutter.project_name }}-testing

# Run Release target with or without valgrind memory checks
./bin/Release/Tests/{{ cookiecutter.project_name }}-testing
valgrind ./bin/Release/Tests/{{ cookiecutter.project_name }}-testing
```

[Catch2](https://github.com/catchorg/Catch2) comes will a lot of options:
  - Generate a report
  - Change verbosity level
  - Run a particular test section
  - ...

As an example the following can be used to run only a specific section with valgrind support:
```bash
valgrind ./bin/Release/Tests/{{ cookiecutter.project_name }}-testing -c <Name_of_section>
```

> First compilation of *Catch2* can take a while, there is nothing wrong with your setup !

### Cleaning
In order to properly clean *Cmake* and *clangd* files the utility provided in `Tools` folder can be used as follow:
```bash
# Clean only Cmake files
./Tools/Purger cmake

# Clean both Cmake and Clangd files
./Tools/Purger cmake clangd
```

This is sometimes required to get a clean working directory and make sure everything works when building from scratch.

> Using the clean command of *Cmake* is not always enough, hence this script !
