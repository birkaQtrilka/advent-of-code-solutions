#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <algorithm>

class Benchmarker {
public:
    explicit Benchmarker(size_t iterations) : iterations_(iterations) {}

    template <typename Callable>
    void addFunction(std::string name, Callable&& func) {
        functions_.push_back({std::move(name), std::forward<Callable>(func)});
    }

    void run() const {
        if (iterations_ == 0) {
            std::cout << "Iteration count is 0. Nothing to benchmark.\n";
            return;
        }

        std::cout << "Starting benchmark with " << iterations_ << " iterations.\n";
        std::cout << std::string(60, '-') << '\n';
        std::cout << std::left << std::setw(25) << "Function Name" 
                  << std::right << std::setw(35) << "Average Time (ns)" << '\n';
        std::cout << std::string(60, '-') << '\n';

        for (const auto& [name, func] : functions_) {
            // Divide the workload into maximum 100 steps to prevent I/O bottleneck
            size_t steps = std::min<size_t>(100, iterations_);
            size_t chunk_size = iterations_ / steps;
            size_t remainder = iterations_ % steps;

            auto total_time = std::chrono::duration<double, std::nano>::zero();

            for (size_t step = 1; step <= steps; ++step) {
                // The last step picks up any remaining iterations
                size_t current_chunk = chunk_size + (step == steps ? remainder : 0);

                // Start clock (only timing the function execution)
                auto start = std::chrono::high_resolution_clock::now();
                
                for (size_t i = 0; i < current_chunk; ++i) {
                    func();
                }

                // Stop clock
                auto end = std::chrono::high_resolution_clock::now();
                total_time += (end - start);

                // Draw the progress bar (clock is paused during this slow I/O)
                int percent = (step * 100) / steps;
                drawProgressBar(name, percent);
            }

            // Calculate final average
            double avg_time = total_time.count() / static_cast<double>(iterations_);

            // Clear the progress bar line using a carriage return (\r) and spaces
            std::cout << "\r" << std::string(80, ' ') << "\r";

            // Print the final result in the table
            std::cout << std::left << std::setw(25) << name 
                      << std::right << std::setw(35) << std::fixed << std::setprecision(3) 
                      << avg_time << '\n';
        }
        std::cout << std::string(60, '-') << '\n';
    }

private:
    size_t iterations_;
    std::vector<std::pair<std::string, std::function<void()>>> functions_;

    // Helper method to draw an inline progress bar
    void drawProgressBar(const std::string& name, int percent) const {
        const int barWidth = 20;
        
        // \r forces the cursor back to the start of the line to overwrite it
        std::cout << "\r" << std::left << std::setw(25) << name << " [";
        
        int pos = (barWidth * percent) / 100;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        
        // std::flush is necessary to force printing before the newline occurs
        std::cout << "] " << std::right << std::setw(3) << percent << "%" << std::flush;
    }
};
