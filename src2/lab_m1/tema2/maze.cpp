#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

maze::maze() {
}

void maze::setWidth(int width) {
	n = width;
}

int** maze::mazeGen() {
	int** mazeMatrix = (int**) malloc(n * sizeof(int*));
	for (int i = 0; i <= n; i ++)
		mazeMatrix[i] = (int*) calloc(n, sizeof(int));

	for (int i = 0; i < n; i ++) {
		mazeMatrix[0][i] = 1;
		mazeMatrix[n - 1][i] = 1;
		mazeMatrix[i][0] = 1;
		mazeMatrix[i][n - 1] = 1;
	}

	for (int i = 1; i < n - 3; i ++) {
		int r = rand() % (n - 3);
		mazeMatrix[i][r] = 1;
		mazeMatrix[i][r + 1] = 1;
		mazeMatrix[i][r + 2] = 1;
		mazeMatrix[i][r + 3] = 1;
		mazeMatrix[i + 1][r] = 1;
		mazeMatrix[i + 1][r + 1] = 1;
		mazeMatrix[i + 1][r + 2] = 1;
		mazeMatrix[i + 1][r + 3] = 1;
	}

	int exit1 = rand() % 4;
	int exit2 = rand() % 4;

	if (exit1 == 0 || exit2 == 0)
		mazeMatrix[0][n / 2] = 0;

	if (exit1 == 1 || exit2 == 1)
		mazeMatrix[n / 2][0] = 0;

	if (exit1 == 2 || exit2 == 2)
		mazeMatrix[n / 2][n - 1] = 0;

	if (exit1 == 3 || exit2 == 3)
		mazeMatrix[n - 1][n / 2] = 0;


	int enemiesNo = 9;

	for (int i = 0; i < enemiesNo; i++) {
		int l = rand() % (n - 4) + 2; // linia
		int c = rand() % (n - 4) + 2; // coloana
		while (mazeMatrix[l][c] != 0)
			c = rand() % (n - 4) + 2;
		mazeMatrix[l][c] = 2;
	}

	xPlayer = rand() % (n - 4) + 2;
	yPlayer = rand() % (n - 4) + 2;
	while (mazeMatrix[xPlayer][yPlayer] != 0)
		yPlayer = rand() % (n - 4) + 2;
	mazeMatrix[xPlayer][yPlayer] = 3;

	return mazeMatrix;
}