#pragma once
class maze {
public:
	int n;
	int xPlayer, yPlayer;
	maze();
	void setWidth(int width);
	int** mazeGen();
};