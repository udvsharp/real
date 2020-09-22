### Global build system TODOs
# TODO: support multi-config generators

### Cmake setup
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

cmake_policy(SET CMP0077 NEW) # option honors normal variables

### Meta info
set(META_VN_PROJECT_NAME "version")
string(TOUPPER "vn" META_VN_PROJECT_NAME_PREFIX)
string(TOUPPER ${META_VN_PROJECT_NAME} META_VN_PROJECT_NAME_UPPER)
set(META_VN_PROJECT_FULL_NAME "${META_VN_PROJECT_NAME}-engine")
set(META_VN_PROJECT_DESCRIPTION "The Version 3D Rendering Engine")
set(META_VN_AUTHOR "udv-code")
set(META_VN_AUTHOR_DOMAIN "https://github.com/${META_VN_AUTHOR}/${META_VN_PROJECT_NAME}")
# Version
set(META_VN_VERSION_MAJOR "1")
set(META_VN_VERSION_MINOR "0")
set(META_VN_VERSION_PATCH "0")
set(META_VN_VERSION "${META_VN_VERSION_MAJOR}.${META_VN_VERSION_MINOR}.${META_VN_VERSION_PATCH}")
set(META_VN_NAME_VERSION "${META_VN_PROJECT_FULL_NAME} v${META_VN_VERSION_MAJOR}.${META_VN_VERSION_MINOR}.${META_VN_VERSION_PATCH}")
# Targets
set(VN_LIBRARY_TARGET_NAME ${META_VN_PROJECT_NAME})

### Project config options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(OPTION_VN_BUILD_EXAMPLES "Build examples" OFF)
option(OPTION_VN_BUILD_SANDBOX "Build examples" ON)

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
list(APPEND CMAKE_MODULE_PATH "cmake")

include(WriteCompilerDetectionHeader)
include(GenerateExportHeader)

### Build system setup
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/int")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
endif ()

### Project
project(${META_VN_PROJECT_FULL_NAME}
		VERSION ${META_VN_VERSION}
		DESCRIPTION ${META_VN_PROJECT_DESCRIPTION}
		HOMEPAGE_URL ${META_VN_AUTHOR_DOMAIN}
		LANGUAGES C CXX ASM)

include(cmake/compilerOptions.cmake)

### Engine
add_subdirectory(engine)

# TODO: get rid of dependencies
## Submodules

# spdlog
set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE_HO OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS_HO OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/spdlog)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

find_package(OpenGL REQUIRED)

# glad
set(GLAD_INSTALL OFF CACHE BOOL "" FORCE)
set(GLAD_PROFILE "core" CACHE STRING "" FORCE)
add_subdirectory(vendor/glad)

# imgui
set(IMGUI_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/imgui)

# glm
set(GLM_QUIET OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glm)

target_link_libraries(
		${VN_LIBRARY_TARGET_NAME}
		PUBLIC
		imgui
		glfw
		glad
		spdlog::spdlog
		OpenGL::GL
		glm::glm
)

### Examples
if (OPTION_VN_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif ()