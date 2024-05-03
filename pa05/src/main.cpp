#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fstream>
#include <nlohmann/json.hpp>

#include "scene.h"

using json = nlohmann::json;

int main(int argc, char** argv) {
    
    fmt::print("\n================================================\n");
    fmt::print("      LuteRT - PLU Educational Ray Tracer\n");
    fmt::print("================================================\n");
    
    if( argc < 2 ) {
        fmt::print("\nUsage: {} scene_file\n", argv[0] );
        return 1;
    }

    std::string input_path = argv[1];
    if( input_path.size() >= 5 && input_path.substr( input_path.size() - 5, 5) != ".json" ) {
        throw LutertException("Input file must have '.json' extension");
    }

    // Read scene file and parse
    fmt::print(fmt::emphasis::bold | fg(fmt::color::light_green),"\nReading scene file: {}\n", input_path);
    std::ifstream input_file( argv[1] );
    json j = json::parse(input_file);

    Scene scn{j};

    // GO!
    fmt::print("\nRendering with {} samples per pixel...\n", scn.samples());
    Image image = scn.render();

    // File name
    std::string file_name = input_path;
    size_t idx = input_path.find_last_of("/\\");
    if( idx != -1 ) {
        file_name = file_name.substr(idx + 1);
    }
    // Remove .json extension
    std::string input_file_base = file_name.substr(0, file_name.size() - 5);

    // Get current date
    auto now = std::chrono::system_clock::now();
    auto local_time = fmt::localtime(std::chrono::system_clock::to_time_t(now));
    std::string date_str = fmt::format("{:%Y%m%d_%H%M%S}", local_time);

    std::string output_file_name = fmt::format("report/renders/{}-{}spp-{}.png", input_file_base, scn.samples(), date_str);

    // Write output
    fmt::print(fmt::emphasis::bold | fg(fmt::color::light_green),"\nWriting image to {}\n", output_file_name);
    image.save_png(output_file_name);
}
