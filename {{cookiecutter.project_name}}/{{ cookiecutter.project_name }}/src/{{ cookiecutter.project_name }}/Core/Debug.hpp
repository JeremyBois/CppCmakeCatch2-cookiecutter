#ifndef {{ cookiecutter.project_name_upper }}_DEBUG__HPP
#define {{ cookiecutter.project_name_upper }}_DEBUG__HPP

#include <cstdio>

// Add a signal that can be intercepted by the debugger before closing the program
#if defined {{ cookiecutter.project_name_upper }}_DEBUG
#if defined __MINGW32__ || __GNUC__
// Windows + MinGW || Linux
#include <csignal>
#define {{ cookiecutter.project_name_upper }}_DEBUGBREAK() raise(SIGTRAP)
#elif defined _WIN32 || defined __CYGWIN__
// Windows only
#define {{ cookiecutter.project_name_upper }}_DEBUGBREAK() __debugbreak()
#else
// Not yet supported
#define {{ cookiecutter.project_name_upper }}_DEBUGBREAK() (void)0
#endif

#define ASSERT_DEBUG(condition, message)                                                           \
    do {                                                                                           \
        if (!(condition))                                                                          \
        {                                                                                          \
            printf((message));                                                                     \
            {{ cookiecutter.project_name_upper }}_DEBUGBREAK();                                                                 \
        }                                                                                          \
    } while (false)
#else
#define ASSERT_DEBUG(...) (void)0
#endif

#endif
