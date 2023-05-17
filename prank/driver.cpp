#include <prank/driver.hpp>

//
// ... Standard header files
//
#include <string>
#include <vector>

//
// ... External header files
//
#include <boost/program_options.hpp>

//
// ... prank header files
//
#include <prank/exceptions/help_request.hpp>
#include <prank/exceptions/usage_error.hpp>

namespace prank {

  namespace po = boost::program_options;

  class command_line_processor {
    int argc;
    po::options_description desc;
    po::variables_map config;

  public:
    command_line_processor(int argc, char** argv)
      : argc(argc)
      , desc(make_description()) {
      check_argument_count();
      po::store(po::parse_command_line(argc, argv, desc), config);
      check_for_help();
    }

    operator const po::variables_map&() const { return config; }

  private:

    static po::options_description
    make_description() {
      po::options_description result("prank options");
      result.add_options()("help,h", "produce this help message");
      return result;
    }

    void
    check_argument_count() {
      if(argc == 1) {
        std::ostringstream oss;
        oss << desc << std::endl;
        throw usage_error(oss.str());
      }
    }

    void
    check_for_help() const {

      if(config.count("help")) {
        std::ostringstream oss;
        oss << desc << std::endl;
        throw help_request(oss.str());
      }
    }
  };

  using arguments = std::vector<std::string>;

  class driver::impl {
    arguments args;
    po::variables_map config;
    int exit_code{};

  public:
    impl(int argc, char** argv)
      : args(argv, argv + argc)
      , config(command_line_processor{argc, argv}) {}

    operator int() const { return exit_code; }
  };

  driver::driver(int argc, char** argv) : pimpl(new impl{argc, argv}) {}
  driver::~driver() { delete pimpl; }
  driver::operator int() const { return int(*pimpl); }

} // end of namespace prank
