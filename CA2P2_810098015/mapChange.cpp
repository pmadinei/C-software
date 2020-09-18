#include "othelloLow.h"

void putInMap(char map[8][8], int *positionX , int *positionY, char turn) {
	/*catches the place and character, and change the map array based on that*/
	int i, j;
	i = (*positionX - 50) / 50;
	j = (*positionY - 50) / 50;
	map[j][i] = turn;
}

void mapChange(char map[8][8]) {
	/*with the help of surronded function, could check for if a place is surronded with the opponent,
	and if so, changes the character to opponent's character*/
	int flag = 0;
	for (int i = 0;i<8;i++) {
		for (int j = 0;j<8;j++) {
			if ((map[i][j] == 87) && (othelloLowSurounded(map, i, j, 66) == 1)) {
				map[i][j] = 66;
			}
			else if ((map[i][j] == 66) && (othelloLowSurounded(map, i, j, 87) == 1)) {
				map[i][j] = 87;
			}
		}
	}
}