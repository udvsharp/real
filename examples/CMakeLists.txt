message(STATUS "Configuring examples")

set(EXAMPLES) # List of all examples

function (example_target_name_for EX_NAME TARGET_NAME)
	set(${TARGET_NAME} "${META_REAL_PROJECT_NAME}-example-${EX_NAME}" PARENT_SCOPE)
endfunction ()

macro (add_example EX_NAME)
	### Helpers
	set(EXAMPLE_TARGET_NAME)
	example_target_name_for(${EX_NAME} EXAMPLE_TARGET_NAME)

	set(EXAMPLE_SOURCES ${ARGN})

	message(STATUS "Adding real example: ${EX_NAME}(${EXAMPLE_SOURCES})")
	### Target
	add_executable(
			${EXAMPLE_TARGET_NAME}
			EXCLUDE_FROM_ALL
			${EXAMPLE_SOURCES}
	)

	target_link_libraries(
			${EXAMPLE_TARGET_NAME}
			PRIVATE
			${REAL_LIBRARY_TARGET_NAME}
	)

	# Properties
	set_target_properties(
			${EXAMPLE_TARGET_NAME} PROPERTIES

			# Folder
			FOLDER ${META_REAL_PROJECT_FULL_NAME}/examples/${EX_NAME}

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

	list(APPEND EXAMPLES ${EX_NAME})
endmacro ()

# Examples
if (OPTION_REAL_EXAMPLES_CUBE)
	add_example(
			cube
			cube/main.cpp
	)
endif ()

if (OPTION_REAL_EXAMPLES_TEXTURE)
	add_example(
			texture
			texture/main.cpp
	)
	add_assets_dir(texture/assets)
endif ()

# RenderDoc
foreach (EX_NAME IN LISTS EXAMPLES)
	set(EXAMPLE_TARGET_NAME)
	example_target_name_for(${EX_NAME} EXAMPLE_TARGET_NAME)

	generate_rdoc_settings_from(
			"${PROJECT_SOURCE_DIR}/rdoc/settings.cap"
			${EXAMPLE_TARGET_NAME}
			"${CMAKE_BINARY_DIR}/examples/${EX_NAME}"
	)
endforeach ()