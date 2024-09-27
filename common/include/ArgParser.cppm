module;

#include <boost/program_options.hpp>
#include <filesystem>
#include <optional>

export module ArgParser;

namespace po = boost::program_options;

namespace common {
    export struct CommandLineResults {
        std::optional<std::filesystem::path> input_path;
        bool help_requested;
    };

    export CommandLineResults parse_command_line(int argc, char** argv) {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("input", po::value<std::filesystem::path>(), "set input file")
            ("extra", po::value<std::string>(), "extra inputs");

        po::positional_options_description pos_desc;
        pos_desc.add("input", 1);
        pos_desc.add("extra", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pos_desc).run(), vm);
        po::notify(vm);

        std::optional<std::filesystem::path> input_path;
        if (vm.count("input")) {
            input_path = vm["input"].as<std::filesystem::path>();
        }
        return {
            input_path,
            vm.count("help") > 0
        };
    }
};
