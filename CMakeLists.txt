### Global build system TODOs
# TODO: support multi-config generators

### Cmake setup
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

cmake_policy(SET CMP0077 NEW) # option honors normal variables

### Meta info
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
set(META_REAL_VERSION "${META_REAL_VERSION_MAJOR}.${META_REAL_VERSION_MINOR}.${META_REAL_VERSION_PATCH}")
set(META_REAL_NAME_VERSION "${META_REAL_PROJECT_FULL_NAME} v${META_REAL_VERSION_MAJOR}.${META_REAL_VERSION_MINOR}.${META_REAL_VERSION_PATCH}")
# Targets
set(REAL_LIBRARY_TARGET_NAME ${META_REAL_PROJECT_NAME})

### Project config options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Examples
option(OPTION_REAL_BUILD_EXAMPLES "Build examples" OFF)
option(OPTION_REAL_EXAMPLES_CUBE "Build rotating cube example" ON)
option(OPTION_REAL_EXAMPLES_TEXTURE "Build texture example" ON)
option(OPTION_REAL_ENABLE_COVERAGE "Enable code coverage" OFF)
option(OPTION_REAL_ENABLE_SANITIZE "Enable sanitizers" OFF)
set(REAL_SANITIZER "" CACHE STRING "Choose which sanitizer to use")
set_property(CACHE REAL_SANITIZER PROPERTY STRINGS "thread" "leak" "undefined" "address" "memory")

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
# Directories
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
# Standard
include(WriteCompilerDetectionHeader)
include(GenerateExportHeader)

# Own
include(compilerOptions)
include(rdoc)
include(assets)

### Code analysis
# Coverage
if (OPTION_REAL_ENABLE_COVERAGE)
	include(coverage)
	append_coverage_compiler_flags()
endif ()
# Sanitizers
if (OPTION_REAL_ENABLE_SANITIZE)
	include(sanitizers)
	append_sanitizer_compiler_flags()
endif ()

### Build system setup
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/int")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
endif ()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

### Project
project(${META_REAL_PROJECT_FULL_NAME}
		VERSION ${META_REAL_VERSION}
		DESCRIPTION ${META_REAL_PROJECT_DESCRIPTION}
		HOMEPAGE_URL ${META_REAL_AUTHOR_DOMAIN}
		LANGUAGES C CXX ASM)

### Engine
add_subdirectory(engine)

# TODO: get rid of dependencies
### Submodules
add_subdirectory(vendor)

### Packages
find_package(OpenGL REQUIRED)

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