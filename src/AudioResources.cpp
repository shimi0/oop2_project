#include "AudioResources.h"

AudioResources& AudioResources::Instance()
{
    static AudioResources instance = AudioResources();
    return instance;
}

//--------------------------------------------------

sf::SoundBuffer& AudioResources::getSound(const std::string& filename)
{
    if (sounds.find(filename) == sounds.end())
    {
        sf::SoundBuffer soundBuffer;
        if (!soundBuffer.loadFromFile(filename))
            throw std::runtime_error("Couldnt load file: " + filename);
        sounds[filename] = soundBuffer;
    }

    return sounds[filename];
}