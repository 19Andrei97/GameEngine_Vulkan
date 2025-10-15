add_library(first_app first_app.cpp first_app.hpp)

target_include_directories(first_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(first_app 
    PUBLIC 
    lve_swap_chain
    lve_device
    lve_window
    lve_pipeline
    pch
)