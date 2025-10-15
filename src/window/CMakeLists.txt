add_library(lve_window lve_window.cpp lve_window.hpp)

target_include_directories(lve_window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lve_window 
    PUBLIC     
    pch
)
