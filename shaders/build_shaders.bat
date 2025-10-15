@echo off

set OUT_DIR=%1
if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

glslc simple_shader.vert -o "%OUT_DIR%/simple_shader.vert.spv"
glslc simple_shader.frag -o "%OUT_DIR%/simple_shader.frag.spv"