### CMake setup

# Version
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
# Policies
cmake_policy(SET CMP0077 NEW) # option honors normal variables

### Meta info

# Names
set(META_REAL_PROJECT_NAME "real")
string(TOUPPER "real" META_REAL_PROJECT_NAME_PREFIX)
string(TOUPPER ${META_REAL_PROJECT_NAME} META_REAL_PROJECT_NAME_UPPER)
set(META_REAL_PROJECT_FULL_NAME "${META_REAL_PROJECT_NAME}-engine")
set(META_REAL_PROJECT_DESCRIPTION "The Real 3D Rendering Engine")
set(META_REAL_AUTHOR "udv-code")
set(META_REAL_AUTHOR_DOMAIN "https://github.com/${META_REAL_AUTHOR}/${META_REAL_PROJECT_NAME}")

# Version
set(META_REAL_VERSION_MAJOR "1")
set(META_REAL_VERSION_MINOR "0")
set(META_REAL_VERSION_PATCH "0")
set(META_REAL_VERSION_TWEAK "0")
set(META_REAL_VERSION "${META_REAL_VERSION_MAJOR}.${META_REAL_VERSION_MINOR}.${META_REAL_VERSION_PATCH}.${META_REAL_VERSION_TWEAK}")
set(META_REAL_NAME_VERSION "${META_REAL_PROJECT_FULL_NAME} v${META_REAL_VERSION_MAJOR}.${META_REAL_VERSION_MINOR}.${META_REAL_VERSION_PATCH}.${META_REAL_VERSION_TWEAK}")

# Targets
set(REAL_LIBRARY_TARGET_NAME "${META_REAL_PROJECT_NAME}")

### Project config options

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
# Examples
option(OPTION_REAL_BUILD_EXAMPLES "Build examples" OFF)
# Detail examples
option(OPTION_REAL_EXAMPLES_CUBE "Build rotating cube example" ON)
option(OPTION_REAL_EXAMPLES_TEXTURE "Build texture example" ON)
# Analysis tools
option(OPTION_REAL_ENABLE_COVERAGE "Enable code coverage" OFF)
option(OPTION_REAL_ENABLE_SANITIZE "Enable sanitizers" OFF)

# Configs
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

### Project
project(${META_REAL_PROJECT_FULL_NAME}
		VERSION ${META_REAL_VERSION}
		DESCRIPTION ${META_REAL_PROJECT_DESCRIPTION}
		HOMEPAGE_URL ${META_REAL_AUTHOR_DOMAIN}
		LANGUAGES C CXX ASM)

### Language Options
# C
set(C_STANDARD_DEFAULT 11)
set(CMAKE_C_STANDARD ${C_STANDARD_DEFAULT})
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
# C++
set(CXX_STANDARD_DEFAULT 20)
set(CMAKE_CXX_STANDARD ${CXX_STANDARD_DEFAULT})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# TODO: ASM

### Modules
# Standard
include(WriteCompilerDetectionHeader)
include(GenerateExportHeader)

# Own
include(build)

include(rdoc)
include(assets)
include(shaders)

# TODO: get rid of dependencies
### Submodules
add_subdirectory(vendor)

### Packages
find_package(OpenGL REQUIRED)

### Code analysis
# Coverage
if (OPTION_REAL_ENABLE_COVERAGE)
	include(coverage)
	append_coverage_compiler_flags()
endif ()

# Sanitizers
if (OPTION_REAL_ENABLE_SANITIZE)
	include(sanitizers)
	# TODO: append_sanitizer_compiler_flags()
endif ()

### Engine
add_subdirectory(engine)

target_link_libraries(
		${REAL_LIBRARY_TARGET_NAME}
		PUBLIC
		imgui
		glfw
		glad
		spdlog::spdlog
		OpenGL::GL
		glm::glm

		stb
)

### Examples
if (OPTION_REAL_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif ()