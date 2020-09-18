#include <stdio.h>
#include "othelloLow.h"

#define ZERO 0
#define ONE 1
#define B 66
#define W 87
#define DOT 46
/*their ASCII codes!*/

int checkEndGame(char map[8][8], char turn) {
	int fullOrNot = ONE, doable = ZERO;
	char opponent;
	/*cecking if whole map is full or not*/
	for (int i = 0;i<8;i++) {
		for (int j = 0;j<8;j++) {
			if (map[i][j] == DOT)
				fullOrNot = ZERO;
		}
	}
	if (fullOrNot == ONE) {
		printf("The map is fully covered!\n");
		return 0;
	}

	/*cecking if the free place is suitable for placing*/
	if (turn == B)
		opponent = W;
	else
		opponent = B;
	for (int i = 0;i<8;i++) {
		for (int j = 0;j<8;j++) {
			if (othelloLowInput(map, i, j, opponent) == 2) {
				doable = ONE;
				return ONE;
			}
		}
	}
	/*if not, the game could not be continued*/
	printf("The map has some empty places, althogh you can not play in them!\n");
	return ZERO;
}