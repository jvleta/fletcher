add_subdirectory(panel)
add_executable(fletcher main.cpp)
target_link_libraries(fletcher panel boost_program_options)