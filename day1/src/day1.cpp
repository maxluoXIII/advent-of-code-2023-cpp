#include <cctype>
#include <charconv>
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
            last_digit = c - '0';
            if (is_first) {
                first_digit = c - '0';
                is_first = false;
            }
        }
    }

    return first_digit * 10 + last_digit;
}

int parse_calibration_with_words(std::string_view input) {
    int first_digit {};
    int last_digit {};
    bool is_first {true};
    for (size_t i = 0; i < input.length(); ++i) {
        if (isdigit(input.at(i))) {
            last_digit = input.at(i) - '0';
            if (is_first) {
                first_digit = input.at(i) - '0';
                is_first = false;
            }
        } else if (input.substr(i, 3) == "one") {
            last_digit = 1;
            if (is_first) {
                first_digit = 1;
                is_first = false;
            }
        } else if (input.substr(i, 3) == "two") {
            last_digit = 2;
            if (is_first) {
                first_digit = 2;
                is_first = false;
            }
        } else if (input.substr(i, 5) == "three") {
            last_digit = 3;
            if (is_first) {
                first_digit = 3;
                is_first = false;
            }
        } else if (input.substr(i, 4) == "four") {
            last_digit = 4;
            if (is_first) {
                first_digit = 4;
                is_first = false;
            }
        } else if (input.substr(i, 4) == "five") {
            last_digit = 5;
            if (is_first) {
                first_digit = 5;
                is_first = false;
            }
        } else if (input.substr(i, 3) == "six") {
            last_digit = 6;
            if (is_first) {
                first_digit = 6;
                is_first = false;
            }
        } else if (input.substr(i, 5) == "seven") {
            last_digit = 7;
            if (is_first) {
                first_digit = 7;
                is_first = false;
            }
        } else if (input.substr(i, 5) == "eight") {
            last_digit = 8;
            if (is_first) {
                first_digit = 8;
                is_first = false;
            }
        } else if (input.substr(i, 4) == "nine") {
            last_digit = 9;
            if (is_first) {
                first_digit = 9;
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
        int calibration = parse_calibration_with_words(line);
        sum += calibration;
        std::cout << line << " " << calibration << "\n";
    }

    std::cout << "Calibration sum: " << sum << "\n";

    return 0;
}
