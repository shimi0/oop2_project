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
#include "Gift.h"
#include "JetPack.h"
#include "PropellerHat.h"

class Player : public Movable
{
public:

    Player();

    void animate(const sf::Time& deltaTime) override;

    virtual void handleCollision(GameObject& obj);
    virtual void handleCollision(Unmovable& obj);
    virtual void handleCollision(Platform& obj);
    virtual void handleCollision(BlackHoleEnemy& obj);
    virtual void handleCollision(FlyingEnemy& obj);
    virtual void handleCollision(FireMonster& obj);
    virtual void handleCollision(SpringGift& obj);
    virtual void handleCollision(JetPack& obj);
    virtual void handleCollision(PropellerHat& obj);

    void deathAnimation(const sf::Time& deltaTime)
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
    void step(const sf::Time& deltaTime) override;
	void processKeyInput(const sf::Event& event, const sf::Time& deltaTime);
    void kill()
    {
        if (!m_isAlive) return;
        jump(0.5);
        m_isAlive = false;
    }

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

    bool hasShotBullet() const
    {
        return m_hasShotBullet;
    }

    void useBullet()
    {
        m_hasShotBullet = false;
    }

    bool isAllowedToUseGift() const
    {
        return !m_isUsingJetPack && !m_isUsingPropellerHat;
    }
private:

    void crossWindow();
    bool m_isJumpinAllowed = true;

    //lower number = higher platform
    sf::Vector2f m_basePosition;
    bool a = false;

    bool m_isAlive = true;
    bool m_isDying = false;
    bool m_wasDying = false;
    bool m_isInvulnerable = false;
    bool m_isUsingPropellerHat = false;
    bool m_isUsingJetPack = false;
    bool m_hasShotBullet = false;
    sf::Clock m_clock;
    sf::Sprite m_spriteDeathStars;
    Animation m_animationDeathStars;
};