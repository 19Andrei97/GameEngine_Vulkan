add_library(lve_pipeline lve_pipeline.cpp lve_pipeline.hpp)

target_include_directories(lve_pipeline PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lve_pipeline 
    PUBLIC     
    lve_device
    pch
)

