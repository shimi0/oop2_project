#include "ExplodingPlatform.h"

ExplodingPlatform::ExplodingPlatform(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	: GameObject(Resources::instance().animationData(Resources::ExplodingPlatform), Direction::Stay, m_sprite), Platform(),
	Unmovable(Resources::instance().animationData(Resources::ExplodingPlatform), Direction::Stay, m_sprite)
{
	defineBody(world, bodydef, pos);
	m_sound.setBuffer(AudioResources::Instance().getSound("explodingplatform2.wav"));
	Platform::loadObject();
}

//----------------------------------------

void ExplodingPlatform::animate(const sf::Time& deltaTime)
{
	if (m_animation.isEndOfAnimation())
	{
		if (!m_hasSoundBeenPlayed)
		{
			m_sound.play();
			m_hasSoundBeenPlayed = true;
		}
		m_objectBody->SetEnabled(false);
		m_sprite.setColor(sf::Color::Transparent);
		return;
	}
	m_animation.updateBasedOnTime(deltaTime);

	
		
}

//----------------------------------------

bool ExplodingPlatform::isMovable() const
{
	return false;
}

//----------------------------------------

static auto registerIt = Factory<Platform>::instance().registerType(
	"ExplodingPlatform",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Platform>
	{
		return std::make_unique<ExplodingPlatform>(world, bodydef, pos);
	}
);