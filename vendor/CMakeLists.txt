# spdlog
set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE_HO OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS_HO OFF CACHE BOOL "" FORCE)
add_subdirectory(spdlog)
set_target_properties(spdlog PROPERTIES FOLDER vendor)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)
set_target_properties(glfw PROPERTIES FOLDER vendor)

# glad
set(GLAD_INSTALL OFF CACHE BOOL "" FORCE)
set(GLAD_PROFILE "core" CACHE STRING "" FORCE)
add_subdirectory(glad)
set_target_properties(glad PROPERTIES FOLDER vendor)
set_target_properties(glad-generate-files PROPERTIES FOLDER vendor)

# imgui
set(IMGUI_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(imgui)
set_target_properties(imgui PROPERTIES FOLDER vendor)

# glm
set(GLM_QUIET OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory(glm)

# stb
add_subdirectory(stb)