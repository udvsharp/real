message(STATUS "Configuring ${META_REAL_NAME_VERSION}")

# Target
add_library(
		${REAL_LIBRARY_TARGET_NAME}
		SHARED  # It is necessary

		### Headers
		# util
		include/real/util/singleton.hpp
		# Core
		include/real/real.hpp
		include/real/pch.hpp
		include/real/assert.hpp
		include/real/core.hpp
		include/real/application.hpp
		include/real/logger.hpp
		include/real/layer.hpp
		include/real/layer_stack.hpp
		include/real/input.hpp
		include/real/window.hpp
		include/real/event.hpp
		include/real/time.hpp
		include/real/transform.hpp
		# Layers
		include/real/layer/base_layer.hpp
		include/real/layer/imgui_layer.hpp
		# Window
		include/real/window/base_window.hpp
		# Input
		include/real/keycode.hpp
		include/real/input/base_input.hpp
		# Events
		include/real/event/base_event.hpp
		include/real/event/key_event.hpp
		include/real/event/mouse_event.hpp
		include/real/event/window_event.hpp
		# Renderer
		include/real/renderer.hpp
		include/real/renderer/base_rendering_context.hpp
		include/real/renderer/base_renderer.hpp
		include/real/renderer/render_command.hpp
		include/real/renderer/renderer_api.hpp
		include/real/renderer/base_shader.hpp
		include/real/renderer/base_texture.hpp
		include/real/renderer/buffer_layout.hpp
		include/real/renderer/buffer_vertex.hpp
		include/real/renderer/buffer_index.hpp
		include/real/renderer/array_vertex.hpp
		include/real/renderer/camera.hpp
		include/real/renderer/common.hpp
		# Time
		include/real/time/timestep.hpp
		## Api
		## GL
		include/real/api/gl/gl_rendering_context.hpp
		include/real/api/gl/gl_renderer_api.hpp
		include/real/api/gl/gl_buffer_vertex.hpp
		include/real/api/gl/gl_buffer_index.hpp
		include/real/api/gl/gl_array_vertex.hpp
		include/real/api/gl/gl_conversions.hpp
		include/real/api/gl/gl_shader.hpp
		include/real/api/gl/gl_texture.hpp

		### Sources
		# Core
		src/application.cpp
		src/base_window.cpp
		src/layer_stack.cpp
		src/logger.cpp
		# Layers
		src/base_layer.cpp
		src/layer/imgui_layer.cpp
		# Input
		src/base_input.cpp
		# Renderer
		src/renderer/base_rendering_context.cpp
		src/renderer/base_renderer.cpp
		src/renderer/renderer_api.cpp
		src/renderer/buffer_vertex.cpp
		src/renderer/buffer_index.cpp
		src/renderer/buffer_layout.cpp
		src/renderer/array_vertex.cpp
		src/renderer/base_shader.cpp
		src/renderer/base_texture.cpp
		src/renderer/camera.cpp
		## Api
		## GL
		# Imgui
		src/api/gl/imgui_impl_opengl3.h
		src/api/gl/imgui_impl_opengl3.cpp
		# Renderer
		src/api/gl/gl_rendering_context.cpp
		src/api/gl/gl_renderer_api.cpp
		src/api/gl/gl_shader.cpp
		src/api/gl/gl_texture.cpp
		src/api/gl/gl_buffer_vertex.cpp
		src/api/gl/gl_buffer_index.cpp
		src/api/gl/gl_array_vertex.cpp
		## Other
		src/stb.cpp
)

# Platform-dependent sources
if (WIN32)
	target_sources(
			${REAL_LIBRARY_TARGET_NAME}
			PUBLIC
			# Window
			include/real/platform/windows/windows_window.hpp
			# Input
			include/real/platform/windows/windows_input.hpp
			# Time
			include/real/platform/windows/windows_time.hpp
			PRIVATE
			# Window
			src/platform/windows/windows_window.cpp
			# Input
			src/platform/windows/windows_input.cpp
			# Time
			src/platform/windows/windows_time.cpp
	)

	target_precompile_headers(
			${REAL_LIBRARY_TARGET_NAME}
			PRIVATE

			# Platform-dependent headers
			<Windows.h>
	)
endif ()

