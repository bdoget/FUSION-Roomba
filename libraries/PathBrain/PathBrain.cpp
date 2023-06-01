#include "PathBrain.h"
#include "Arduino.h"


// ---------------------------------------------------------------------------

void PathBrain::init(float heightA, float widthA, float pickupA, float rumbaA) {
    height = heightA;
    width = widthA;
    pickup = pickupA;
    rumba = rumbaA;

    mode = 'o';
};

char PathBrain::getDir(float x, float y, float dir) {
    Coord user {x,y};
    if (mode == 'o') {
        return goToPoint(user, dir, Coord{0,0});
    }
    if (mode == 's') {
        return 's';
    }
    return '2';
};

bool PathBrain::onPath(float x, float y) {
    float k = (x - rumba/2)/(pickup-overlap);
    if (k == floor(k))
        return true; // on the vertical line
    if (floor(k) / 2 == 0 && y == height - (rumba / 2))
        return true; // on the top horizontal
    if (floor(k) / 2 == 1 && y == (rumba / 2))
        return true; // on the bottom horizontal
    // float tempX 
};

PathBrain::Coord PathBrain::nearestPoint(float x, float y) {
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

float PathBrain::dist(PathBrain::Coord c1, PathBrain::Coord c2) {
    float x2 = (c1.x - c2.x) * (c1.x - c2.x);
    float y2 = (c1.y - c2.y) * (c1.y - c2.y);
    return sqrt(x2 + y2);
};

float PathBrain::getDirC(PathBrain::Coord user, PathBrain::Coord target) {
    return fmod(atan2(target.y - user.y, target.x - user.x) + PI, PI);
};


char PathBrain::goToPoint(PathBrain::Coord user, float dir, PathBrain::Coord tar) {
    /*
        Rotate and go forward to tar until user == tar
    */

    if (user.x == tar.y && user.y == tar.y) 
        return 's';
    if (dir != getDirC(user,tar)) {
        Serial.print(getDirC(user,tar));
        float left = fmod(getDirC(user, tar) + PI - dir,PI);
        float right = fmod(dir + PI - getDirC(user,tar),PI);
        if (left < right)
            return 'l';
        return 'r';
    }
    return 'f';
};
