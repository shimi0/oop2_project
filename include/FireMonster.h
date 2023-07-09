#pragma once

#include "Unmovable.h"
#include "Resources.h"
#include "Animation.h"
#include "Factory.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"
#include "Enemy.h"
#include "Player.h"

//an enmey.

class FireMonster : public Enemy, public Unmovable
{
public:

    FireMonster(std::unique_ptr<b2World>&, b2BodyDef&, const sf::Vector2f&);
    virtual void handleCollision(Player& obj); 

private:

};