#pragma once

#include <thread>
#include <atomic>

/**
 * A convenient way to create and display a progress bar in the console.
 * When created, it spawns a thread and updates the progress bar at regular
 * intervals.
 */
class ProgressBar {

public:
    explicit ProgressBar(uint64_t target);
    ~ProgressBar();

    void step( uint64_t steps = 1 ) {
        current_count += steps;
    }

    ProgressBar & operator++() {
        step();
        return *this;
    }

    void set_done() {
        current_count = target_count;
        if( worker_thread.joinable() ) worker_thread.join();
    }

private:
    void run();

    std::string format_duration( double duration ) const;

    std::thread worker_thread;
    uint64_t target_count;
    std::atomic_uint64_t current_count;
};