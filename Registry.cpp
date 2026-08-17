#include "Registry.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <regex>
#include <algorithm>

namespace fs = std::filesystem;

static std::vector<ChallengeData> registry;

void Registry::registerClass(ChallengeData challenge) {
    registry.push_back(challenge);
}

// Helper method to parse a simple JSON key (avoids dependency on heavy JSON libs)
std::string getJsonValue(const std::string& json, const std::string& key) {
    size_t pos = json.find("\"" + key + "\"");
    if (pos == std::string::npos) return "";
    size_t start = json.find(":", pos);
    size_t openQuote = json.find("\"", start);
    size_t closeQuote = json.find("\"", openQuote + 1);
    if (openQuote == std::string::npos || closeQuote == std::string::npos) {
        // Might be a number instead of a string
        size_t end = json.find_first_of(",}", start);
        std::string val = json.substr(start + 1, end - start - 1);
        val.erase(remove(val.begin(), val.end(), ' '), val.end());
        return val;
    }
    return json.substr(openQuote + 1, closeQuote - openQuote - 1);
}

// Separate logic for Year and Day selection
std::pair<int, int> Registry::determineYearAndDay() {
    // 1. Get Year from registry-config.json
    std::ifstream configFile("registry-config.json");
    if (!configFile.is_open()) {
        std::cerr << "Error: Could not open registry-config.json" << std::endl;
        return {2023, 1}; // Fallback
    }
    std::string content((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());
    int year = std::stoi(getJsonValue(content, "selected_year"));

    // 2. Find latest day in ../../Exercises/{year}
    std::string path = "./Exercices/" + std::to_string(year);
    int maxDay = 0;

    if (fs::exists(path)) {
        // Regex to match Ex_{YY}_{day}
        std::regex pattern("Ex_\\d{2}_(\\d+)");
        for (const auto& entry : fs::directory_iterator(path)) {
            std::string filename = entry.path().stem().string();
            std::smatch match;
            if (std::regex_search(filename, match, pattern)) {
                int day = std::stoi(match[1].str());
                if (day > maxDay) maxDay = day;
            }
        }
    }
    else {
      std::cerr << "Path:  " << path << "   DOES NOT EXIST!"; 
    }

    return {year, maxDay};
}

void downloadAocInput(int year, int day, const std::string& targetFile) {
    // Note: You need a file named 'session.txt' with your AOC session cookie
    std::ifstream sessionFile("session.txt");
    std::string session;
    if (sessionFile) {
        std::getline(sessionFile, session);
    } else {
        std::cerr << "Warning: session.txt not found. Download will fail." << std::endl;
        return;
    }

    std::cout << "Downloading input for Year " << year << " Day " << day << "..." << std::endl;
    
    // Construct curl command
    std::string url = "https://adventofcode.com/" + std::to_string(year) + "/day/" + std::to_string(day) + "/input";
    std::string command = "curl -s --cookie \"session=" + session + "\" " + url + " -o " + targetFile;
    
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Failed to download input file." << std::endl;
    }
}

void Registry::instantiateAndRun() {
    for (int i = registry.size() - 1; i > -1; --i) {
        std::unique_ptr<Challenge> obj = registry[i].creator();
        obj->Run(registry[i].inputName);
        std::cout << std::endl << std::endl;
    }
}

void Registry::instantiateAndRunLastOrGivenFile(const std::string& file) {
    int i = registry.size() - 1;
    if (i < 0) return;

    std::string fileName = file;

    // Trigger: Create file and populate if first char is '-'
    if (!file.empty() && file[0] == '-') {
        auto [year, day] = determineYearAndDay();
        
        // Define filename based on what the Registry expects or a default
        fileName = "Inputs/Ex_" + std::to_string(year).substr(2,2) + "_" + std::to_string(day) + "_input.txt";

        // Only download if the file doesn't exist
        if (!fs::exists(fileName)) {
            downloadAocInput(year, day, fileName);
        } else {
            std::cout << "Using existing file: " << fileName << std::endl;
        }
    } else if (file == "") {
        fileName = registry[i].inputName;
    }

    // Now instantiate and run the correct challenge
    std::unique_ptr<Challenge> obj = registry[i].creator();
    obj->Run(fileName);
}