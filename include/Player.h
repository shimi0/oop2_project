#pragma once

#include "Movable.h"
#include "Resources.h"
#include "Animation.h"
#include "macros.h"
#include "box2d/box2d.h"

class Player : public Movable
{
public:

	Player();
	void loadPlayer(std::unique_ptr<b2World>& world, b2BodyDef& bodydef);
	void setPosition(const sf::Vector2f pos)
	{
		m_sprite.setPosition(pos);
		//m_sprite.setPosition(m_playerBody->GetPosition().x * SCALE, m_playerBody->GetPosition().y * SCALE);
	}

	void processKeyInput(const sf::Event& event);
	

private:

	b2Body* m_playerBody;


};