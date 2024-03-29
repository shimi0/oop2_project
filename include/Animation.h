#pragma once

#include "Direction.h"
#include "AnimationData.h"

#include <SFML/Graphics.hpp>

//Holds and animates the sfml sprites. using time and direction

class Animation
{
public:
    Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite);

    // Set the direction; the sprite will take the relevant texture rect
    void direction(Direction dir);

    // Add more time to the elapsed time; if enough time passed, it
    // updates the sprite to show the next frame in the animation
    void updateBasedOnTime(sf::Time delta);

   // updates the sprite to show the next frame in the animation
    void updateBasedOnCommand();

    bool isEndOfAnimation() const
    {
        return m_data.m_data.find(m_dir)->second.size() - 1 == m_index;
    }

private:
    // Update the sprite to take the correct part of the texture,
    // based on current dir and index
    void update();

    const AnimationData& m_data;
    sf::Time m_elapsed = {};
    Direction m_dir = Direction::Up;
    int m_index = 0;
    sf::Sprite& m_sprite;
};