//
// Created by rambo3441 on 9/15/2021.
//

#ifndef SNAKE_RAYLIB_SEGMENT_H
#define SNAKE_RAYLIB_SEGMENT_H


class Segment {
public:
    float x, y;
    bool isHead = false;
    char direction = 'N';
    int prev = 0;
    char tmpDirection = 'N';

    Segment();
    ~Segment();
    Segment(const Segment &p1);

    void moveHead();

};


#endif //SNAKE_RAYLIB_SEGMENT_H
