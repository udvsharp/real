### Functions

# Generates renderdoc settings file from given template
function(generate_rdoc_settings_from TEMPLATE_FILENAME TARGET_NAME RDOC_CONFIG_OUTFOLDER)
	message(STATUS "Generating RenderDoc Settings for ${TARGET_NAME}")

	## RenderDoc
	set(RDOC_WORKING_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
	set(RDOC_TARGET_FILE "$<TARGET_FILE:${TARGET_NAME}>")

	set(RDOC_CONFIG_OUTFILE "${RDOC_CONFIG_OUTFOLDER}/rdoc/settings.cap")

	configure_file("${CMAKE_SOURCE_DIR}/rdoc/settings.cap" "${RDOC_CONFIG_OUTFILE}")

	if (REAL_GENERATOR_IS_MULTI_CONFIG)
		file(
				GENERATE
				OUTPUT "${RDOC_CONFIG_OUTFILE}.$<CONFIG>"
				INPUT "${RDOC_CONFIG_OUTFILE}"
		)
	else ()
		file(
				GENERATE
				OUTPUT "${RDOC_CONFIG_OUTFILE}"
				INPUT "${RDOC_CONFIG_OUTFILE}"
		)
	endif ()

endfunction()