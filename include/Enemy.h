#pragma once

#include "Movable.h"
#include "Resources.h"
#include "Animation.h"
//#include "Player.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"
#include "Bullet.h"

//the base class for an enemy object

class Enemy : virtual public GameObject
{
public:

    Enemy();
    virtual ~Enemy() = 0 {}

    virtual void handleCollision(Bullet& obj) override;

    virtual void animate(const sf::Time& deltaTime) override;

protected:

    int m_lives = 1;
    bool m_isAlive = true;
    sf::Clock m_clock;

    void loadObject();

private:

};