#pragma once

#include "Movable.h"
#include "Unmovable.h"
#include "AudioResources.h"
#include "Resources.h"
#include "Platform.h"
#include "Animation.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"
#include "BlackHoleEnemy.h"
#include "SpringGift.h"
#include "Gift.h"
#include "JetPack.h"
#include "PropellerHat.h"

class Player : public Movable
{
public:

    Player();

    void animate(const sf::Time&) override;

    virtual void handleCollision(GameObject&);
    virtual void handleCollision(Platform&);
    virtual void handleCollision(BlackHoleEnemy&);
    virtual void handleCollision(Enemy&);
    virtual void handleCollision(SpringGift&);
    virtual void handleCollision(JetPack&);
    virtual void handleCollision(PropellerHat&);

    void deathAnimation(const sf::Time&);

    void drawStars(sf::RenderWindow&);
    bool isMovingUp() const;
	void loadObject(std::unique_ptr<b2World>&, b2BodyDef&) override;
    void jump(const float);
    void step(const sf::Time&) override;
	void processKeyInput(const sf::Event&, const sf::Time&);
    void kill();
   
    sf::Vector2f getBasePosition() const;
    bool isAlive() const;
    bool isDying() const;
    void playDyingBehavior();
    bool hasShotBullet() const;
    void useBullet();
    bool isAllowedToUseGift() const;
    int getScore() const;

private:

    int m_score = 0;
    sf::Sound m_sound;
    sf::Sound m_soundDeath;
    void crossWindow();
    void shootBullet();
    
    bool m_isJumpinAllowed = true;

    //lower number = higher platform
    sf::Vector2f m_basePosition;

    bool m_isAlive = true;

    //in use for a specific death behavior
    bool m_isDying = false;
    bool m_wasDying = false;
    bool m_isInvulnerable = false;
    bool m_isUsingPropellerHat = false;
    bool m_isUsingJetPack = false;
    bool m_hasShotBullet = false;
    bool m_hasSoundBeenPlayed = false;

    sf::Clock m_bulletsClock;
    sf::Clock m_clock;
    sf::Sprite m_spriteDeathStars;
    Animation m_animationDeathStars;
};