cmake_minimum_required(VERSION 3.12)

project(prank VERSION 0.1.0 LANGUAGES C CXX)

option(prank_BUILD_TESTING "Build the prank tests" ON)
set(prank_CXX_STANDARD 20 CACHE STRING "C++ standard for prank")

include(GNUInstallDirs)
set(prank_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(prank_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(prank_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})
set(prank_INSTALL_CONFDIR ${prank_INSTALL_LIBDIR}/cmake/prank-${PROJECT_VERSION})

list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)

include(prank_deps)

add_library(prank_compiler_settings INTERFACE)
set_target_properties(prank_compiler_settings
  PROPERTIES
  CXX_STANDARD ${prank_CXX_STANDARD}
  CXX_STANDARD_REQUIRED TRUE
  EXPORT_NAME compiler_settings
)
add_library(prank::compiler_settings ALIAS prank_compiler_settings)

add_library(prank_header INTERFACE)
set_target_properties(prank_header PROPERTIES EXPORT_NAME header)
target_include_directories(prank_header
  INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${prank_INSTALL_INCLUDEDIR}>)
target_link_libraries(prank_header INTERFACE prank::compiler_settings)
add_library(prank::header ALIAS prank_header)


add_subdirectory(prank)


install(TARGETS prank_compiler_settings prank_header prank
  EXPORT prank_EXPORTS
  RUNTIME DESTINATION ${prank_INSTALL_BINDIR}
  LIBRARY DESTINATION ${prank_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${prank_INSTALL_LIBDIR}
)

install(FILES
  ${PROJECT_BINARY_DIR}/config.hpp
  DESTINATION ${prank_INSTALL_INCLUDEDIR}/prank)

install(DIRECTORY prank
  DESTINATION ${prank_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.hpp")


if(prank_BUILD_TESTING)
  include(CTest)
  if(BUILD_TESTING)
    add_subdirectory(prank_testing)
  endif()
endif()

install(EXPORT prank_EXPORTS
  NAMESPACE prank::
  FILE prank-exports.cmake
  DESTINATION ${prank_INSTALL_CONFDIR})

configure_file(prank-config.cmake.in prank-config.cmake)
install(FILES ${PROJECT_BINARY_DIR}/prank-config.cmake
  DESTINATION ${prank_INSTALL_CONFDIR})
