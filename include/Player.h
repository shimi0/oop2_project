#pragma once

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

	Player();
	void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override;
	void setPosition(const sf::Vector2f pos)
	{
		m_sprite.setPosition(pos);
        if (isJumpingUp)
        {
            // Apply upward force
            m_objectBody->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -10.0f), true);
            
            // Check if reaching the peak of the jump
            const float maxUpwardVelocity = -15.0f; // Adjust the value as needed
            const float currentUpwardVelocity = m_objectBody->GetLinearVelocity().y;
            if (currentUpwardVelocity < maxUpwardVelocity)
            {
                m_animation.updateBasedOnCommand();
                b2Vec2 newVelocity = m_objectBody->GetLinearVelocity();
                newVelocity.y = maxUpwardVelocity;
                m_objectBody->SetLinearVelocity(newVelocity);
                isJumpingUp = false;
            }
                
        }
        else
        {
            // Apply downward force
            m_objectBody->ApplyForceToCenter(b2Vec2(0.0f, 40.0f), true);
            if (m_objectBody->GetLinearVelocity().y == 0)
            {
                isJumpingUp = true;
                m_animation.updateBasedOnCommand();
            }
            
        }
        
        m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
	}

	void processKeyInput(const sf::Event& event);
	

private:
    bool isJumpingUp = true;
};