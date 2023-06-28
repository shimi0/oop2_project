#pragma once

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

    void deathAnimation(const sf::Time& deltaTime);

    void drawStars(sf::RenderWindow& window);
    bool isMovingUp() const;
	void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override;
    void jump(const float jumpHeightAmount);
    void step(const sf::Time& deltaTime) override;
	void processKeyInput(const sf::Event& event, const sf::Time& deltaTime);
    void kill();
   
    sf::Vector2f getBasePosition() const;
    bool isAlive() const;
    bool isDying() const;
    void playDyingBehavior();
    bool hasShotBullet() const;
    void useBullet();
    bool isAllowedToUseGift() const;

private:

    void crossWindow();
    bool m_isJumpinAllowed = true;

    //lower number = higher platform
    sf::Vector2f m_basePosition;
    bool a = false;

    bool m_isAlive = true;

    //in use for a specific death behavior
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