#include "Button.h"

Button::Button(const AnimationData& data, Direction dir, sf::Sprite& sprite)
	:m_animation(data, dir, sprite)
{

}