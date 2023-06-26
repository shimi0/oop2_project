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
    AnimationData deathStars()
    {
        const auto size = sf::Vector2i(89, 60);
        const auto initSpace = sf::Vector2i(3090, 0);
        const auto middleSpace = sf::Vector2i(10, 0);

        auto deathStars = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += middleSpace;
            currentStart.x += size.x;
            return currentStart;
        };

        deathStars.m_data[Direction::Stay].emplace_back(currentStart, size);
        deathStars.m_data[Direction::Stay].emplace_back(nextStart(), size);
        deathStars.m_data[Direction::Stay].emplace_back(nextStart(), size);

        return deathStars;
    }

    AnimationData explodingPlatform()
    {
        const auto size = sf::Vector2i(116, 30);
        const auto initSpace = sf::Vector2i(1288, 367);
        const auto middleSpace = sf::Vector2i(0, 6);

        auto explodingPlatform = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += middleSpace;
            currentStart.y += size.y;
            return currentStart;
        };

        //we want the explosion to take some time
        for(int i = 0; i < 30; i++)
            explodingPlatform.m_data[Direction::Stay].emplace_back(currentStart, size);
        explodingPlatform.m_data[Direction::Stay].emplace_back(nextStart(), size);
        explodingPlatform.m_data[Direction::Stay].emplace_back(nextStart(), size);
        explodingPlatform.m_data[Direction::Stay].emplace_back(nextStart(), size);
        explodingPlatform.m_data[Direction::Stay].emplace_back(nextStart(), size);
        explodingPlatform.m_data[Direction::Stay].emplace_back(sf::Vector2i(1293, 546), sf::Vector2i(113, 35));
        explodingPlatform.m_data[Direction::Stay].emplace_back(sf::Vector2i(1288, 587), sf::Vector2i(121, 50));
        explodingPlatform.m_data[Direction::Stay].emplace_back(sf::Vector2i(1289, 640), sf::Vector2i(123, 57));

        return explodingPlatform;
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

    AnimationData bluePlatform()
    {
        const auto size = sf::Vector2i(116, 34);
        const auto initSpace = sf::Vector2i(1288, 34);
        const auto middleSpace = sf::Vector2i(0, 0);

        auto greenPlatform = AnimationData{};
        auto currentStart = initSpace;

        greenPlatform.m_data[Direction::Stay].emplace_back(currentStart, size);

        return greenPlatform;
    }

    AnimationData blackHoleEnemy()
    {
        const auto size = sf::Vector2i(148, 140);
        const auto initSpace = sf::Vector2i(1744, 92);

        auto blackHoleEnemy = AnimationData{};
        auto currentStart = initSpace;

        blackHoleEnemy.m_data[Direction::Stay].emplace_back(currentStart, size);

        return blackHoleEnemy;
    }

    AnimationData gameOver()
    {
        const auto size = sf::Vector2i(425, 150);
        const auto initSpace = sf::Vector2i(3380, 205);

        auto gameOver = AnimationData{};
        auto currentStart = initSpace;

        gameOver.m_data[Direction::Stay].emplace_back(currentStart, size);

        return gameOver;
    }

    AnimationData menuButton()
    {
        const auto size = sf::Vector2i(222, 84);
        const auto initSpace = sf::Vector2i(3380, 96);

        auto menuButton = AnimationData{};
        auto currentStart = initSpace;

        menuButton.m_data[Direction::Up].emplace_back(currentStart, size);
        menuButton.m_data[Direction::Down].emplace_back(sf::Vector2i(4625, 0), size);

        return menuButton;
    }

    AnimationData playAgainButton()
    {
        const auto size = sf::Vector2i(222, 92);
        const auto initSpace = sf::Vector2i(3605, 96);

        auto playAgainButton = AnimationData{};
        auto currentStart = initSpace;

        playAgainButton.m_data[Direction::Up].emplace_back(currentStart, size);
        playAgainButton.m_data[Direction::Down].emplace_back(sf::Vector2i(4403, 0), size);

        return playAgainButton;
    }

    AnimationData springGift()
    {
        const auto size = sf::Vector2i(34, 55);
        const auto initSpace = sf::Vector2i(2096, 166);

        auto springGift = AnimationData{};
        auto currentStart = initSpace;

        springGift.m_data[Direction::Down].emplace_back(currentStart, size);
        springGift.m_data[Direction::Up].emplace_back(sf::Vector2i(2096, 230) , size);

        return springGift;
    }

    AnimationData flyingEnemy()
    {
        const auto size = sf::Vector2i(160, 92);
        const auto initSpace = sf::Vector2i(1584, 0);
        const auto middleSpace = sf::Vector2i(0, 0);

        auto flyingEnemy = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += middleSpace;
            currentStart.x += size.x;
            return currentStart;
        };

        flyingEnemy.m_data[Direction::Stay].emplace_back(currentStart, size);
        flyingEnemy.m_data[Direction::Stay].emplace_back(nextStart(), size);
        flyingEnemy.m_data[Direction::Stay].emplace_back(nextStart(), size);
        flyingEnemy.m_data[Direction::Stay].emplace_back(nextStart(), size);
        flyingEnemy.m_data[Direction::Stay].emplace_back(sf::Vector2i(1580, 92), size);

        return flyingEnemy;
    }

    AnimationData pauseButton()
    {
        const auto size = sf::Vector2i(30, 37);
        const auto initSpace = sf::Vector2i(5759, 0);
        auto springGift = AnimationData{};

        springGift.m_data[Direction::Stay].emplace_back(initSpace, size);
        return springGift;
    }

    AnimationData scoreTopClassic()
    {
        const auto size = sf::Vector2i(640, 100);
        const auto initSpace = sf::Vector2i(4848, 0);
        auto scoreTopClassic = AnimationData{};

        scoreTopClassic.m_data[Direction::Stay].emplace_back(initSpace, size);
        return scoreTopClassic;
    }

    AnimationData pauseScreen()
    {
        const auto size = sf::Vector2i(640, 960);
        const auto initSpace = sf::Vector2i(5872, 0);
        auto pauseScreen = AnimationData{};

        pauseScreen.m_data[Direction::Stay].emplace_back(initSpace, size);
        return pauseScreen;
    }

    AnimationData fireMonster()
    {
        const auto size = sf::Vector2i(163, 119);
        auto fireMonster = AnimationData{};

        for(int i = 0; i < 10; i ++)
            fireMonster.m_data[Direction::Stay].emplace_back(sf::Vector2i(1290, 721), size);
        fireMonster.m_data[Direction::Stay].emplace_back(sf::Vector2i(1416, 481), size);
        fireMonster.m_data[Direction::Stay].emplace_back(sf::Vector2i(1416, 601), size);
        fireMonster.m_data[Direction::Stay].emplace_back(sf::Vector2i(1457, 721), size);
        fireMonster.m_data[Direction::Stay].emplace_back(sf::Vector2i(1584, 409), size);
        fireMonster.m_data[Direction::Stay].emplace_back(sf::Vector2i(1457, 721), size);
        fireMonster.m_data[Direction::Stay].emplace_back(sf::Vector2i(1416, 601), size);
        fireMonster.m_data[Direction::Stay].emplace_back(sf::Vector2i(1416, 481), size);
        return fireMonster;
    }

    AnimationData jetPack()
    {
        const auto size = sf::Vector2i(54, 123);
        const auto initSpace = sf::Vector2i(6855, 0);
        auto jetPack = AnimationData{};

        jetPack.m_data[Direction::Stay].emplace_back(sf::Vector2i(1684, 530), sf::Vector2i(48,74));

        jetPack.m_data[Direction::Left].emplace_back(initSpace, size);
        //add more
        return jetPack;
    }

    AnimationData propellerHat()
    {
        const auto size = sf::Vector2i(61, 64);
        auto propellerHat = AnimationData{};

        propellerHat.m_data[Direction::Stay].emplace_back(sf::Vector2i(7108, 0), size);
        propellerHat.m_data[Direction::Up].emplace_back(sf::Vector2i(7173, 0), size);
        propellerHat.m_data[Direction::Up].emplace_back(sf::Vector2i(7108, 72), size);
        propellerHat.m_data[Direction::Up].emplace_back(sf::Vector2i(7173, 72), size);
        //add more
        return propellerHat;
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

    m_data[DeathStars] = deathStars();
    m_data[BackGroundClassic] = backGrounClassicdData();
    m_data[BluePlatform] = bluePlatform();
    m_data[GreenPlatform] = greenPlatform();
    m_data[DoodleClassic] = doodleClassicData();
    m_data[FlyingEnemy] = flyingEnemy();
    m_data[BlackHoleEnemy] = blackHoleEnemy();
    m_data[GameOver] = gameOver();
    m_data[MenuButton] = menuButton();
    m_data[PlayAgainButton] = playAgainButton();
    m_data[SpringGift] = springGift();
    m_data[ExplodingPlatform] = explodingPlatform();
    m_data[PauseButton] = pauseButton();
    m_data[ScoreTopClassic] = scoreTopClassic();
    m_data[PauseScreen] = pauseScreen();
    m_data[FireMonster] = fireMonster();
    m_data[JetPack] = jetPack();
    m_data[PropellerHat] = propellerHat();
}