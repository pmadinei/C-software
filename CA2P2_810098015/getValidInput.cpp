#include <stdio.h>
#include "othelloLow.h"
#include "printMap.h"

int getValidInput(char map[8][8], char turn,int *positionX,int *positionY) {
	int flag = 0, i, j;
	char validInput,opponent;
	printf("%c, it's your turn!\n", turn);
	if (turn == 66)
		opponent = 87;
	else
		opponent = 66;
	while (flag == 0) {
		scanf("%c", &validInput);
		i = (*positionY - 50) / 50;
		j = (*positionX - 50) / 50;
		/*check out edges*/
		if ((validInput == 'w' && *positionY < 60) || (validInput == 's' && *positionY > 360) || 
			(validInput == 'a' && *positionX < 60) || (validInput == 'd' && *positionX > 360))
			continue;
		/*checking for not crossing filled places*/
	//	if ((map[i + 1][j] != '.' && validInput == 's') || (map[i - 1][j] != '.' && validInput == 'w') ||
		//	(map[i][j + 1] != '.' && validInput == 'd') || (map[i][j - 1] != '.' && validInput == 'a'))
			//continue;
		if (validInput == 'w') {
			*positionY -= 50;
			return 0;
		}
		else if (validInput == 's') {
			*positionY += 50;
			return 0;
		}
		else if (validInput == 'a') {
			*positionX -= 50;
			return 0;
		}
		else if (validInput == 'd') {
			*positionX += 50;
			return 0;
		}
		else if (validInput == ' ') {
			i = (*positionY - 50) / 50;
			j = (*positionX - 50) / 50;
		}
		else
			continue;
		/*checking for near the apponent or not*/
		if (othelloLowInput(map, i, j, opponent) != 2) {
			printf("Not near the opponent! try again\n");
			continue;
		}
		/*checking for already filled places*/
		if (map[i][j] != '.') {
			printf("already filled in!\n");
			continue;
		}
		/*if else, we have a valid input*/
		else if (othelloLowInput(map, i, j, opponent) == 2) {
			flag = 1;
			return 1;
			break;
		}
	}
}