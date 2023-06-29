#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Movable(Resources::instance().animationData(Resources::FlyingEnemy), Direction::Stay, m_sprite),
	GameObject(Resources::instance().animationData(Resources::FlyingEnemy), Direction::Stay, m_sprite), m_statrPosition(pos)
{
	defineBody(world, bodydef, pos);

	Enemy::loadObject();
}

//----------------------------------------

static auto registerIt = Factory<Movable>::instance().registerType(
	"FlyingEnemy",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Movable>
	{
		return std::make_unique<FlyingEnemy>(world, bodydef, pos);
	}
);

//---------------------------------------------

void FlyingEnemy::movementBlockingRect()
{
	//horizontal ovement
	if (box2DToSFML(m_objectBody->GetPosition()).x < 150.f)
		m_directionHorizontal = Direction::Right;

	if (box2DToSFML(m_objectBody->GetPosition()).x > (WIN_SIZE_X - 150))
		m_directionHorizontal = Direction::Left;

	//vertical movement
	if (box2DToSFML(m_objectBody->GetPosition()).y < m_statrPosition.y - 200)
		m_directionVertical = Direction::Down;

	if (box2DToSFML(m_objectBody->GetPosition()).y >= m_statrPosition.y + 500)
		m_directionVertical = Direction::Up;
}

//---------------------------------------------

void FlyingEnemy::randomMovement()
{
	int num = rand() % 300;
	switch (num)
	{
		case 0:	m_directionHorizontal = Direction::Left;	break;
		case 1: m_directionHorizontal = Direction::Right;	break;
		case 2: m_directionVertical   = Direction::Up;	    break;
		case 3: m_directionVertical   = Direction::Down;	break;
		case 4: m_directionVertical   = Direction::Stay;	break;
		case 5: m_directionVertical   = Direction::Stay;	break;
		case 6: m_directionVertical   =
		    	m_directionHorizontal = Direction::Stay;	break;
		default:						 					break;
	}
}

//---------------------------------------------

void FlyingEnemy::setVelocity(const Direction& dir, const char axis)
{
	float desiredVelocityX = 0.0f,
		  desiredVelocityY = 0.0f;

	switch (dir)
	{
		case Direction::Right: desiredVelocityX =  1.0f;    break;
		case Direction::Left:  desiredVelocityX = -1.0f;    break;
		case Direction::Down:  desiredVelocityY =  2.0f;    break;
		case Direction::Up:    desiredVelocityY = -1.0f;    break;
		case Direction::Stay: 
			if (axis == 'x')   desiredVelocityX =  0.0f;
			if (axis == 'y')   desiredVelocityY =  0.0f;	break;
		default:                                            break;
	}

	if (axis == 'x') updatePositionX(desiredVelocityX);
	if (axis == 'y') updatePositionY(desiredVelocityY);
}

//---------------------------------------------

void FlyingEnemy::handleCollision(Player& obj)
{
	obj.handleCollision(*this);
}


//---------------------------------------------

void FlyingEnemy::step(const sf::Time& deltaTime)
{
	movementBlockingRect();

	//Randomly change direction - might go out of the blocking rect but should get back quickly
	randomMovement();

	setVelocity(m_directionHorizontal, 'x');
	setVelocity(m_directionVertical, 'y');

	m_animation.updateBasedOnTime(deltaTime);
	matchSptitePosToBody();
}