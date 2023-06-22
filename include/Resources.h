#pragma once

#include "AnimationData.h"

#include <SFML/graphics.hpp>

#include <vector>

class Resources
{
public:
    enum Objects
    {
        BackGroundClassic,
        DoodleClassic,
        GreenPlatform,
        BluePlatform,
        BlackHoleEnemy,
        FlyingEnemy,
        DeathStars,
        GameOver,
        MenuButton,
        PlayAgainButton,
        Max,
    };

    static Resources& instance();

    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    const sf::Texture& texture() const { return m_texture; }
    const AnimationData& animationData(Objects object) { return m_data[object]; }

private:
    Resources();
    sf::Texture m_texture;
    std::vector<AnimationData> m_data;
};
