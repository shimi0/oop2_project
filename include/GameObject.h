#pragma once

#include "Resources.h"
#include "Animation.h"
#include "Direction.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "CordinatesConverter.h"

class Platform;
class Player;
class Movable;
class Unmovable;
class Platform;
class BlackHoleEnemy;
class Enemy;
class FlyingEnemy;
class SpringGift;
class FireMonster;
class JetPack;
class PropellerHat;
class Bullet;

class GameObject
{
public:

	GameObject(const AnimationData& data, Direction dir, sf::Sprite& sprite);
	virtual ~GameObject() = 0 {}
	void draw(sf::RenderWindow& m_window) const;
	virtual void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) = 0;
	virtual void handleCollision(GameObject& obj) {};
	virtual void handleCollision(JetPack& obj) {};
	virtual void handleCollision(Player& obj) {};
	virtual void handleCollision(Platform& obj) {};
	virtual void handleCollision(SpringGift& obj) {};
	virtual void handleCollision(BlackHoleEnemy& obj) {};
	virtual void handleCollision(PropellerHat& obj) {};
	virtual void handleCollision(Bullet& obj) {};
	virtual void handleCollision(Enemy& obj) {};

	bool isSameBody(const b2Body* other) const;
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	virtual void animate(const sf::Time& deltaTime);

protected:

	sf::Sprite m_sprite;
	Animation m_animation;
	b2Body* m_objectBody;

private:
};