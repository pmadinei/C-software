#define ZERO 0
#define ONE 1
#define B 66
#define W 87
#define DOT 46
/*their ASCII codes!*/

void mapInitiator(char map[8][8]) {
	/*making our array map ready for the start*/
	for (int i = 0;i<8;i++) {
		for (int j = 0;j<8;j++) {
			if ((i == 3 && j == 3) || (i == 4 && j == 4))
				map[i][j] = W;
			else if ((i == 4 && j == 3) || (i == 3 && j == 4))
				map[j][i] = B;
			else
				map[i][j] = DOT;
		}
	}
}