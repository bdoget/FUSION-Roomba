#ifndef Map_H
#define Map_H

// #if (ARDUINO >= 100)
#include <Arduino.h>

class Map
{

public:
    init(height, width, roomba_radius, roomba_eff_width, paper_width);

    getDir(posX, posY);
    bool onPath(posX, posY);

private:
};

#endif

/*
    when on the path, but obstacle. then return the way to turn
    turn until turned 90deg.
    Move in that way until



*/