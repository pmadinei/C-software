#include <stdio.h>
#include "graphics.h"
#include "checkEndGame.h"
#include "getValidInput.h"
#include "mapChange.h"
#include "mapInitiator.h"
#include "othelloLow.h"
#include "printMap.h"
#include "score_winner.h"

#define ZERO 0
#define ONE 1
#define B 66
#define W 87

/*their ASCII codes!*/


int main() {
	/*defining variables*/
	char map[8][8], turn = 66, winner;
	/*making our map ready for start*/
	mapInitiator(map);
	printf("Let's start!\n\n");
	int wid = ALL_WINDOWS;
	int positionX = 150, positionY = 200;
	initwindow(550, 550, "Othello");
	printMap(map, positionX, positionY, turn);
	/*our main game loop!*/
	do {
		while (getValidInput(map, turn, &positionX, &positionY)!=1) {
			printMap(map, positionX, positionY, turn);
		}
		putInMap(map, &positionX, &positionY, turn);
		mapChange(map);
		/*finding first putable place*/
		int flag = 0;
		for (int i = 0;i < 8;i++) {
			for (int j = 0;j < 8;j++) {
				if ((map[i][j] == '.' && map[i + 1][j] == '.') || (map[i][j] == '.' && map[i][j + 1] == '.') ||
					(map[i][j] == '.' && map[i - 1][j] == '.') || (map[i][j] == '.' && map[i][j - 1] == '.')) {
					positionX = (j * 50) + 50;
					positionY = (i * 50) + 50;
					flag = 1;
					break;
				}
			}
			if (flag == 1)
				break;
		}
		//positionX = 50;
		//positionY = 50;
		if (turn == B)
			turn = W;
		else
			turn = B;
		printMap(map, positionX, positionY, turn);
		
	} while (checkEndGame(map, turn) == ONE);
	/*checks the winner...if we ave one, writes the name, otherwise, it tells DUES!*/
	winner = checkWinner(map);
	printf("The game has finished!\n");
	if (winner != ZERO)
		printf("%c has won the match!\nblack: %d\nwhite: %d\n", winner, score(map, B), score(map, W));
	else
		printf("DUES!\n");
	closegraph(wid);
	return ZERO;
}