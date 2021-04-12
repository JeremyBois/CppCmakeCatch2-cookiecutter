#ifndef __PLATFORM__HPP
#define __PLATFORM__HPP

// More at
// https://cmake.org/Wiki/BuildingWinDLL
// https://gcc.gnu.org/wiki/Visibility


// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
    #if defined __MINGW32__
        // GCC with MINGW
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
    #else
        // Windows
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_IMPORT __declspec(dllimport)
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_EXPORT __declspec(dllexport)
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_LOCAL
#endif
#else
    #if __GNUC__ >= 4
        // GCC
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
    #else
        // GCC does not support __attribute__ before version 4.
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_IMPORT
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_EXPORT
        #define {{cookiecutter.project_name_upper}}_HELPER_DLL_LOCAL
    #endif
#endif

// Now we use the generic helper definitions above to define {{cookiecutter.project_name_upper}}_API and {{cookiecutter.project_name_upper}}_LOCAL.
// {{cookiecutter.project_name_upper}}_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// {{cookiecutter.project_name_upper}}_LOCAL is used for non-api symbols.
#ifdef {{cookiecutter.project_name_upper}}_SHARED              // Defined if {{cookiecutter.project_name_upper}} is compiled as a DLL
    #ifdef {{cookiecutter.project_name_upper}}_SHARED_EXPORTS  // Defined if we are building the {{cookiecutter.project_name_upper}} DLL (instead of using it)
        #define {{cookiecutter.project_name_upper}}_API {{cookiecutter.project_name_upper}}_HELPER_DLL_EXPORT
    #else
        #define {{cookiecutter.project_name_upper}}_API {{cookiecutter.project_name_upper}}_HELPER_DLL_IMPORT
    #endif // {{cookiecutter.project_name_upper}}_SHARED_EXPORTS
    #define {{cookiecutter.project_name_upper}}_LOCAL {{cookiecutter.project_name_upper}}_HELPER_DLL_LOCAL
#else  // {{cookiecutter.project_name_upper}}_SHARED is not defined: this means {{cookiecutter.project_name_upper}} is a STATIC lib.
    #define {{cookiecutter.project_name_upper}}_API
    #define {{cookiecutter.project_name_upper}}_LOCAL
#endif // {{cookiecutter.project_name_upper}}_SHARED


// Compile time hash function that works also for template function
// as opposed to __func__ that only extract function name
#if defined _MSC_VER
    #define FUNC_NAME __FUNCSIG__
#elif defined __clang__ || (defined __GNUC__)
    #define FUNC_NAME __PRETTY_FUNCTION__
#endif


// Allow to test current platform at compile time
#define {{cookiecutter.project_name_upper}}_PLATFORM_WINDOWS  1
#define {{cookiecutter.project_name_upper}}_PLATFORM_MAC      2
#define {{cookiecutter.project_name_upper}}_PLATFORM_UNIX     3

#if defined _WIN32 || (defined __CYGWIN__)
    #define {{cookiecutter.project_name_upper}}_PLATFORM {{cookiecutter.project_name_upper}}_PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define {{cookiecutter.project_name_upper}}_PLATFORM {{cookiecutter.project_name_upper}}_PLATFORM_MAC
#else
    #define {{cookiecutter.project_name_upper}}_PLATFORM {{cookiecutter.project_name_upper}}_PLATFORM_UNIX
#endif

#endif
