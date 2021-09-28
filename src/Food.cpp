//
// Created by rambo3441 on 9/16/2021.
//

#include "Food.h"
#include <iostream>
#include <random>

Food::Food()
{
    Food::x = (rand() % 19) * 30;
    Food::y = (rand() % 19) * 30;
}

Food::~Food()
{
}
