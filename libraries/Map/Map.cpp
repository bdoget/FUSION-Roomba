#include "Map.h"
#include "Arduino.h"


// ---------------------------------------------------------------------------

Map::Map(float heightA, float widthA, float pickupA, float rumbaA) {
    height = heightA;
    width = widthA;
    pickup = pickupA;
    rumba = rumbaA;

    mode = 's';
};

char Map::getDir(float x, float y, float dir) {
    Coord user {x,y};
    if (mode == 'o') {
        return goToPoint(user, dir, Coord{0,0});
    }
    return '1';
};

bool Map::onPath(float x, float y) {
    float k = (x - rumba/2)/(pickup-overlap);
    if (k == floor(k))
        return true; // on the vertical line
    if (floor(k) / 2 == 0 && y == height - (rumba / 2))
        return true; // on the top horizontal
    if (floor(k) / 2 == 1 && y == (rumba / 2))
        return true; // on the bottom horizontal
    // float tempX 
};

Map::Coord Map::nearestPoint(float x, float y) {
    float k = (x - rumba / 2) / (pickup - overlap);

    Coord left{floor(k) * (pickup - overlap) + (rumba / 2), y};
    Coord right{(floor(k)+1)*(pickup-overlap) + (rumba/2), y};

    Coord top{x, 0};
    top.y = (floor(k) / 2 == 0) ? height - (rumba / 2) : rumba/2;

    Coord user{x,y};

    // return min dist from user of : top, left, right
    if (dist(left,user) > dist(right,user))
        left = right;
    if (dist(left,user) < dist(top,user)) 
        return left;
    return top;


};

float Map::dist(Map::Coord c1, Map::Coord c2) {
    float x2 = (c1.x - c2.x) * (c1.x - c2.x);
    float y2 = (c1.y - c2.y) * (c1.y - c2.y);
    return sqrt(x2 + y2);
};

float Map::getDir(Map::Coord user, Map::Coord target) {
    return fmod(atan2(target.y - user.y, target.x - user.x) + PI, PI);
};


char Map::goToPoint(Map::Coord user, float dir, Map::Coord tar) {
    /*
        Rotate and go forward to tar until user == tar
    */

    if (user.x == tar.y && user.y == tar.y) 
        return 's';
    if (dir != getDir(user,tar)) {
        float left = fmod(getDir(user, tar) + PI - dir,PI);
        float right = fmod(dir + PI - getDir(user,tar),PI);
        if (left < right)
            return 'l';
        return 'r';
    }
    return 'f';
};
