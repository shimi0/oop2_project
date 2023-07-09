#include "BlackHoleEnemy.h"

BlackHoleEnemy::BlackHoleEnemy(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Unmovable(Resources::instance().animationData(Resources::BlackHoleEnemy), Direction::Stay, m_sprite),
	GameObject(Resources::instance().animationData(Resources::BlackHoleEnemy), Direction::Stay, m_sprite)
{
	defineBody(world, bodydef, pos);
	loadObject();
	m_sound.setBuffer(AudioResources::Instance().getSound("blackHole.wav"));
}

//----------------------------------------

static auto registerIt = Factory<Unmovable>::instance().registerType(
	"BlackHoleEnemy",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Unmovable>
	{
		return std::make_unique<BlackHoleEnemy>(world, bodydef, pos);
	}
);

//-------------------------------------------

void BlackHoleEnemy::loadObject()
{
	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 1.6f, 1.6f });
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 15.0f, m_sprite.getGlobalBounds().height / 15.f);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 10.0f;
	m_objectBody->CreateFixture(&fixtureDef);
	m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
}

//----------------------------------------

void BlackHoleEnemy::handleCollision(Player& obj)
{
	obj.handleCollision(*this);
	m_sound.play();
}