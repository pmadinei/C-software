#include <stdio.h>
#define ZERO 0

int score(char map[8][8], char player) {
	int score = 0;
	/*counting the given player score from map array*/
	for (int i = 0;i<8;i++) {
		for (int j = 0;j<8;j++) {
			if (map[i][j] == player)
				score++;
		}
	}
	return score;
}

void printMap(char map[8][8]) {
	/*printing the map based on updated map array content in every level of game*/
	printf("    1   2   3   4   5   6   7   8\tscores: [b=%d  w=%d]\n", score(map, 66), score(map, 87));
	for (int i = ZERO;i<8;i++) {
		printf("%d  ", (i + 1) * 10);
		for (int j = ZERO;j<8;j++) {
			printf("%c   ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}