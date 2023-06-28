#pragma once

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
#include "Player.h"

class FlyingEnemy : public Enemy, public Movable
{
public:

    FlyingEnemy(std::unique_ptr<b2World>&, b2BodyDef&, const sf::Vector2f&);

   
    virtual void step(const sf::Time& deltaTime) override;
    virtual void handleCollision(Player& obj);

private:

    void loadObject();

    void movementBlockingRect();
    void randomMovement();
    void setVelocity(const Direction& dir, const char);

    sf::Vector2f m_statrPosition;


};