configure_file(config.hpp.in config.hpp)

add_executable(prank prank.cpp driver.cpp exception_handler.cpp)
target_link_libraries(prank PRIVATE prank::header Boost::program_options)
add_executable(prank::prank ALIAS prank)

