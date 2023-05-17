#pragma once

//
// ... Standards header files
//
#include <stdexcept>

namespace prank {

  class usage_error : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
  };

} // end of namespace prank
