#include "audio.h"

#include <SDL2/SDL.h>

#include <fstream>
#include <stdexcept>

Audio::Audio() {
    // initialize audio
    int result = SDL_Init(SDL_INIT_AUDIO);
    if (result < 0) {
        throw std::runtime_error(SDL_GetError());
    }

    // initialize mixer
    result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    if (result < 0) {
        throw std::runtime_error(SDL_GetError());
    }
}

Audio::~Audio() {
    // remove existing sounds
    for (auto [name, sound] : sounds) {
        Mix_FreeChunk(sound);
    }

    // Quit SDL2 Mixer
    Mix_CloseAudio();
}

void Audio::load_sounds(const std::string& filename) {
    // remove existing sounds
    for (auto [name, sound] : sounds) {
        Mix_FreeChunk(sound);
    }

    std::ifstream input{filename};
    if (!input) {
        throw std::runtime_error("Could not open filename: " + filename);
    }
    auto i = filename.find('/');
    std::string parent_path{filename.substr(0, i + 1)};

    std::string name, file;
    while (input >> name >> file) {
        std::string full_path = parent_path + file;
        Mix_Chunk* effect = Mix_LoadWAV(full_path.c_str());
        if (!effect) {
            throw std::runtime_error("Unable to load sound from " + full_path);
        }
        sounds[name] = effect;
    }
}

void Audio::play_sound(const std::string& sound_name, bool is_background) {
    auto sound = sounds.find(sound_name);
    if (sound == sounds.end()) {
        throw std::runtime_error("Cannot find sound " + sound_name);
    }
    int result{0};
    if (is_background) {
        result = Mix_PlayChannel(0, sound->second, -1);
    } else {
        result = Mix_PlayChannel(1, sound->second, 0);
    }
    if (result < 0) {
        throw std::runtime_error(sound_name + " cannot be played.");
    }
}
