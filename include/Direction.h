#pragma once

#include <SFML/Graphics.hpp>

//in use to set an object direction and for the animation class as well.

enum class Direction
{
    Up,
    Down,
    Right,
    Left,
    Stay,
    Max,
};

Direction opposite(Direction dir);
sf::Vector2f toVector(Direction dir);