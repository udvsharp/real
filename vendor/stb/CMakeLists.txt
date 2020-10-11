# TODO: improve this.
add_library(stb INTERFACE)
target_include_directories(
		stb INTERFACE
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
		"$<INSTALL_INTERFACE:include>"
)