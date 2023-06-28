#pragma once

#include "box2d/box2d.h"
#include "Player.h"
#include "StaticPlatform.h"
#include "Platform.h"
#include "Unmovable.h"
#include "Movable.h"
#include "GameObject.h"
#include "Bullet.h"
#include <vector>

class ContactListener : public b2ContactListener
{
public:
	ContactListener(Player& player, std::vector<std::unique_ptr<Unmovable>>& unmovableObjVec,
									std::vector<std::unique_ptr<Movable>>& movableObjVec,
									std::vector<std::unique_ptr<Platform>>& platformVec,
									std::vector<std::unique_ptr<Bullet>>& m_bullets)
									
	:m_player(player), m_unmovableObjVec(unmovableObjVec), m_movableObjVec(movableObjVec), m_platformVec(platformVec), m_bullets(m_bullets)
	{}		

	//NOTICE: had to comment out	"m_flags |= e_enabledFlag;" in "b2_contact.cpp" to avoid multy sub collisions
	void BeginContact(b2Contact* contact)		
	{
		if (m_player.isDying() || !m_player.isAlive())
		{
			contact->SetEnabled(false);
			return;
		}
		auto fixtureBodyA = contact->GetFixtureA()->GetBody();
		auto fixtureBodyB = contact->GetFixtureB()->GetBody();
	

		//player - platfrom collision
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

		for (auto& movableObj : m_movableObjVec) {
			if (m_player.isSameBody(fixtureBodyA) && movableObj->isSameBody(fixtureBodyB) ||
				m_player.isSameBody(fixtureBodyB) && movableObj->isSameBody(fixtureBodyA))
			{
					m_player.handleCollision(*movableObj);
			}
		}

		for (auto& unmovableObj : m_unmovableObjVec) {
			if (m_player.isSameBody(fixtureBodyA) && unmovableObj->isSameBody(fixtureBodyB) ||
				m_player.isSameBody(fixtureBodyB) && unmovableObj->isSameBody(fixtureBodyA))
			{
					m_player.handleCollision(*unmovableObj);
			}
		}

		for (auto& bullet : m_bullets)
		{
			if(bullet->isSameBody(fixtureBodyA) || bullet->isSameBody(fixtureBodyB))
			{
				for (auto& movableObj : m_movableObjVec)
				{
					if (movableObj->isSameBody(fixtureBodyA) || movableObj->isSameBody(fixtureBodyB))
					{
						bullet->handleCollision(*movableObj);
					}
				}

				for (auto& unmovableObj : m_unmovableObjVec)
				{
					if (unmovableObj->isSameBody(fixtureBodyA) || unmovableObj->isSameBody(fixtureBodyB))
					{
						bullet->handleCollision(*unmovableObj);
					}
				}
			}

			
		}



		contact->SetEnabled(false);		//for any other unexpected collision - ignore it. currently for 2 platfroms collision.
										//	!!!
	}

	void EndContact(b2Contact* contact)
	{
	//	contact->SetEnabled(true);?????????????
	}

private:
	Player& m_player;

	std::vector<std::unique_ptr<Unmovable>>& m_unmovableObjVec;
	std::vector<std::unique_ptr<Movable>>& m_movableObjVec;
	std::vector<std::unique_ptr<Platform>>& m_platformVec;
	std::vector<std::unique_ptr<Bullet>>& m_bullets;
};

//---------------------------------------------------------------

//iforce2d code for one way collision:
//
//void BeginContact(b2Contact* contact)
//{
//    b2Fixture* fixtureA = contact->GetFixtureA();
//    b2Fixture* fixtureB = contact->GetFixtureB();
//
//    //check if one of the fixtures is single-sided
//    b2Fixture* platformFixture = NULL;
//    b2Fixture* otherFixture = NULL;
//    int platformScale = 1;
//    int fudA = (int)fixtureA->GetUserData();
//    int fudB = (int)fixtureB->GetUserData();
//    bool fixtureAIsPlatform = (fudA && fudA < 100);
//    bool fixtureBIsPlatform = (fudB && fudB < 100);
//    if (fixtureAIsPlatform && fixtureBIsPlatform) {
//        contact->SetEnabled(false);//avoids problems with swinging wall
//        return;
//    }
//    else if (fixtureAIsPlatform) {
//        platformFixture = fixtureA;
//        platformScale = fudA;
//        otherFixture = fixtureB;
//    }
//    else if (fixtureBIsPlatform) {
//        platformFixture = fixtureB;
//        platformScale = fudB;
//        otherFixture = fixtureA;
//    }
//
//    bool solid = true;
//
//    if (platformFixture) {
//        int numPoints = contact->GetManifold()->pointCount;
//        b2WorldManifold worldManifold;
//        contact->GetWorldManifold(&worldManifold);
//
//        b2Body* platformBody = platformFixture->GetBody();
//        b2Body* otherBody = otherFixture->GetBody();
//
//        //check if contact points are moving into platform
//        solid = false;
//        for (int i = 0; i < numPoints; i++) {
//            b2Vec2 pointVelPlatform =
//                platformBody->GetLinearVelocityFromWorldPoint(worldManifold.points[i]);
//            b2Vec2 pointVelOther =
//                otherBody->GetLinearVelocityFromWorldPoint(worldManifold.points[i]);
//            b2Vec2 relativeVel = platformBody->GetLocalVector(pointVelOther - pointVelPlatform);
//            if (relativeVel.y < -1)
//                solid = true;//point is moving into platform, leave contact solid
//            else if (relativeVel.y < 1) {
//                //borderline case, moving only slightly out of platform
//                b2Vec2 contactPointRelativeToPlatform =
//                    platformBody->GetLocalPoint(worldManifold.points[i]);
//                float platformFaceY = 0.5f * 1 / (float)platformScale;
//                if (contactPointRelativeToPlatform.y > platformFaceY - 0.05)
//                    solid = true;
//            }
//        }
//    }
//
//    if (solid) {
//        //check if fixture A was the foot
//        void* fixtureUserData = contact->GetFixtureA()->GetUserData();
//        if ((int)fixtureUserData == 100) {
//            m_numFootContacts++;
//        }
//        //check if fixture B was the foot
//        fixtureUserData = contact->GetFixtureB()->GetUserData();
//        if ((int)fixtureUserData == 100) {
//            m_numFootContacts++;
//        }
//    }
//    else
//        //no points are moving into platform, contact should not be solid
//        contact->SetEnabled(false);
//}
//
//void EndContact(b2Contact* contact)
//{
//    if (contact->IsEnabled()) {
//        //check if fixture A was the foot
//        void* fixtureUserData = contact->GetFixtureA()->GetUserData();
//        if ((int)fixtureUserData == 100)
//            m_numFootContacts--;
//        //check if fixture B was the foot
//        fixtureUserData = contact->GetFixtureB()->GetUserData();
//        if ((int)fixtureUserData == 100)
//            m_numFootContacts--;
//    }
//
//    contact->SetEnabled(true);
//}