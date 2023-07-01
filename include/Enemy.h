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

class Enemy : virtual public GameObject
{
public:
    Enemy();
    virtual ~Enemy() = 0 {}

    virtual void handleCollision(Bullet& obj) override;

    virtual void animate(const sf::Time& deltaTime)
    {
        if (!m_isAlive) {
            m_objectBody->SetEnabled(false);
            m_sprite.setColor(sf::Color::Transparent);
        }
        m_animation.updateBasedOnTime(deltaTime);
    }

  /*  virtual void handleCollision(Player& obj)
    {
        obj.handleCollision(*this);
    }*/
protected:

    int m_lives = 1;
    bool m_isAlive = true;
    sf::Clock m_clock;

    void loadObject();
private:

    
};