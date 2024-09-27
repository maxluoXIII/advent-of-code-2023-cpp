add_executable(day1 src/day1.cpp)
target_compile_features(day1 PUBLIC cxx_std_20)
target_link_libraries(day1 Boost::program_options ArgParser)
