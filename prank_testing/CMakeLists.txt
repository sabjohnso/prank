find_package(GTest)

macro(prank_add_test test_name exe_name)
  add_executable(${exe_name} ${ARGN})
  target_link_libraries(${exe_name} PRIVATE
    prank::header
    GTest::gtest_main)
  set_target_properties(${exe_name}
    PROPERTIES
    CXX_STANDARD ${prank_CXX_STANDARD})
  add_test(${test_name} ${exe_name})
endmacro()

add_test(NAME prank_no_args COMMAND prank::prank)
set_tests_properties(prank_no_args
  PROPERTIES
    WILL_FAIL TRUE
    FAIL_REGULAR_EXPRESSION "usage error"
    LABELS app
)

add_test(NAME prank_help COMMAND prank::prank --help)
set_tests_properties(prank_help
  PROPERTIES
    PASS_REGULAR_EXPRESSION "prank options"
    LABELS app  
)


  

  
