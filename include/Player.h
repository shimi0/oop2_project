#pragma once

#include <iostream>

#include "Movable.h"
#include "Unmovable.h"
#include "Resources.h"
#include "Platform.h"
#include "Animation.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"
#include "BlackHoleEnemy.h"
#include "FlyingEnemy.h"
#include "SpringGift.h"


class Player : public Movable
{
public:

    Player();

    void updateAnimation()
    {
        if (m_objectBody->GetLinearVelocity().y == 0.f)
        {
            m_animation.updateBasedOnCommand();
        }
    }


    virtual void handleCollision(GameObject& obj);
 //   virtual void handleCollision(Movable& obj);
    virtual void handleCollision(Unmovable& obj);
    virtual void handleCollision(Platform& obj);
    virtual void handleCollision(BlackHoleEnemy& obj);
    virtual void handleCollision(FlyingEnemy& obj);
    virtual void handleCollision(SpringGift& obj);

    void starsAnimation(const sf::Time& deltaTime)
    {
        m_animationDeathStars.updateBasedOnTime(deltaTime);
        m_spriteDeathStars.setPosition(m_sprite.getPosition().x, m_sprite.getGlobalBounds().top);
    }

    void drawStars(sf::RenderWindow& window)
    {
        if(m_wasDying) return;
        window.draw(m_spriteDeathStars);
    }
    bool isMovingUp() const;
	void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override;
    void jump(const float jumpHeightAmount);
    void step(const sf::Time& deltaTime);
	void processKeyInput(const sf::Event& event, const sf::Time& deltaTime);

    sf::Vector2f getBasePosition() const
    {
        return m_basePosition;
    }

    bool isAlive() const
    {
        return m_isAlive;
    }

    bool isDying() const
    {
        return m_isDying;
    }
    
    void playDyingBehavior()
    {
        m_sprite.rotate(5);
        m_sprite.scale({ 0.98,0.98 });

        if (m_sprite.getScale().x < 0.1)
        {
            m_isAlive = false;
            m_wasDying = true;
        }
    }
 
private:

    bool m_isJumpinAllowed = true;
    //lower number = higher platform
    sf::Vector2f m_basePosition;
    bool a = false;

    bool m_isAlive = true;
    bool m_isDying = false;
    bool m_wasDying = false;
    bool m_isInvulnerable = false;

    sf::Sprite m_spriteDeathStars;
    Animation m_animationDeathStars;
};