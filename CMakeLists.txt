cmake_minimum_required(VERSION 3.20)
project(GameEngineVulkan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

######################################################

# Vulkan
find_package(Vulkan REQUIRED)

# GLFW
find_package(glfw3 REQUIRED)

######################################################

# Add submodules
add_subdirectory(src/pch)
add_subdirectory(src/window)
add_subdirectory(src/first_app)
add_subdirectory(src/pipeline)
add_subdirectory(src/device)
add_subdirectory(src/swap_chain)
add_subdirectory(shaders)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp "src/first_app/first_app.cpp" "src/pipeline/lve_pipeline.cpp")

# Link internal libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    lve_swap_chain
    lve_device
    lve_pipeline
    lve_window
    first_app
    pch
    glfw
    Vulkan::Vulkan
)

# Ensure shaders build before executable
add_dependencies(${PROJECT_NAME} build_shaders)