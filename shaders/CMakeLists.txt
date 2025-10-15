cmake_minimum_required(VERSION 3.16)

set(SHADER_BUILD_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/build_shaders.bat")
set(SHADER_OUTPUT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders")

file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

add_custom_target(build_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E echo "=== Building shaders ==="
    COMMAND ${CMAKE_COMMAND} -E echo "Output directory: ${SHADER_OUTPUT_DIR}"
    COMMAND "${SHADER_BUILD_SCRIPT}" "${SHADER_OUTPUT_DIR}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running shader compilation script"
)