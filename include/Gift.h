#pragma once

#include "Animation.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Factory.h"
#include "Unmovable.h"

class Gift : public Unmovable
{
public:
	Gift(const AnimationData& data, Direction dir, sf::Sprite& sprite);


protected:


private:

};