#include <prank/driver.hpp>
#include <prank/exception_handler.hpp>

int
main(int argc, char** argv) {
  try {
    return prank::driver(argc, argv);
  } catch(...) { return prank::exception_handler(argc, argv); }
}
