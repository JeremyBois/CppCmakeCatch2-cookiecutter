cmake_minimum_required(VERSION 3.3.0 FATAL_ERROR)
project("{{ cookiecutter.project_name }}-app")


# ------------------------------------------------------------------------------
# Samples EXE
# ------------------------------------------------------------------------------
file(
    GLOB
    app_SOURCES
    ${PROJECT_SOURCE_DIR}/src/*
)
add_executable(
    {{ cookiecutter.project_name }}-app ${app_SOURCES}
)


# See https://cmake.org/pipermail/cmake/2016-May/063400.html
if ({{ cookiecutter.project_name_upper }}_BUILD_SHARED_LIBS)
    # Shared lib need to know includes directories
    message(VERBOSE "Using shared library.")
    target_include_directories({{ cookiecutter.project_name }}-app
        PRIVATE
            ${CMAKE_SOURCE_DIR}/{{ cookiecutter.project_name }}/src
            ${PROJECT_SOURCE_DIR}/src
    )

    # Set pre processor command for Shared lib import
    target_compile_definitions({{ cookiecutter.project_name }}-app
    PRIVATE
        {{ cookiecutter.project_name_upper }}_SHARED="USED"
    )
else()
    message(VERBOSE "Using static library.")
    target_include_directories({{ cookiecutter.project_name }}-app
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src
    )
endif()


set_target_properties({{ cookiecutter.project_name }}-app
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/${CMAKE_GENERATOR_PLATFORM}/App/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/${CMAKE_GENERATOR_PLATFORM}/App/"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_GENERATOR_PLATFORM}/App/"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    LINKER_LANGUAGE CXX
)

# Using dynamic or static lib based on previous flag (see {{ cookiecutter.project_name_upper }}_BUILD_SHARED_LIBS)
target_link_libraries({{ cookiecutter.project_name }}-app
    PRIVATE
      {{ cookiecutter.project_name }}::{{ cookiecutter.project_name }}
)

