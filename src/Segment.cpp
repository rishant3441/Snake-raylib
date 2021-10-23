//
// Created by rambo3441 on 9/15/2021.
//

#include "Segment.h"
#include "raylib.h"

Segment::Segment()
{
    Segment::x = 10 * 30;
    Segment::y = 10 * 30;
    Segment::isHead = false;
}

Segment::~Segment() = default;

void Segment::moveHead()
{
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
    {
        if (Segment::tmpDirection == Segment::direction)
            Segment::tmpDirection = Segment::direction;
        Segment::direction = 'N';
    }
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
    {
        if (Segment::tmpDirection == Segment::direction)
            Segment::tmpDirection = Segment::direction;
        Segment::direction = 'S';
    }
    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
    {
        if (Segment::tmpDirection == Segment::direction)
            Segment::tmpDirection = Segment::direction;
        Segment::direction = 'W';
    }
    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
    {
        if (Segment::tmpDirection == Segment::direction)
            Segment::tmpDirection = Segment::direction;
        Segment::direction = 'E';
    }
}
Segment::Segment(const Segment &p1)
{
    x = p1.x;
    y = p1.y;
    isHead = false;
}
