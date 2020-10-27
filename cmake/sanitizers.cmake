include(CMakeParseArguments)

set(SANITIZER_COMPILER_FLAGS "-g -O3 -fsanitize=address -fsanitize=thread -fsanitize=leak -fsanitize=undefined"
		CACHE INTERNAL "")

set(CMAKE_CXX_FLAGS_SANITIZER
		${SANITIZER_COMPILER_FLAGS}
		CACHE STRING "Flags used by the C++ compiler during coverage builds."
		FORCE)
set(CMAKE_C_FLAGS_SANITIZER
		${SANITIZER_COMPILER_FLAGS}
		CACHE STRING "Flags used by the C compiler during coverage builds."
		FORCE)
set(CMAKE_EXE_LINKER_FLAGS_SANITIZER
		""
		CACHE STRING "Flags used for linking binaries during coverage builds."
		FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_SANITIZER
		""
		CACHE STRING "Flags used by the shared libraries linker during coverage builds."
		FORCE)
mark_as_advanced(
		CMAKE_CXX_FLAGS_SANITIZER
		CMAKE_C_FLAGS_SANITIZER
		CMAKE_EXE_LINKER_FLAGS_SANITIZER
		CMAKE_SHARED_LINKER_FLAGS_SANITIZER
)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(WARNING "Code coverage results with an optimised (non-Debug) build may be misleading")
endif ()

if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_Fortran_COMPILER_ID STREQUAL "GNU")
	link_libraries(gcov)
endif ()

function (append_sanitizer_compiler_flags)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZER_COMPILER_FLAGS}" PARENT_SCOPE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_COMPILER_FLAGS}" PARENT_SCOPE)
	message(STATUS "Appending code coverage compiler flags: ${SANITIZER_COMPILER_FLAGS}")
endfunction ()