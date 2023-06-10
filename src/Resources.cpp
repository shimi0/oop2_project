#include "Resources.h"

#include "Direction.h"

#include <stdexcept>

namespace
{
    AnimationData backGrounClassicdData()
    {
        const auto size = sf::Vector2i(640, 1024);
        const auto initSpace = sf::Vector2i(0, 0);
        const auto middleSpace = sf::Vector2i(0, 0);

        auto classicBG = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += middleSpace;
            currentStart.y += size.y;
            return currentStart;
        };

        classicBG.m_data[Direction::Stay].emplace_back(currentStart, size);
        return classicBG;
    }

    AnimationData doodleClassicData()
    {
        const auto size = sf::Vector2i(124, 120);
        const auto initSpace = sf::Vector2i(640, 0);
        const auto middleSpace = sf::Vector2i(0, 0);

        auto doodleClassic = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += middleSpace;
            currentStart.x += size.x;
            return currentStart;
        };

        doodleClassic.m_data[Direction::Right].emplace_back(currentStart, size);
        doodleClassic.m_data[Direction::Right].emplace_back(nextStart(), size);
        doodleClassic.m_data[Direction::Left].emplace_back(nextStart(), size);
        doodleClassic.m_data[Direction::Left].emplace_back(nextStart(), size);
        doodleClassic.m_data[Direction::Up].emplace_back(nextStart(), size);

        return doodleClassic;
    }

    AnimationData greenPlatform()
    {
        const auto size = sf::Vector2i(116, 34);
        const auto initSpace = sf::Vector2i(1288, 0);
        const auto middleSpace = sf::Vector2i(0, 0);

        auto greenPlatform = AnimationData{};
        auto currentStart = initSpace;

        greenPlatform.m_data[Direction::Stay].emplace_back(currentStart, size);

        return greenPlatform;
    }
}

Resources& Resources::instance()
{
    static Resources instance = Resources();//:)
    return instance;

}

Resources::Resources()
    : m_data(Max)
{
    if (!m_texture.loadFromFile("spritesheet.png"))
    {
        throw std::runtime_error("Can't load file");
    }

    m_data[BackGroundClassic] = backGrounClassicdData();
    m_data[GreenPlatform] = greenPlatform();
    m_data[DoodleClassic] = doodleClassicData();
}
