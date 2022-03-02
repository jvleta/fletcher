#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include "panel/geometry.h"

using namespace std;

int main(int argc, char *argv[]) {
  namespace po = boost::program_options;

  try {
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")(
        "input", po::value<std::string>(), "set name of input file");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help")) {
      cout << desc << "\n";
      return 0;
    }
    if (vm.count("input")) {
      cout << "input was set to " << vm["input"].as<std::string>()
           << ".\n";
    } else {
      cout << "inputfile was not set.\n";
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