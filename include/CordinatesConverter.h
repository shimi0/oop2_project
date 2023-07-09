#pragma once

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "macros.h"


//sfml to Box2D / Box2D to sfml conver func

b2Vec2 sfmlToBox2D(const sf::Vector2f& vec);
b2Vec2 sfmlToBox2D(const float x, const float y);
float sfmlToBox2D(const float x);

sf::Vector2f box2DToSFML(const b2Vec2& vec);