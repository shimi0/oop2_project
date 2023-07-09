#pragma once

#include "Resources.h"
#include "AudioResources.h"
#include "Animation.h"
#include "Direction.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "box2d/box2d.h"
#include "CordinatesConverter.h"

//a game object base class.

//using forward decleration for double dispatch
class Platform;
class Player;
class Platform;
class BlackHoleEnemy;
class Enemy;
class SpringGift;
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

	//in use to detect an object type in a collision
	bool isSameBody(const b2Body* other) const;

	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	virtual void animate(const sf::Time& deltaTime);

	int getScoreWorth() const;

protected:

	//an item may have a score worth once died/ collide etc.
	int m_scoreWorth = 0;
	
	//each exist using this 3 members:

	//sfml object - graphic object
	sf::Sprite m_sprite;

	//helps animate the graphic object
	Animation m_animation;

	//box2d object
	b2Body* m_objectBody;

private:
};