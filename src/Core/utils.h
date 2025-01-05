#pragma once
#include <string>

static std::string getFileNameFromPath(const std::string& filePath) {
    // Find the last occurrence of the directory separator ('/' or '\')
    size_t lastSlashPos = filePath.find_last_of("/\\");

    // If no separator is found, return the full path as the file name
    if (lastSlashPos == std::string::npos) {
        return filePath;
    }

    // Return the substring after the last separator
    return filePath.substr(lastSlashPos + 1);
}