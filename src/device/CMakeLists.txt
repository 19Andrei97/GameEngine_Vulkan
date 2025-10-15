add_library(lve_device lve_device.cpp lve_device.hpp)

target_include_directories(lve_device PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lve_device 
    PUBLIC 
    lve_window
    pch
)