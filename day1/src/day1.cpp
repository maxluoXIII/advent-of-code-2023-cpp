#include <cctype>
#include <iostream>
#include <boost/program_options.hpp>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

namespace po = boost::program_options;

import ArgParser;

int parse_calibration(std::string_view input) {
    int first_digit {};
    int last_digit {};
    bool is_first {true};
    for (const char& c : input) {
        if (isdigit(c)) {
            last_digit = std::stoi(std::string {c});
            if (is_first) {
                first_digit = std::stoi(std::string {c});
                is_first = false;
            }
        }
    }

    return first_digit * 10 + last_digit;
}

int main(int argc, char** argv) {
    std::filesystem::path input_path;
    common::CommandLineResults cli_results = common::parse_command_line(argc, argv);
    if (cli_results.input_path) {
        input_path = cli_results.input_path.value();
    }

    std::ifstream input_stream {input_path};

    std::vector<int> calibrations;
    std::string line;
    int sum {0};
    while (std::getline(input_stream, line)) {
        int calibration = parse_calibration(line);
        sum += calibration;
    }

    std::cout << "Calibration sum: " << sum << "\n";

    return 0;
}
