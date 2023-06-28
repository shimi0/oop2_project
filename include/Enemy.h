#pragma once

#include <iostream>

#include "Movable.h"
#include "Resources.h"
#include "Animation.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"
#include "Bullet.h"

class Enemy : virtual public GameObject
{
public:
    Enemy();
    virtual ~Enemy() = 0 {}

    virtual void handleCollision(Bullet& obj) override;

    virtual void animate(const sf::Time& deltaTime)
    {
        if(!m_isAlive)
            m_objectBody->SetEnabled(false);
        m_animation.updateBasedOnTime(deltaTime);
    }
protected:

    int m_lives = 1;
    bool m_isAlive = true;
private:

    
};