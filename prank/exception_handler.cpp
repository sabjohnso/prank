#include <prank/exception_handler.hpp>

//
// ... Standard header files
//
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>

//
// ... prank header files
//
#include <prank/exceptions/help_request.hpp>
#include <prank/exceptions/usage_error.hpp>

namespace prank {

  class exception_handler::impl {
    int exit_code{1};

  public:
    impl(int argc, char** argv) {
      try {
        std::rethrow_exception(std::current_exception());
      } catch(help_request& e) {
        exit_code = 0;
        std::cout << e.what() << std::endl;
      } catch(usage_error& e) {
        std::cerr << "\nusage error:\n";
        std::copy_n(
          argv,
          argc,
          std::ostream_iterator<std::string>(std::cerr, " "));
        std::cout << "\n\nusage:\n" << e.what() << std::endl;

      } catch(std::exception& e) {
        std::cerr << "prank experienced an unexpected error:\n"
                  << e.what() << std::endl;
        std::rethrow_exception(std::current_exception());
      }
    }
    operator int() const { return exit_code; }
  };

  exception_handler::exception_handler(int argc, char** argv)
    : pimpl(new impl{argc, argv}) {}
  exception_handler::~exception_handler() { delete pimpl; }
  exception_handler::operator int() const { return int(*pimpl); }

} // end of namespace prank
