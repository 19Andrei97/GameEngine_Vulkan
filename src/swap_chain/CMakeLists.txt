add_library(lve_swap_chain lve_swap_chain.cpp lve_swap_chain.hpp)

target_include_directories(lve_swap_chain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lve_swap_chain 
    PUBLIC
    lve_device
    pch
)
