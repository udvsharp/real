### Architecture setup

# Determine architecture (32/64 bit)
set(X64 OFF)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(X64 ON)
endif ()

set(DEFAULT_COMPILE_DEFINITIONS)
set(DEFAULT_COMPILE_OPTIONS)
set(DEFAULT_LINKER_OPTIONS)

### MSVC TODO: modify options
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    set(DEFAULT_COMPILE_DEFINITIONS ${DEFAULT_COMPILE_DEFINITIONS}
            _SCL_SECURE_NO_WARNINGS  # Calling any one of the potentially unsafe methods in the Standard C++ Library
            _CRT_SECURE_NO_WARNINGS  # Calling any one of the potentially unsafe methods in the CRT Library
            )

    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
            PRIVATE
            /MP           # -> build with multiple processes
            /W4           # -> warning level 4
            # /WX         # -> treat warnings as errors

            /wd4251       # -> disable warning: 'identifier': class 'type' needs to have dll-interface to be used by clients of class 'type2'
            /wd4592       # -> disable warning: 'identifier': symbol will be dynamically initialized (implementation limitation)
            # /wd4201     # -> disable warning: nonstandard extension used: nameless struct/union (caused by GLM)
            # /wd4127     # -> disable warning: conditional expression is constant (caused by Qt)

            PUBLIC
            $<$<NOT:$<CONFIG:Release>>:
            /Zi
            >

            $<$<CONFIG:Release>:
            /Gw           # -> whole program global optimization
            /GS-          # -> buffer security check: no
            /GL           # -> whole program optimization: enable link-time code generation (disables Zi)
            /GF           # -> enable string pooling
            >
            )

    set(DEFAULT_LINKER_OPTIONS ${DEFAULT_LINKER_OPTIONS}
            PRIVATE

            PUBLIC
            $<$<NOT:$<CONFIG:Release>>:
            /DEBUG
            >

            /INCREMENTAL
            )
endif ()

### GCC and Clang compiler options TODO: modify options
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(DEFAULT_COMPILE_DEFINITIONS ${DEFAULT_COMPILE_DEFINITIONS})

    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
            PRIVATE
            -Wall
            -Wextra
            -Wunused

            -Wreorder
            -Wignored-qualifiers
            -Wmissing-braces
            -Wreturn-type
            -Wswitch
            -Wswitch-default
            -Wuninitialized
            -Wmissing-field-initializers

            $<$<CXX_COMPILER_ID:GNU>:
            -Wmaybe-uninitialized

            $<$<VERSION_GREATER:$<CXX_COMPILER_VERSION>,4.8>:
            -Wpedantic

            -Wreturn-local-addr
            >
            >

            $<$<CXX_COMPILER_ID:Clang>:
            -Wpedantic

            # -Wreturn-stack-address # gives false positives
            >

            $<$<BOOL:${OPTION_REAL_ENABLE_COVERAGE}>:
            -fprofile-arcs
            -ftest-coverage
            >

            PUBLIC

            $<$<PLATFORM_ID:Darwin>:
            -pthread
            >

            # Required for CMake < 3.1; should be removed if minimum required CMake version is raised.
            $<$<VERSION_LESS:${CMAKE_VERSION},3.1>:
            -std=c++11
            >
            )

    set(DEFAULT_LINKER_OPTIONS ${DEFAULT_LINKER_OPTIONS})
endif ()

# Use pthreads on mingw and linux
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR "${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
    set(DEFAULT_LINKER_OPTIONS
            ${DEFAULT_LINKER_OPTIONS}
            -pthread
            )

    if (${OPTION_REAL_ENABLE_COVERAGE})
        set(DEFAULT_LINKER_OPTIONS
                ${DEFAULT_LINKER_OPTIONS}
                -fprofile-arcs
                -ftest-coverage
                )
    endif ()
endif ()