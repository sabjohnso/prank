#pragma once

//
// ... Standard header files
//
#include <stdexcept>

namespace prank {

  class help_request : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
  };

} // end of namespace prank
