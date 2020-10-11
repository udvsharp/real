macro (add_assets_dir DIRNAME)
	file(COPY "${DIRNAME}" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endmacro ()