set(WANTED_SANITIZE_THREAD ${SANITIZE_THREAD})
set(WANTED_SANITIZE_UNDEFINED ${SANITIZE_UNDEFINED})
set(WANTED_SANITIZE_MEMORY ${SANITIZE_MEMORY})
set(WANTED_SANITIZE_ADDRESS ${SANITIZE_ADDRESS})

function (check_sanitizer NAME PREFIX)
	if (${WANTED_SANITIZE_${NAME}})
		if ("${${PREFIX}_${CMAKE_C_COMPILER_ID}_FLAGS}" STREQUAL "")
			message(FATAL_ERROR ${NAME} " sanitizer is NOT available")
		else ()
			message(STATUS ${NAME} " sanitizer is available")
		endif ()
	endif ()
endfunction ()

check_sanitizer(THREAD TSan)
check_sanitizer(UNDEFINED UBSan)
check_sanitizer(MEMORY MSan)
check_sanitizer(ADDRESS ASan)

# TODO: figure out what to do with sanitizers!
