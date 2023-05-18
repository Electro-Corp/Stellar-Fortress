#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <unordered_map>

class Settings {
public:
    Settings();

    void set(const std::string& key, const std::string& value);

    std::string get(const std::string& key) const;

    int saveToFile(std::string filename);
private:
    std::unordered_map<std::string, std::string> m_settingsMap;
    
};
#include "settings.cpp"
#endif
