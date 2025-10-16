add_library(lve_model lve_model.cpp lve_model.hpp)

target_include_directories(lve_model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lve_model 
    PUBLIC 
    lve_device
    pch
)