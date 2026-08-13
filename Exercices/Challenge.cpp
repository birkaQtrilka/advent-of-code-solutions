#include "Challenge.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  // For std::exit()

void Challenge::Run(const std::string& inputName)
{
    std::ifstream input(inputName);

    if (!input) {
        std::cerr << "Input File for exercise not found! Creating new file..." << inputName << std::endl;
        std::ofstream newFile(inputName);  // This creates a new file
        if (!newFile) {
            std::cerr << "Failed to create file!" << std::endl;
            return;
        }
        newFile.close();
        std::exit(EXIT_SUCCESS);
        return;
    }

    // Continue with the file reading and processing
    Run1(input);
    input.clear();  // Reset stream state
    input.seekg(0, std::ios::beg);  // Rewind to the beginning
    Run2(input);
}

