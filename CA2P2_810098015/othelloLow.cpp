int othelloLowSurounded(char map[8][8], int i, int j, char opponent) {
	/*for checking if the character should change*/
	/*checking center*/
	if ((i>0) && (i<7) && (j>0) && (j<7)) {
		if ((map[i - 1][j] == opponent) && (map[i + 1][j] == opponent) && (map[i][j - 1] == opponent) &&
			(map[i][j + 1] == opponent) && (map[i - 1][j - 1] == opponent) && (map[i - 1][j + 1] == opponent) &&
			(map[i + 1][j - 1] == opponent) && (map[i + 1][j + 1] == opponent))
			return 1;
	}
	/*checking corners*/
	else if ((i == 0) && (j == 0)) {
		if ((map[i + 1][j] == opponent) && ((map[i][j + 1] == opponent)) && (map[i + 1][j + 1] == opponent))
			return 1;
	}
	else if ((i == 7) && (j == 7)) {
		if ((map[i - 1][j] == opponent) && ((map[i][j - 1] == opponent)) && (map[i - 1][j - 1] == opponent))
			return 1;
	}
	else if ((i == 0) && (j == 7)) {
		if ((map[i + 1][j] == opponent) && ((map[i][j - 1] == opponent)) && (map[i + 1][j - 1] == opponent))
			return 1;
	}
	else if ((i == 7) && (j == 0)) {
		if ((map[i - 1][j] == opponent) && ((map[i][j + 1] == opponent)) && (map[i - 1][j + 1] == opponent))
			return 1;
	}
	/*checking left wall*/
	else if (j == 0) {
		if ((map[i + 1][j] == opponent) && ((map[i - 1][j] == opponent)) && (map[i][j + 1] == opponent) &&
			(map[i + 1][j + 1] == opponent) && (map[i - 1][j + 1] == opponent))
			return 1;
	}
	/*checking top wall*/
	else if (i == 0) {
		if ((map[i][j + 1] == opponent) && ((map[i][j - 1] == opponent)) && (map[i + 1][j - 1] == opponent) &&
			(map[i + 1][j] == opponent) && (map[i + 1][j + 1] == opponent))
			return 1;
	}
	/*checking buttom wall*/
	else if (i == 7) {
		if ((map[i][j + 1] == opponent) && ((map[i][j - 1] == opponent)) && (map[i - 1][j - 1] == opponent) &&
			(map[i - 1][j] == opponent) && (map[i - 1][j + 1] == opponent))
			return 1;
	}
	/*checking left wall*/
	else if (j == 7) {
		if ((map[i + 1][j] == opponent) && ((map[i - 1][j] == opponent)) && (map[i][j - 1] == opponent) &&
			(map[i + 1][j - 1] == opponent) && (map[i - 1][j - 1] == opponent))
			return 1;
	}
	return 0;
}

int othelloLowInput(char map[8][8], int i, int j, char opponent) {
	/*checking for valid input*/
	if ((map[i - 1][j] == opponent) || (map[i + 1][j] == opponent) || (map[i][j - 1] == opponent) ||
		(map[i][j + 1] == opponent) || (map[i - 1][j - 1] == opponent) || (map[i - 1][j + 1] == opponent) ||
		(map[i + 1][j - 1] == opponent) || (map[i + 1][j + 1] == opponent))
		return 2;
	return 0;
}