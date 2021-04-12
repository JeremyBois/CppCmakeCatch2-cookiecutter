cmake_minimum_required(VERSION 3.3.0 FATAL_ERROR)
PROJECT("{{ cookiecutter.project_name }}")


# ------------------------------------------------------------------------------
# Additionnal Cmake module path for external dependencies search
# ------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake-modules/")



# ------------------------------------------------------------------------------
# Options
# ------------------------------------------------------------------------------
# Allow the developer to select if Dynamic or Static libraries are built
OPTION ({{ cookiecutter.project_name_upper }}_BUILD_SHARED_LIBS "Build Shared Libraries" OFF)



# ------------------------------------------------------------------------------
# Create a static or shared library target.
# ------------------------------------------------------------------------------
if ({{ cookiecutter.project_name_upper }}_BUILD_SHARED_LIBS)
    set ({{ cookiecutter.project_name_upper }}_LIB_NAME {{ cookiecutter.project_name }}-shared)
    set (LIB_TYPE SHARED)  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
else()
    set ({{ cookiecutter.project_name_upper }}_LIB_NAME {{ cookiecutter.project_name }}-static)
    set (LIB_TYPE STATIC)  # Set the LIB_TYPE variable to STATIC
endif ()

# Display information about the build parameters
message(STATUS "{{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME} will be build as ${LIB_TYPE} library (${CMAKE_BUILD_TYPE})")

file(
    GLOB
    {{ cookiecutter.project_name }}_SOURCES
    ${PROJECT_SOURCE_DIR}/src/*
    ${PROJECT_SOURCE_DIR}/src/Core/*
)
add_library({{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME} ${LIB_TYPE} {{ "${" }}{{ cookiecutter.project_name }}_SOURCES})


# See https://cmake.org/pipermail/cmake/2016-May/063400.html
if ({{ cookiecutter.project_name_upper }}_BUILD_SHARED_LIBS)
    # Shared library
    target_include_directories({{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME}
        PRIVATE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    )
    # Set pre processor command for Shared lib export
    target_compile_definitions({{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME}
    PRIVATE
        {{ cookiecutter.project_name_upper }}_SHARED="USED"
        {{ cookiecutter.project_name_upper }}_SHARED_EXPORTS="USED"
    )
else()
    # Static library
    target_include_directories({{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    )
endif()




set_target_properties({{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/${CMAKE_GENERATOR_PLATFORM}/${PROJECT_NAME}/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/${CMAKE_GENERATOR_PLATFORM}/${PROJECT_NAME}/"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_GENERATOR_PLATFORM}/${PROJECT_NAME}/"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    LINKER_LANGUAGE CXX

    # https://gcc.gnu.org/wiki/Visibility
    # https://github.com/elucideye/drishti/issues/225
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

# Read only alias
add_library({{ cookiecutter.project_name }}::{{ cookiecutter.project_name }} ALIAS {{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME})




# ------------------------------------------------------------------------------
# Build options based on platform (Windows, Unix)
# ------------------------------------------------------------------------------
if (MSVC)
    # warning level 4 and all warnings as errors
    target_compile_options({{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME}
        PRIVATE
            /W4
            # /WX
    )
    target_link_options({{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME}
        PUBLIC
            -MACHINE:x64
    )
else()
    # lots of warnings and all warnings as errors
    target_compile_options({{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME}
        PRIVATE
            -Wall -Wextra -pedantic -Wwrite-strings
            -Wno-parentheses -Warray-bounds -Weffc++ -Wstrict-aliasing
            # -Werror
        PUBLIC
            -m64
    )
endif()


# ------------------------------------------------------------------------------
# Add a list of header files to precompile.
# https://cmake.org/cmake/help/latest/command/target_precompile_headers.html
# ------------------------------------------------------------------------------
target_precompile_headers({{ "${" }}{{ cookiecutter.project_name_upper }}_LIB_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/{{ cookiecutter.project_name }}PCH.hpp
)
