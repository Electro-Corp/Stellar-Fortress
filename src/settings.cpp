#include "settings.h"

Settings::Settings(){
}

void Settings::set(const std::string& key, const std::string& value) {
    m_settingsMap[key] = value;
}

std::string Settings::get(const std::string& key) const {
    auto it = m_settingsMap.find(key);
    if (it != m_settingsMap.end()) {
        return it->second;
    }
    return "";
}

int Settings::saveToFile(std::string filename) {
  // TODO
  return 0;
}