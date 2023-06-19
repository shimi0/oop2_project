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

class Player : public Movable
{
public:

    Player();

    void updateAnimation()
    {
        if(m_objectBody->GetLinearVelocity().y == 0.f)
            m_animation.updateBasedOnCommand();
    }


    virtual void handleCollision(GameObject& obj);
    virtual void handleCollision(Movable& obj);
    virtual void handleCollision(Unmovable& obj);
    virtual void handleCollision(Platform& obj);
    virtual void handleCollision(BlackHoleEnemy& obj);


    bool isMovingUp() const;
	void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override;
    void jump();
    void step(const sf::Time& deltaTime);
	void processKeyInput(const sf::Event& event, const sf::Time& deltaTime);

    sf::Vector2f getBasePosition() const
    {
        return m_basePosition;
    }
 
private:

    //lower number = higher platform
    sf::Vector2f m_basePosition;

};