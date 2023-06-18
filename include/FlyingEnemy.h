#pragma once

#include <iostream>

#include "Movable.h"
#include "Resources.h"
#include "Animation.h"
#include "Factory.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"
#include "Enemy.h"

class FlyingEnemy : public Enemy, public Movable
{
public:

    FlyingEnemy(std::unique_ptr<b2World>&, b2BodyDef&, const sf::Vector2f&);

   
    virtual void step(const sf::Time& deltaTime) override;


private:

    void loadObject();


};