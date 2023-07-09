#pragma once

#include "Animation.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Factory.h"
#include "Unmovable.h"
#include "GameObject.h"

//base class for a game gift

class Gift : virtual public GameObject
{
public:

	Gift(const AnimationData& data, Direction dir, sf::Sprite& sprite);

protected:

	void loadObject();

	bool m_hasBeenUsed = false;
	bool m_isInUse = false;

private:
};