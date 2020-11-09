function (add_shaders TARGET_NAME)
	set(GENERATE_SHADERS_TARGET_NAME "${TARGET_NAME}-generate-shaders")
	set(SHADERS)
	set(SHADERS_OUTDIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders")

	add_custom_command(
			OUTPUT "${SHADERS_OUTDIR}"
			COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADERS_OUTDIR}"
			COMMENT "Creating shaders directory in ${SHADERS_OUTDIR}"

			VERBATIM
	)

	foreach (SHADER_SOURCE IN LISTS ARGN)
		get_filename_component(SHADER_NAME "${SHADER_SOURCE}" NAME)
		set(SHADER_OUTFILE "${SHADERS_OUTDIR}/${SHADER_NAME}")

		message(STATUS "Adding shaders ${SHADER_SOURCE} to ${TARGET_NAME}")
		list(APPEND SHADERS "${SHADER_OUTFILE}")

		add_custom_command(
				OUTPUT "${SHADER_OUTFILE}"
				DEPENDS ${SHADERS_OUTDIR} ${SHADER_SOURCE}
				COMMAND ${CMAKE_COMMAND} -E copy ${SHADER_SOURCE} ${SHADERS_OUTDIR}


				COMMENT "Moving ${SHADER_SOURCE} to runtime directory..."

				VERBATIM
		)
	endforeach ()

	add_custom_target(
			${GENERATE_SHADERS_TARGET_NAME} ALL
			DEPENDS ${SHADERS}
	)
	add_dependencies(${TARGET_NAME} ${GENERATE_SHADERS_TARGET_NAME})
endfunction ()
