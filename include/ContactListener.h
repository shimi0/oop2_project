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
	ContactListener(Player&, std::vector<std::unique_ptr<Unmovable>>&,
							 std::vector<std::unique_ptr<Movable>>&,
							 std::vector<std::unique_ptr<Platform>>&,
							 std::vector<std::unique_ptr<Bullet>>&);

	//NOTICE: had to comment out	"m_flags |= e_enabledFlag;" in "b2_contact.cpp" to avoid multy sub collisions
	void BeginContact(b2Contact*) override;
	
private:

	void playerContact(b2Contact*);
	void bulletContact(b2Contact*);

	void playerPlatformContact(b2Contact*);
	void playerMovableContact(b2Contact*);
	void playerUnmovableContact(b2Contact*);
	void bulletMovableContact(b2Body*, b2Body*, std::unique_ptr<Bullet>&);
	void bulletUnmovableContact(b2Body*, b2Body*, std::unique_ptr<Bullet>&);

	Player& m_player;

	std::vector<std::unique_ptr<Unmovable>>& m_unmovableObjVec;
	std::vector<std::unique_ptr<Movable>>& m_movableObjVec;
	std::vector<std::unique_ptr<Platform>>& m_platformVec;
	std::vector<std::unique_ptr<Bullet>>& m_bullets;
};