#include "PathBrain.h"
#include "Arduino.h"


// ---------------------------------------------------------------------------

void PathBrain::init(double heightA, double widthA, double pickupA, double rumbaA) {
    height = heightA;
    width = widthA;
    pickup = pickupA;
    rumba = rumbaA;

    moveTol = 0.05;
    turnTol = 0.05;
    mode = 'o';
};

void PathBrain::getTolerance(double moveTolA, double turnTolA) {
    moveTol = moveTolA;
    turnTol = turnTolA; 
}

bool PathBrain::isEqual(double a, double b, double tol) {
    if (abs(a - b) < tol)
        return true;
    return false;
}

bool PathBrain::isGreater(double a, double b, double tol) {// a > b
    if (a > b - tol)
        return true;
    return false;
}

char PathBrain::getDir(double x, double y, double dir) {
    Coord user {x,y};

    if (onPath(x,y)) {
        // go dir
    } else {
        return goToPoint(user,dir,Coord{0,0});
        // go to nearest point
    }


    // Serial.print("hi");

    // onPath
    Serial.print(onPath(x,y));
    Serial.print("|");
    Coord tar = nearestPoint(x,y);
    Serial.print(tar.x);
    Serial.print("|");
    Serial.print(tar.y);
    Serial.print("|");
    // if (onPath(x,y)) {
    //     Serial.print("onPath");
    //     Coord tar = nearestPoint(x,y);
    //     return goToPoint(user, dir, tar);
    // }
    // return 's';
    return goToPoint(user,dir,Coord{0,0});
    
    // if (mode == 'o') {
    //     return goToPoint(user, dir, Coord{0,0});
    // }
    // if (mode == 's') {
    //     return 's';
    // }
    // return '2';
};

bool PathBrain::onPath(double x, double y) {
    Coord nearestPt = nearestPoint(x,y);
    if (isEqual(x, nearestPt.x, moveTol) && isEqual(y, nearestPt.y, moveTol))
        return true;
    return false;

    // double k = (x - rumba/2)/(pickup-overlap);
    // if (k == floor(k))
    //     return true; // on the vertical line
    // if (floor(k) / 2 == 0 && y == height - (rumba / 2))
    //     return true; // on the top horizontal
    // if (floor(k) / 2 == 1 && y == (rumba / 2))
    //     return true; // on the bottom horizontal
    // // double tempX 
    // return false;
};

PathBrain::Coord PathBrain::nearestPoint(double x, double y) {
    double k = (x - rumba / 2) / (pickup - overlap);

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

double PathBrain::dist(PathBrain::Coord c1, PathBrain::Coord c2) {
    double x2 = (c1.x - c2.x) * (c1.x - c2.x);
    double y2 = (c1.y - c2.y) * (c1.y - c2.y);
    return sqrt(x2 + y2);
};

double PathBrain::getDirCoords(PathBrain::Coord user, PathBrain::Coord target) {
    return fmod(atan2(target.y - user.y, target.x - user.x) + 2*PI, 2*PI);
};


char PathBrain::goToPoint(PathBrain::Coord user, double dir, PathBrain::Coord tar) {
    /*
        Rotate and go forward to tar until user == tar
    */

    if (isEqual(user.x, tar.x, moveTol) && isEqual(user.y, tar.y, moveTol)) {
        Serial.print("user == tar");
        return 's';
    }

    double targetVector = getDirCoords(user, tar);
    if (!isEqual(dir, targetVector,turnTol)) {
        // Serial.print(getDirCoords(user,tar));
        double left = fmod(targetVector - dir + 2*PI,2*PI);
        double right = fmod(dir - targetVector + 2 * PI, 2 * PI);
        if (left < right)
            return 'l';
        return 'r';
    }

    return 'f';
};

