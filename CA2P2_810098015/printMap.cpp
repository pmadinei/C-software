#include "graphics.h"

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

void printMap(char map[8][8], int positionX, int positionY, char turn) {
	int locs[9];
	/*clearing from last round and coloring the window*/
	cleardevice();
	setfillstyle(1, CYAN);
	floodfill(1, 1, DARKGRAY);
	setcolor(LIGHTGRAY);
	for (int i = 0;i < 9;i++) {
		locs[i] = i * 50 + 50;
	}
	/*drowing main map*/
	for (int i = 0;i < 9;i++) {
		for (int j = 0;j < 9;j++) {
			line(locs[i], locs[j], locs[i], locs[8]);
			line(locs[j], locs[i], locs[8], locs[i]);
		}
	}
	/*drowing circles*/
	setfillstyle(1, WHITE);
	floodfill(1, 1, LIGHTGRAY);
	for (int i = 0;i < 9;i++) {
		for (int j = 0;j < 9;j++) {
			if (map[i][j] == 'W') {
				setcolor(WHITE);
				setfillstyle(1, WHITE);
				circle(locs[j] + 25, locs[i] + 25, 22);
				floodfill(locs[j] + 25, locs[i] + 25, WHITE);
			}
			else if (map[i][j] == 'B') {
				setcolor(BLACK);
				setfillstyle(1, BLACK);
				circle(locs[j] + 25, locs[i] + 25, 22);
				floodfill(locs[j] + 25, locs[i] + 25, BLACK);
			}
			else {
				setcolor(WHITE);
			}
		}
	}
	/*showing scores and turn*/
	char scores[300], turnScript[300];
	sprintf(scores, "scores: [B=%d  W=%d]", score(map, 66), score(map, 87));
	sprintf(turnScript, " turn: %c ", turn);
	settextstyle(9, HORIZ_DIR, 2);
	outtextxy(130, 490, scores);
	settextstyle(3, HORIZ_DIR, 3);
	outtextxy(225, 5, turnScript);
	/*start playing*/
	setcolor(YELLOW);
	rectangle(positionX, positionY, positionX + 50, positionY + 50);
	setfillstyle(LTSLASH_FILL, YELLOW);
	floodfill(positionX + 1, positionY + 1, YELLOW);
	while (!kbhit) {
		delay(200);
	}
}