#pragma once
class enemy {
public:
	int x;
	int y;
	float translateX = 0.0f;
	float translateY = 0.0f ;
	enemy();
	float getAngle(int xEnemy, int yEnemy, int xPlayer, int yPlayer);
};