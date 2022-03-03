#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include "panel/geometry.h"

using namespace std;

int main(int argc, char *argv[]) {
  namespace po = boost::program_options;

  try {
    po::options_description options("Allowed options");

    options.add_options()("help,h", "produce help message")(
        "input,i", po::value<std::string>(), "set input filename")(
        "output,o", po::value<std::string>(), "set output filename");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, options), vm);
    po::notify(vm);
    
    if (vm.count("help")) {
      cout << options << "\n";
      return 0;
    }
    
    if (vm.count("input")) {
      cout << "input filename was set to " << vm["input"].as<std::string>() << ".\n";
    } else {
      cout << "input filename was not set.\n";
    }

    if (vm.count("output")) {
      cout << "output filename was set to " << vm["output"].as<std::string>() << ".\n";
    } else {
      cout << "output filename was not set.\n";
    }

  } catch (exception &e) {
    cerr << "error: " << e.what() << "\n";
    return 1;
  } catch (...) {
    cerr << "Exception of unknown type!\n";
  }

  return 0;
  // constexpr int num_points = 1000;
  // std::cout << poflow::get_naca00XX_coords(num_points, 0.5);
}