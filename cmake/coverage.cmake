find_program(GCOV_PATH gcov)
# find_program(LCOV_PATH NAMES lcov lcov.bat lcov.exe lcov.perl)
# find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/scripts/test)
# find_program(CPPFILT_PATH NAMES c++filt)

include(CMakeParseArguments)

if (NOT GCOV_PATH)
	message(FATAL_ERROR "gcov not found! Aborting...")
else ()
	message(STATUS "Found gcov: ${GCOV_PATH}")
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
	if ("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 3)
		message(FATAL_ERROR "Clang version must be 3.0.0 or greater! Aborting...")
	endif ()
elseif (NOT CMAKE_COMPILER_IS_GNUCXX)
	# Do something
	message(STATUS "Compiler is not GNUCXX")
endif ()

set(COVERAGE_COMPILER_FLAGS "-g -fprofile-arcs -ftest-coverage"
		CACHE INTERNAL "")

set(CMAKE_CXX_FLAGS_COVERAGE
		${COVERAGE_COMPILER_FLAGS}
		CACHE STRING "Flags used by the C++ compiler during coverage builds."
		FORCE)
set(CMAKE_C_FLAGS_COVERAGE
		${COVERAGE_COMPILER_FLAGS}
		CACHE STRING "Flags used by the C compiler during coverage builds."
		FORCE)
set(CMAKE_EXE_LINKER_FLAGS_COVERAGE
		""
		CACHE STRING "Flags used for linking binaries during coverage builds."
		FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
		""
		CACHE STRING "Flags used by the shared libraries linker during coverage builds."
		FORCE)
mark_as_advanced(
		CMAKE_CXX_FLAGS_COVERAGE
		CMAKE_C_FLAGS_COVERAGE
		CMAKE_EXE_LINKER_FLAGS_COVERAGE
		CMAKE_SHARED_LINKER_FLAGS_COVERAGE
)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(WARNING "Code coverage results with an optimised (non-Debug) build may be misleading")
endif ()

if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
	link_libraries(gcov)
endif ()

function (append_coverage_compiler_flags)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_COVERAGE}" PARENT_SCOPE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_COVERAGE}" PARENT_SCOPE)
	message(STATUS "Appending code coverage compiler flags: ${COVERAGE_COMPILER_FLAGS}")
endfunction ()