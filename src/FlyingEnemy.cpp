#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Movable(Resources::instance().animationData(Resources::FlyingEnemy), Direction::Stay, m_sprite),
	GameObject(Resources::instance().animationData(Resources::FlyingEnemy), Direction::Stay, m_sprite)
{
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));

	m_objectBody = world->CreateBody(&bodydef);

	loadObject();
}

//----------------------------------------

static auto registerIt = Factory<Movable>::instance().registerType(
	"FlyingEnemy",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Movable>
	{
		return std::make_unique<FlyingEnemy>(world, bodydef, pos);
	}
);


//-------------------------------------------

void FlyingEnemy::loadObject()
{

	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 2.f,2.f });

	//NOTICE: should be divided by 2. not by 6. but turns out to be too big. dont know why... 

	//Y should be m_sprite.getGlobalBounds().height / 2 for the full platform. curentlly it 0.01
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.f);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 10.0f;
	m_objectBody->CreateFixture(&fixtureDef);
	matchSptitePosToBody();
	//m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));

	m_objectBody->SetGravityScale(0.0f);
}

//---------------------------------------------

void FlyingEnemy::step(const sf::Time& deltaTime)
{
	//m_direction = Direction::Right;

	if (box2DToSFML(m_objectBody->GetPosition()).x < 150.f)
		m_direction = Direction::Right;

	if (box2DToSFML(m_objectBody->GetPosition()).x > (WIN_SIZE_X - 150))
		m_direction = Direction::Left;

	

	//will randomly change direction in a specific point
	if ((box2DToSFML(m_objectBody->GetPosition()).x > (WIN_SIZE_X - 500) &&
		box2DToSFML(m_objectBody->GetPosition()).x < (WIN_SIZE_X - 499)) || m_direction == Direction::Stay)
	{
		int num = rand() % 2;
		switch (num)
		{
		case 0:	m_direction = Direction::Left;	break;
		case 1: m_direction = Direction::Right;	break;
		default:								break;
		}
	}
	float desiredVelocity = 0.0f;
	switch (m_direction)
	{
		case Direction::Right: desiredVelocity = 1.5f;       break;
		case Direction::Left:  desiredVelocity = -1.5f;      break;
		case Direction::Stay:  desiredVelocity = 0.0f;       break;
		default:                                             break;
	}

	m_animation.updateBasedOnTime(deltaTime);
	updatePositionX(desiredVelocity);
	matchSptitePosToBody();
}