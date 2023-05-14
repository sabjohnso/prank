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

add_subdirectory(prank)

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
