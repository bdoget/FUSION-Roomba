#ifndef Map_H
#define Map_H

// #if (ARDUINO >= 100)
#include <Arduino.h>

class Map {

public:
    // all in inches
    Map(float heightA, float widthA, float pickupA, float rumbaA);

    char getDir(float x, float y, float dir);
    bool onPath (float x, float y);
    
    

    // char getDir(posX, posY); // return char f,b,s,l,r
    // bool onPath (posX, posY);
    
private:
    struct Coord {
        float x;
        float y;

    };

    char mode; 
        /*
            o = go to 0,0
            x = go around obstacle
            f = continue path
            g = go to nearest point
            s = stop
        */
    float height, width, pickup, rumba;
    float overlap = 1;

    Coord nearestPoint(float x, float y);
    float dist(Coord x, Coord y);
    float getDir(Coord user, Coord target);
    char goToPoint(Coord user, float dir, Coord tar);

};


#endif

/*
    when on the path, but obstacle. then return the way to turn
    turn until turned 90deg. 
    Move in that way until 



*/