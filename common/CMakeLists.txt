add_library(ArgParser)
target_compile_features(ArgParser PUBLIC cxx_std_20)
target_sources(ArgParser
    PUBLIC FILE_SET CXX_MODULES FILES
        include/ArgParser.cppm
)
target_link_libraries(ArgParser Boost::program_options)
