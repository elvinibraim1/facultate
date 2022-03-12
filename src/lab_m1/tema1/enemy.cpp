#include "enemy.h"
#include <math.h>
#include <iostream>

#define PI 3.1415926535

using namespace std;

enemy::enemy() {
    x = rand() % 1280;
    y = rand() % 720;
}

float enemy::getAngle(int xEnemy, int yEnemy, int xPlayer, int yPlayer) {

    float angle = 0.0f;
    
    if (xEnemy > xPlayer && yEnemy > yPlayer)
        angle = atan((float)(abs(yEnemy - yPlayer)) / abs(xEnemy - xPlayer));
        
    else if (xEnemy > xPlayer && yEnemy < yPlayer)
        angle = 2 * PI - atan((float)(abs(yEnemy - yPlayer)) / abs((xEnemy - xPlayer)));
        
    else if (xEnemy < xPlayer && yEnemy < yPlayer)
        angle = 3 * PI / 2 - atan((float)(abs(xEnemy - xPlayer)) / abs((yEnemy - yPlayer)));
            
    else if (xEnemy < xPlayer && yEnemy >yPlayer)
        angle = PI / 2 + atan((float)(abs(xEnemy - xPlayer)) / abs(yEnemy- yPlayer));

    return angle;
          
    }