#pragma once

#include <iostream>

#include "Movable.h"
#include "Resources.h"
#include "Animation.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"

class Player : public Movable
{
public:

    void updateAnimation()
    {
        if(m_objectBody->GetLinearVelocity().y == 0.f)
            m_animation.updateBasedOnCommand();
    }


    virtual void handleCollision(GameObject& obj)
    {
        jump();
        m_animation.updateBasedOnCommand();
    }

	Player();
	void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override;
    void jump();
	

    void step(const Direction dir, const sf::Time& deltaTime);

	void processKeyInput(const sf::Event& event, const sf::Time& deltaTime);
 

private:

};