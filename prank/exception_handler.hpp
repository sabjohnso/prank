#pragma once

namespace prank {
   /**
    * @brief A class providing top-level exception handling
    * for `prank`.
    */
   class exception_handler {
   public:
     exception_handler(int argc, char** argv);
     ~exception_handler();

     operator int() const;

   private:
     class impl;
     impl* pimpl;
   };
} // namespace prank
