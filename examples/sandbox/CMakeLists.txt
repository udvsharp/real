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