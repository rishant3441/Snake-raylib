//
// Created by rambo3441 on 9/16/2021.
//

#include "Food.h"
#include <random>
#include <iostream>

Food::Food()
{
    Food::x = (rand() % 19) * 30;
    Food::y = (rand() % 19) * 30;
}

Food::~Food()
{

}
