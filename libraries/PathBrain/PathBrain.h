#ifndef PathBrain_H
#define PathBrain_H

#include <Arduino.h>

class PathBrain {

public:
    // Map() {};
    // all in inches
    void init(double heightA, double widthA, double pickupA, double rumbaA);

    char getDir(double x, double y, double dir); // return char f,b,s,l,r
    bool onPath (double x, double y);
    
    void getTolerance(double moveTolA, double turnTolA);

    bool isEqual(double a, double b, double tol);
    bool isGreater(double a, double b, double tol);
    
private:
    struct Coord {
        double x;
        double y;

    };

    char mode; 
        /*
            o = go to 0,0
            x = go around obstacle
            f = continue path
            g = go to nearest point
            s = stop
        */
    double height, width, pickup, rumba;
    double overlap = 1;
    double moveTol, turnTol;

    Coord nearestPoint(double x, double y);
    double dist(Coord x, Coord y);
    double getDirCoords(Coord user, Coord target);
    char goToPoint(Coord user, double dir, Coord tar);

};


#endif

/*
    when on the path, but obstacle. then return the way to turn
    turn until turned 90deg. 
    Move in that way until 



*/