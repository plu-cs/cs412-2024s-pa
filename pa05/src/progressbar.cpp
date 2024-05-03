#include <fmt/core.h>
#include <vector>
#include "progressbar.h"

ProgressBar::ProgressBar( uint64_t target) : target_count(target), current_count(0) {
    worker_thread = std::thread( &ProgressBar::run, this );
}

ProgressBar::~ProgressBar() {
    set_done();
}

void ProgressBar::run() {
    using namespace std::literals::chrono_literals;
    static std::vector<std::string> parts = {"", "\u258F", "\u258E", "\u258D", "\u258C", "\u258B", "\u258A", "\u2589"};

    std::fflush(stdout);
    auto sleep_time = 500ms;
    auto bar_size = 50;
    auto total_size = 100;

    auto start_time{std::chrono::steady_clock::now()};

    while( true ) {
        double pct = std::clamp( double(current_count) / target_count, 0.0, 1.0 );

        int segments = int(pct * bar_size * 8);
        int whole_segments = segments / 8;
        int partial_segments = segments % 8;
        int blanks = bar_size - whole_segments;
        std::string part = parts[partial_segments];

        auto current_time{ std::chrono::steady_clock::now()};
        std::chrono::duration<double> elapsed{ current_time - start_time };

        if( current_count >= target_count ) {
            std::string time_str = fmt::format("({})",
                                               format_duration(elapsed.count()));
            int remaining_size = total_size - bar_size - 2 - time_str.length() - 1;
            fmt::print("\r|{:\u2588<{}}| {:<{}}\n", "", bar_size, time_str, remaining_size);
            break;
        } else {
            std::chrono::duration<double> expected{ elapsed / pct };
            if( pct == 0.0 ) expected = 0s;

            std::string time_str = fmt::format("({}/{})",
                                               format_duration(elapsed.count()),
                                               format_duration(expected.count()));
            int remaining_size = total_size - bar_size - 2 - 5 - time_str.length() - 1;
            fmt::print("\r|{:\u2588<{}}{: <{}}|{:4.0f}% {:<{}}", "", whole_segments, part, blanks,
                       pct * 100.0, time_str, remaining_size);
            std::fflush(stdout);

            std::this_thread::sleep_for( sleep_time );
        }
    }

}

std::string ProgressBar::format_duration(double duration) const {
    uint64_t seconds = uint64_t(duration);
    uint64_t minutes = seconds / uint64_t(60);
    uint64_t hours = minutes / uint64_t(60);
    uint64_t days = hours / uint64_t(24);

    if( duration < 10.0 ) {
        return fmt::format("{:.1f}s", duration);
    } else if( minutes == 0 ) {
        return fmt::format("{}s", seconds % 60);
    } else if( hours == 0 ) {
        return fmt::format("{}m{}s", minutes % 60, seconds % 60);
    } else if( days == 0 ) {
        return fmt::format( "{}h{}m{}s", hours % 24, minutes % 60, seconds % 60);
    } else {
        return fmt::format( "{}d{}h{}m{}s", days, hours % 24, minutes % 60, seconds % 60);
    }
}
