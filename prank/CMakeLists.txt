configure_file(config.hpp.in config.hpp)

add_library(prank_header INTERFACE)
set_target_properties(prank_header PROPERTIES EXPORT_NAME header)
target_include_directories(prank_header
  INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${prank_INSTALL_INCLUDEDIR}>)

add_library(prank::header ALIAS prank_header)
  
install(TARGETS prank_header
  EXPORT prank_EXPORTS
  RUNTIME DESTINATION ${prank_INSTALL_BINDIR}
  LIBRARY DESTINATION ${prank_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${prank_INSTALL_LIBDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  DESTINATION ${prank_INSTALL_INCLUDEDIR}/prank)
