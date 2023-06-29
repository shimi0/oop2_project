#include "ContactListener.h"

ContactListener::ContactListener(Player& player, std::vector<std::unique_ptr<Unmovable>>& unmovableObjVec,
												 std::vector<std::unique_ptr<Movable>>& movableObjVec,
												 std::vector<std::unique_ptr<Platform>>& platformVec,
												 std::vector<std::unique_ptr<Bullet>>& m_bullets)

	:m_player(player), m_unmovableObjVec(unmovableObjVec), m_movableObjVec(movableObjVec), m_platformVec(platformVec), m_bullets(m_bullets)
{}

//---------------------------------------------------------------------

void ContactListener::BeginContact(b2Contact* contact)
{
	if (m_player.isDying() || !m_player.isAlive())
	{
		contact->SetEnabled(false);
		return;
	}

	playerContact(contact);
	bulletContact(contact);
	
	//for any other unexpected collision - ignore the collision.
	contact->SetEnabled(false);	
}

//---------------------------------------------------------------------

void ContactListener::playerContact(b2Contact* contact)
{
	playerPlatformContact(contact);
	playerMovableContact(contact);
	playerUnmovableContact(contact);
}

//---------------------------------------------------------------------

void ContactListener::bulletContact(b2Contact* contact)
{
	auto fixtureBodyA = contact->GetFixtureA()->GetBody();
	auto fixtureBodyB = contact->GetFixtureB()->GetBody();

	for (auto& bullet : m_bullets)
	{
		if (bullet->isSameBody(fixtureBodyA) || bullet->isSameBody(fixtureBodyB))
		{
			bulletMovableContact(fixtureBodyA, fixtureBodyB, bullet);
			bulletUnmovableContact(fixtureBodyA, fixtureBodyB, bullet);
		}
	}
}

//---------------------------------------------------------------------

void ContactListener::playerPlatformContact(b2Contact* contact)
{
	auto fixtureBodyA = contact->GetFixtureA()->GetBody();
	auto fixtureBodyB = contact->GetFixtureB()->GetBody();

	for (auto& platform : m_platformVec) {
		if (m_player.isSameBody(fixtureBodyA) && platform->isSameBody(fixtureBodyB) ||
			m_player.isSameBody(fixtureBodyB) && platform->isSameBody(fixtureBodyA))
		{
			b2WorldManifold worldManifold;
			contact->GetWorldManifold(&worldManifold);
			b2Vec2 contactPoint = worldManifold.points[0];
			auto contPointSFML = box2DToSFML(contactPoint);
			float playerHight = (m_player.getGlobalBounds().height / 2);
			float playerPos = m_player.getPosition().y;
			float playerBottom = m_player.getPosition().y + (m_player.getGlobalBounds().height / 2);

			//if the player is moving up or the collision is with the player body - dont collide (coll shouls be with player's legs only!)
			if (m_player.isMovingUp() || std::abs(contPointSFML.y - playerBottom) > 40)
				contact->SetEnabled(false);
			else
				m_player.handleCollision(*platform);
		}
	}
}

//---------------------------------------------------------------------

void ContactListener::playerMovableContact(b2Contact* contact)
{
	auto fixtureBodyA = contact->GetFixtureA()->GetBody();
	auto fixtureBodyB = contact->GetFixtureB()->GetBody();

	for (auto& movableObj : m_movableObjVec)
		if (m_player.isSameBody(fixtureBodyA) && movableObj->isSameBody(fixtureBodyB) ||
			m_player.isSameBody(fixtureBodyB) && movableObj->isSameBody(fixtureBodyA))
			 m_player.handleCollision(*movableObj);
}

//---------------------------------------------------------------------

void ContactListener::playerUnmovableContact(b2Contact* contact)
{
	auto fixtureBodyA = contact->GetFixtureA()->GetBody();
	auto fixtureBodyB = contact->GetFixtureB()->GetBody();


	for (auto& unmovableObj : m_unmovableObjVec)
		if (m_player.isSameBody(fixtureBodyA) && unmovableObj->isSameBody(fixtureBodyB) ||
			m_player.isSameBody(fixtureBodyB) && unmovableObj->isSameBody(fixtureBodyA))
			 m_player.handleCollision(*unmovableObj);
}

//---------------------------------------------------------------------

void ContactListener::bulletMovableContact(b2Body* fixtureBodyA, b2Body* fixtureBodyB, std::unique_ptr<Bullet>& bullet)
{
	for (auto& movableObj : m_movableObjVec)
		if (movableObj->isSameBody(fixtureBodyA) || movableObj->isSameBody(fixtureBodyB))
			bullet->handleCollision(*movableObj);
}

//---------------------------------------------------------------------

void ContactListener::bulletUnmovableContact(b2Body* fixtureBodyA, b2Body* fixtureBodyB, std::unique_ptr<Bullet>& bullet)
{
	for (auto& unmovableObj : m_unmovableObjVec)
		if (unmovableObj->isSameBody(fixtureBodyA) || unmovableObj->isSameBody(fixtureBodyB))
			bullet->handleCollision(*unmovableObj);
}