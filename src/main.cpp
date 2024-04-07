#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"

#include "GameEngine.h"
#include "Physics.h"
#include "Animation.h"
#include <iostream>

int main()
{
    GameEngine GE("../data/TestECS.txt"); 
    GE.run();
    return 0;
}
