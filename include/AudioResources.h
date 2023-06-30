#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>

class AudioResources {
public:
    static AudioResources& Instance();

    sf::SoundBuffer& getSound(const std::string& filename);

private:

    std::unordered_map<std::string, sf::SoundBuffer> sounds;

    AudioResources(){}
    AudioResources(const AudioResources&) = delete;
    AudioResources& operator=(const AudioResources&) = delete;
};
