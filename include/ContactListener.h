#pragma once

#include "box2d/box2d.h"
#include "Player.h"
#include "SimplePlatform.h"
#include "GameObject.h"
#include <vector>

class ContactListener : public b2ContactListener
{
public:
	ContactListener(Player& player, std::vector<std::unique_ptr<GameObject>>& simplePlatforms)
	:m_player(player), m_simplePlatdorms(simplePlatforms)
	{}																					  //	!!!!!
																						  //	!!!!!
	//TO_DO: add pre solve/ Endcontact function for side - down collision processing!!!!! //	!!!!!
	//			add one way collision!!!												  //	!!!!!
																						  //	!!!!!
	void BeginContact(b2Contact* contact)		
	{
		auto fixtureBodyA = contact->GetFixtureA()->GetBody();
		auto fixtureBodyB = contact->GetFixtureB()->GetBody();
	
		for (auto& platform : m_simplePlatdorms) {
			if (m_player.isSameBody(fixtureBodyA) && platform->isSameBody(fixtureBodyB) ||
				m_player.isSameBody(fixtureBodyB) && platform->isSameBody(fixtureBodyA))
			{
				m_player.handleCollision(*platform);
				
			}
		}
	}

	void EndContact(b2Contact* contact)
	{

	}

private:
	Player& m_player;

	std::vector<std::unique_ptr<GameObject>>& m_simplePlatdorms;
};