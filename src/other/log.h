#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <filesystem>

class Logger {
public:
    Logger();
    Logger(const std::string& filename);
    ~Logger();
    void log(const std::string& origin, const std::string& text);
    void newl();

private:
    std::string generateRandomFilename();
    std::ofstream file;
};

Logger::Logger() {
    std::string filename = generateRandomFilename();
    std::string directory = "logs";
    std::filesystem::create_directory(directory);
    std::filesystem::path filepath = directory + "/" + filename;
    file.open(filepath, std::ios::out | std::ios::app);
}

Logger::Logger(const std::string& filename) {
    std::string directory = "logs";
    std::filesystem::create_directory(directory);
    std::filesystem::path filepath = directory + "/" + filename + ".log";
    file.open(filepath, std::ios::out | std::ios::app);
}

Logger::~Logger() {
    if (file.is_open())
        file.close();
}

void Logger::log(const std::string& origin, const std::string& text) {
    if (file.is_open()) {
        file << "[" << origin << "]: " << text << std::endl;
        file.flush();
    }
}

std::string Logger::generateRandomFilename() {
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(1000, 9999);
    int randomNum = distribution(rng);

    std::string filename = "log_" + std::to_string(randomNum) + ".log";
    return filename;
}

void Logger::newl() {
  if (file.is_open()) {
        file << std::endl;
        file.flush();
    }
}

#endif  // LOGGER_H
