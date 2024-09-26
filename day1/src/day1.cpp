#include <cctype>
#include <cstdlib>
#include <iostream>
#include <boost/program_options.hpp>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

namespace po = boost::program_options;

int parse_calibration(std::string_view input) {
    int first_digit {};
    int last_digit {};
    bool is_first {true};
    for (const char& c : input) {
        if (isdigit(c)) {
            last_digit = std::atoi(&c);
            if (is_first) {
                first_digit = std::atoi(&c);
                is_first = false;
            }
        }
    }

    return first_digit * 10 + last_digit;
}

int main(int argc, char **argv) {
    std::cout << "Hello 1\n";

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("input", po::value<std::filesystem::path>(), "set input file")
        ("extra", po::value<std::string>(), "extra inputs");

    po::positional_options_description pos_des;
    pos_des.add("input", 1);
    pos_des.add("extra", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(pos_des).run(), vm);
    po::notify(vm);

    std::cout << "Hello 2\n";

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    std::filesystem::path input_path;
    if (vm.count("extra")) {
        std::cout << "Too many files specified.\n";
    } else if (vm.count("input")) {
        input_path = vm["input"].as<std::filesystem::path>();
        std::cout << "Input file: " << input_path << "\n";
    } else {
        std::cout << "Input file was not set.\n";
    }

    if (std::filesystem::exists(input_path)) {
        std::cout << "Input file exists!\n";
    }

    std::ifstream input_stream {input_path};

    std::vector<int> calibrations;
    std::string line;
    int sum {0};
    while (std::getline(input_stream, line)) {
        int calibration = parse_calibration(line);
        sum += calibration;
        std::cout << line << " " << calibration << "\n";
    }

    std::cout << sum << "\n";

    return 0;
}
