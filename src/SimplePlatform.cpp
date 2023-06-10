#include "SimplePlatform.h"

SimplePlatform::SimplePlatform()
	: GameObject(Resources::instance().animationData(Resources::GreenPlatform), Direction::Stay, m_sprite), Platform(),
	  Unmovable(Resources::instance().animationData(Resources::GreenPlatform), Direction::Stay, m_sprite)
{}