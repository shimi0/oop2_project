#include "Gift.h"

Gift::Gift(const AnimationData& data, Direction dir, sf::Sprite& sprite)
	:
	Unmovable(data, dir, sprite),
	GameObject(data, dir, sprite)
{
	
}
