#include "settings.h"
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include <format>
#include <iostream>

Settings::Settings(std::filesystem::path filename) : path{std::filesystem::absolute(filename)} {
    load();
}

void Settings::load() {
    std::ifstream input{path};
    if (!input) {
        std::string msg{"Could not open settings file: "};
        msg += (std::filesystem::current_path() / path).string();
        throw std::runtime_error(msg);
    }

    for (std::string key, value; input >> key >> value;) {
        parameters[key] = value;
    }

    load("title", title);
    load("screen_width", screen_width);
    load("screen_height", screen_height);
    load("tilesize", tilesize);
    load("zoom", zoom);
    load("tiles", tiles);
    load("heros", heros);
    load("monsters", monsters);
    load("weapons", weapons);
    load("items", items);
    load("effects", effects);
    load("sounds", sounds);
    load("map_width", map_width);
    load("map_height", map_height);
    load("room_placement_attempts", room_placement_attempts);
}
