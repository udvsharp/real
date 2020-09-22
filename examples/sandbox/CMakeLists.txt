### Helpers
set(VN_SANDBOX_TARGET_NAME "${META_VN_PROJECT_NAME}-sandbox")

### Target
add_executable(
		${VN_SANDBOX_TARGET_NAME}
		EXCLUDE_FROM_ALL
		sandbox.cpp
)

target_link_libraries(
		version-sandbox
		PRIVATE
		${VN_LIBRARY_TARGET_NAME}
)

## RenderDoc
set(VN_RDOC_WORKING_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(VN_RDOC_SANDBOX_FILE "$<TARGET_FILE:${VN_SANDBOX_TARGET_NAME}>")
set(VN_RDOC_CONFIG_OUTFILE "${CMAKE_BINARY_DIR}/rdoc/settings.cap")

configure_file("${CMAKE_SOURCE_DIR}/rdoc/settings.cap" "${VN_RDOC_CONFIG_OUTFILE}")

# FIXME: solve problem with single and multiconfig generators
if (CMAKE_CONFIGURATION_TYPES)
	file(
			GENERATE
			OUTPUT "${VN_RDOC_CONFIG_OUTFILE}.$<CONFIG>"
			INPUT "${VN_RDOC_CONFIG_OUTFILE}"
	)
else ()
	file(
			GENERATE
			OUTPUT "${VN_RDOC_CONFIG_OUTFILE}"
			INPUT "${VN_RDOC_CONFIG_OUTFILE}"
	)
endif ()