#pragma once

namespace prank {

  /**
   * @brief A class providing top-level program flow control
   * for `prank`.
   */
  class driver {
  public:
    driver(int argc, char** arg);
    ~driver();
    operator int() const;

  private:
    class impl;
    impl* pimpl;
  };

} // end of namespace prank
