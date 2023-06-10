#include "CordinatesConverter.h"


b2Vec2 sfmlToBox2D(const sf::Vector2f& vec)
{
	return b2Vec2(vec.x / SCALE, vec.y / SCALE);
}

//--------------------------------------------------

b2Vec2 sfmlToBox2D(const float x, const float y)
{
	return b2Vec2(x / SCALE, y / SCALE);
}

//--------------------------------------------------

float sfmlToBox2D(const float x)
{
	return x / SCALE;
}

//--------------------------------------------------

sf::Vector2f box2DToSFML(const b2Vec2& vec)
{
	return sf::Vector2f(vec.x * SCALE, vec.y * SCALE);
}