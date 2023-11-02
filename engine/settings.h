#pragma once

#include <string>
#include <filesystem>
#include <unordered_map>
#include <sstream>

// general settings for game
class Settings {
public:
    Settings(std::filesystem::path filename);

    // absolute file path of settings.txt
    std::filesystem::path path;

    // window parameters
    std::string title;
    int screen_width, screen_height; // screen dimensions in pixels

    // camera parameters
    int tilesize; // number of pixels per tile
    int zoom;     // zoom level of camera

    // dungeon parameters
    int map_width, map_height;
    int room_placement_attempts; // controls the number of rooms
    
    // paths to asset files, relative to settings.txt file
    std::string tiles;
    std::string heros;
    std::string monsters;
    std::string weapons;
    std::string items;
    std::string effects;
    std::string sounds;

private:
    void load();
    std::unordered_map<std::string, std::string> parameters;

    template <typename T>
    void load(const std::string& parameter, T& value) {
        try {
            std::stringstream ss{parameters.at(parameter)};
            ss >> value;
        }
        catch (std::out_of_range& error) {
            throw std::runtime_error("Parameter '" + parameter + "' not found in " + path.string());
        }
    }
};

