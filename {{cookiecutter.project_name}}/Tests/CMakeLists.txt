cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
project("{{ cookiecutter.project_name }}-tests")


# ------------------------------------------------------------------------------
# Engine TESTS
# ------------------------------------------------------------------------------
add_subdirectory(${PROJECT_SOURCE_DIR}/vendors/Catch2)

list(APPEND tests_SOURCES
    ${PROJECT_SOURCE_DIR}/src/CatchMain.cpp
)

add_executable({{ cookiecutter.project_name }}-testing ${tests_SOURCES})

if ({{ cookiecutter.project_name_upper }}_BUILD_SHARED_LIBS)
    message(VERBOSE "Using shared library.")
    target_include_directories({{ cookiecutter.project_name }}-testing
        PRIVATE
            ${CMAKE_SOURCE_DIR}/{{ cookiecutter.project_name }}/src
            ${PROJECT_SOURCE_DIR}/src
    )

    # Set pre processor command for Shared lib import
    target_compile_definitions({{ cookiecutter.project_name }}-testing
    PRIVATE
        {{ cookiecutter.project_name_upper }}_SHARED="USED"
    )
else()
    message(VERBOSE "Using static library.")
    target_include_directories({{ cookiecutter.project_name }}-testing
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src
    )
endif()


set_target_properties({{ cookiecutter.project_name }}-testing
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/${CMAKE_GENERATOR_PLATFORM}/Tests/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}/${CMAKE_GENERATOR_PLATFORM}/Tests/"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_GENERATOR_PLATFORM}/Tests/"
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    LINKER_LANGUAGE CXX
)

target_link_libraries({{ cookiecutter.project_name }}-testing
    PRIVATE
        {{ cookiecutter.project_name }}::{{ cookiecutter.project_name }}
        Catch2::Catch2
)
