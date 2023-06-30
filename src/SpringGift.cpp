#include "SpringGift.h"

SpringGift::SpringGift(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Gift(Resources::instance().animationData(Resources::SpringGift), Direction::Down, m_sprite),
	Unmovable(Resources::instance().animationData(Resources::SpringGift), Direction::Down, m_sprite),
	GameObject(Resources::instance().animationData(Resources::SpringGift), Direction::Down, m_sprite)
{
	defineBody(world, bodydef, pos);
	Gift::loadObject();
	m_sound.setBuffer(AudioResources::Instance().getSound("spring.wav"));
}

//----------------------------------------

void SpringGift::handleCollision(Player& obj)
{
	if (!obj.isAllowedToUseGift()) return;
	if (obj.isMovingUp()) return;

	m_sound.play();
	m_animation.direction(Direction::Up);
	obj.handleCollision(*this);
}

//----------------------------------------

static auto registerIt = Factory<Unmovable>::instance().registerType(
	"SpringGift",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Unmovable>
	{
		return std::make_unique<SpringGift>(world, bodydef, pos);
	}
);