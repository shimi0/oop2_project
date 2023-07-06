#pragma once

#include "GameObject.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

template <typename T>
class Factory
{
public:
    static Factory& instance()
    {
        static auto instance = Factory();
        return instance;
    }

    using FuncType = std::unique_ptr<T>(*)(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos);
    bool registerType(std::string type, FuncType f)
    {
        m_map.emplace(type, f);
        return true;
    }

    std::unique_ptr<T> create(std::string type, std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) const
    {
        if (!m_map.contains(type)) return nullptr;
        return m_map.at(type)(world, bodydef, pos);
    }

private:
    Factory() = default;
    Factory(const Factory&) = delete;
    void operator=(const Factory&) = delete;

    std::unordered_map<std::string, FuncType> m_map;
};