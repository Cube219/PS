#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
using namespace std;

using lli = long long int;

int n, m;
char map[16][16];
char input[52];
int inputSize;

bool t[16][16];
int px, py;

void Move(char key)
{
	int dx, dy;
	
	if(key == 'U') {
		dx = -1;
		dy = 0;
	} else if(key == 'D') {
		dx = 1;
		dy = 0;
	} else if(key == 'L') {
		dx = 0;
		dy = -1;
	} else {
		dx = 0;
		dy = 1;
	}

	int mvX = px + dx;
	int mvY = py + dy;

	if(map[mvX][mvY] == '.') {
		map[mvX][mvY] = 'w';
		map[px][py] = '.';
		px = mvX;
		py = mvY;
		return;
	}
	if(map[mvX][mvY] == '#') {
		return;
	}

	// map[mvX][mvY] == 'b'인 경우
	int boxMvX = mvX + dx;
	int boxMvY = mvY + dy;
	if(map[boxMvX][boxMvY] == '.') {
		map[boxMvX][boxMvY] = 'b';
		map[mvX][mvY] = 'w';
		map[px][py] = '.';
		px = mvX;
		py = mvY;
		return;
	}
}

bool IsComplete()
{
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(t[i][j] == true && map[i][j] != 'b') {
				return false;
			}
		}
	}
	return true;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	int gameNum = 0;

	while(1) {
		gameNum++;

		scanf("%d %d", &n, &m);
		if(n == 0 && m == 0) break;

		for(int i = 0; i < n; i++) {
			scanf("%s", map[i]);
		}
		scanf("%s", input);
		inputSize = strlen(input);

		px = -1;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				t[i][j] = false;

				if(map[i][j] == 'w' || map[i][j] == 'W') {
					px = i;
					py = j;
				}

				if(map[i][j] == 'B') {
					map[i][j] = 'b';
					t[i][j] = true;
				} else if(map[i][j] == '+') {
					map[i][j] = '.';
					t[i][j] = true;
				} else if(map[i][j] == 'W') {
					map[i][j] = 'w';
					t[i][j] = true;
				}
			}
		}

		for(int i = 0; i < inputSize; i++) {
			Move(input[i]);
			if(IsComplete() == true) break;
		}

		bool isPossible = true;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(t[i][j] == false) continue;

				if(map[i][j] == '.') {
					map[i][j] = '+';
					isPossible = false;
				} else if(map[i][j] == 'w') {
					map[i][j] = 'W';
				} else if(map[i][j] == 'b') {
					map[i][j] = 'B';
				}
			}
		}

		printf("Game %d: ", gameNum);
		if(isPossible == false) {
			printf("incomplete\n");
		} else {
			printf("complete\n");
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				printf("%c", map[i][j]);
			}
			printf("\n");
		}
	}

	return 0;
}