# Shaders
file(MAKE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders")

set(
		SHADERS_SRCS
		"${CMAKE_CURRENT_SOURCE_DIR}/include/real/renderer/shaders/base.glsl"
		"${CMAKE_CURRENT_SOURCE_DIR}/include/real/renderer/shaders/tex.glsl"
)

foreach (SHADER_SRC ${SHADERS_SRCS})
	get_filename_component(SHADER_FILENAME "${SHADER_SRC}" NAME)

	set(SHADER_OUTPUT_FILENAME)
	if (REAL_GENERATOR_IS_MULTI_CONFIG)
		set(SHADER_OUTPUT_FILENAME "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/shaders/${SHADER_FILENAME}")
	else ()
		set(SHADER_OUTPUT_FILENAME "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/${SHADER_FILENAME}")
	endif ()

	add_custom_command(
			TARGET ${REAL_LIBRARY_TARGET_NAME} PRE_BUILD
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			COMMENT "Copying shader (${SHADER_FILENAME}) to build directory..."
			DEPENDS ${SHADER_SRC}

			COMMAND ${CMAKE_COMMAND} -E copy
			"${SHADER_SRC}"
			"${SHADER_OUTPUT_FILENAME}"

			VERBATIM
	)
endforeach ()

target_include_directories(
		${REAL_LIBRARY_TARGET_NAME}
		PUBLIC
		"include"
		"${CMAKE_CURRENT_BINARY_DIR}"
		PRIVATE
		"src"
)

target_precompile_headers(
		${REAL_LIBRARY_TARGET_NAME}
		PRIVATE
		"include/real/pch.hpp"
)

# Properties
set_target_properties(
		${REAL_LIBRARY_TARGET_NAME} PROPERTIES

		# Folder
		FOLDER ${META_REAL_PROJECT_FULL_NAME}/engine

		# Version
		VERSION ${META_REAL_VERSION}
		SOVERSION ${META_REAL_VERSION_MAJOR}

		# C++
		CXX_STANDARD ${CXX_STANDARD_DEFAULT}
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF

		# C
		C_STANDARD ${C_STANDARD_DEFAULT}
		C_STANDARD_REQUIRED ON
		C_EXTENSIONS OFF

		# Other
		VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

target_compile_definitions(
		${REAL_LIBRARY_TARGET_NAME}
		PRIVATE

		PUBLIC
		# Build type macros
		$<$<CONFIG:Debug>:REAL_DEBUG>
		$<$<CONFIG:Release>:REAL_RELEASE>
		$<$<CONFIG:Profile>:REAL_PROFILE>
		# Platform macros
		$<$<PLATFORM_ID:Windows>:REAL_PLATFORM_WINDOWS>
		INTERFACE
		REAL_CLIENT
)

target_compile_options(
		${REAL_LIBRARY_TARGET_NAME}
		PUBLIC
		${DEFAULT_COMPILER_OPTIONS}
)

target_link_options(
		${REAL_LIBRARY_TARGET_NAME}
		PRIVATE
		${DEFAULT_LINKER_OPTIONS}
)

set_target_properties(
		${REAL_LIBRARY_TARGET_NAME} PROPERTIES

		VISIBILITY_INLINES_HIDDEN YES
		CXX_VISIBILITY_PRESET hidden
		C_VISIBILITY_PRESET hidden
		ASM_VISIBILITY_PRESET hidden
)

# Utility
# Generated Files
write_compiler_detection_header(
		FILE "${META_REAL_PROJECT_NAME}/core-compiler.hpp"
		PREFIX ${META_REAL_PROJECT_NAME_PREFIX}
		COMPILERS Clang GNU MSVC
		FEATURES cxx_override
)

generate_export_header(
		${REAL_LIBRARY_TARGET_NAME}
		BASE_NAME "${META_REAL_PROJECT_NAME_PREFIX}"
		PREFIX_NAME "${META_REAL_PROJECT_NAME_PREFIX}_"
		INCLUDE_GUARD_NAME "${META_REAL_PROJECT_NAME_PREFIX}_CORE_COMPILER"
		EXPORT_MACRO_NAME "API"
		EXPORT_FILE_NAME "${META_REAL_PROJECT_NAME}/core-export.hpp"
		NO_EXPORT_MACRO_NAME "NO_EXPORT"
		DEPRECATED_MACRO_NAME "DEPRECATED"
		INCLUDE_GUARD_NAME "${META_REAL_PROJECT_NAME_PREFIX}_CORE_API"
		STATIC_DEFINE "STATIC"
		NO_DEPRECATED_MACRO_NAME "NO_DEPRECATED"

		# DEFINE_NO_DEPRECATED
)

# Custom commands
set(LOGS_DIR "${CMAKE_CURRENT_BINARY_DIR}/logs")
set(LOG_EXPORTS_FILE "${LOGS_DIR}/exports.txt")

file(MAKE_DIRECTORY "${LOGS_DIR}")

# TODO: add support for other platforms
if (WIN32 AND MSVC)
	# Save DLL exports
	add_custom_command(
			TARGET ${REAL_LIBRARY_TARGET_NAME} POST_BUILD
			WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
			COMMENT "Saving DLL file exports"
			BYPRODUCTS "${LOG_EXPORTS_FILE}"

			COMMAND dumpbin /exports $<TARGET_FILE:${REAL_LIBRARY_TARGET_NAME}> > "${LOG_EXPORTS_FILE}"

			VERBATIM
	)
endif ()