#pragma once

#include "box2d/box2d.h"
#include "Player.h"
#include "SimplePlatform.h"
#include "GameObject.h"
#include <vector>

class ContactListener : public b2ContactListener
{
public:
	ContactListener(Player& player, std::vector<SimplePlatform>& simplePlatforms)
	:m_player(player), m_simplePlatdorms(simplePlatforms)
	{}

	void BeginContact(b2Contact* contact)
	{
		auto fixtureBodyA = contact->GetFixtureA()->GetBody();
		auto fixtureBodyB = contact->GetFixtureB()->GetBody();
	
		for (auto& platform : m_simplePlatdorms) {
			if (m_player.isSameBody(fixtureBodyA) && platform.isSameBody(fixtureBodyB))
			{
				m_player.handleCollision(platform);
			}
		}
	}

private:
	Player& m_player;

	std::vector<SimplePlatform>& m_simplePlatdorms;
};