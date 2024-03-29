function(build_log MSG SEVERITY)
	# Severity: ALWAYS, ...
	if (OPTION_REAL_DEBUG_CMAKE OR SEVERITY STREQUAL "ALWAYS")
		message(STATUS "${MSG}")
	endif ()
endfunction()

### Multi-config generator detection
get_property(REAL_GENERATOR_IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (REAL_GENERATOR_IS_MULTI_CONFIG)
	message(STATUS "Current CMake generator is multi-config generator(${CMAKE_GENERATOR})")
	message(STATUS "CMAKE_BUILD_TYPE variable is ignored!")
else ()
	message(STATUS "Current CMake generator is single-config generator(${CMAKE_GENERATOR})")
endif ()

### Updating Build types
message(STATUS "Updating Build types...")
set(CUSTOM_BUILD_TYPES "Debug;Release;RelWithDebInfo")
if (REAL_GENERATOR_IS_MULTI_CONFIG)
	foreach (BUILD_TYPE IN LISTS CUSTOM_BUILD_TYPES)
		if (NOT "${BUILD_TYPE}" IN_LIST CMAKE_CONFIGURATION_TYPES)
			set(CMAKE_CONFIGURATION_TYPES ${CUSTOM_BUILD_TYPES} CACHE STRING "" FORCE)
		endif ()
	endforeach ()
else ()
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
			STRINGS "${CUSTOM_BUILD_TYPES}")

	if (NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
	elseif (NOT CMAKE_BUILD_TYPE IN_LIST CUSTOM_BUILD_TYPES)
		message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE} (Supported: ${CUSTOM_BUILD_TYPES})")
	endif ()
endif ()

### Build Directories
message(STATUS "Updating build directories...")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/int")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (REAL_GENERATOR_IS_MULTI_CONFIG)
	foreach (OUTPUT_CONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
		string(TOUPPER "${OUTPUT_CONFIG}" OUTPUT_CONFIG_UPPER)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUT_CONFIG_UPPER} "${CMAKE_BINARY_DIR}/lib")
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUT_CONFIG_UPPER} "${CMAKE_BINARY_DIR}/int")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG_UPPER} "${CMAKE_BINARY_DIR}/bin")
	endforeach ()
endif ()

 include(compilerOptions)

foreach (BUILD_TYPE IN LISTS CUSTOM_BUILD_TYPES)
	string(TOUPPER "${BUILD_TYPE}" BUILD_TYPE_UPPERCASE)
#	set(CMAKE_SHARED_LINKER_FLAGS_${BUILD_TYPE_UPPERCASE} ${DEFAULT_LINKER_OPTIONS})
#	set(CMAKE_MODULE_LINKER_FLAGS_${BUILD_TYPE_UPPERCASE} ${DEFAULT_LINKER_OPTIONS})
#	set(CMAKE_EXE_LINKER_FLAGS_${BUILD_TYPE_UPPERCASE} ${DEFAULT_LINKER_OPTIONS})
endforeach ()