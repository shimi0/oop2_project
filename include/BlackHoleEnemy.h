#pragma once

#include "Unmovable.h"
#include "Resources.h"
#include "Animation.h"
#include "Factory.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"
#include "Enemy.h"
#include "Player.h"

//an enemy. kills the player in a collision. not dying from bullets.

class BlackHoleEnemy : public Enemy, public Unmovable
{
public:

    BlackHoleEnemy(std::unique_ptr<b2World>&, b2BodyDef&, const sf::Vector2f&);

    virtual void handleCollision(Player& obj) override;
    virtual void handleCollision(Bullet& obj) override {};

private:

    void loadObject();
    sf::Sound m_sound;
};