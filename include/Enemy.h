#pragma once

#include <iostream>

#include "Movable.h"
#include "Resources.h"
#include "Animation.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"

class Enemy : virtual public GameObject
{
public:
    Enemy();
    virtual ~Enemy() = 0 {}

    

private:


};