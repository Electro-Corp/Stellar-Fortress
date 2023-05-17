#include "settings.h"

Settings::Settings(){
}

void Settings::set(const std::string& key, const std::string& value)
{
    m_settingsMap[key] = value;
}// how like intresting

std::string Settings::get(const std::string& key) const
{
    auto it = m_settingsMap.find(key);
    if (it != m_settingsMap.end()) {
        return it->second;
    }
    return "";
} // we will need to load in the keybinds before the game starts because i imagine getting the keys at runtime will not be fast 
// ya, I was thinking this would be more for passing game settings into the game class because there is no good way to go back if you get the game settings in the game class        k makes sense   

//What if i deleted everything - Joseph  
//andrew would be very sad (real)