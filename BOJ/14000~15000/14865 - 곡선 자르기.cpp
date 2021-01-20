#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>
using namespace std;

int n;

vector<pair<int, int>> d;
stack<int> st;

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d", &n);

	int cColor = 0, cx, cy, startX = -1000000001;
	scanf("%d %d", &cx, &cy);

	int beginX = cx;
	int beginY = cy;

	for(int i = 1; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);

		if(cy < 0 && y > 0) { // 위로
			cColor++;
			startX = x;
		} else if(cy > 0 && y < 0) { // 아래로
			if(startX != -1000000001) {
				d.push_back({ startX, cColor });
			}
			d.push_back({ x, cColor });
		}

		cx = x;
		cy = y;
	}

	if(cy < 0 && beginY > 0) { // 위로
		startX = beginX;
	} else if(cy > 0 && beginY < 0) { // 아래로
		if(startX != -1000000001) {
			d.push_back({ startX, cColor });
		}
		d.push_back({ beginX, cColor });
	}
	cx = beginX;
	cy = beginY;

	if(cy > 0) {
		d.push_back({ startX, 0 });
	}

	sort(d.begin(), d.end());

	int res1 = 0, res2 = 0;

	for(auto iter = d.begin(); iter != d.end(); iter++) {
		int color = iter->second;

		if(st.size() == 0) {
			st.push(color);
			continue;
		}

		if(st.top() == color) {
			if(st.size() == 1) {
				res1++;
			}
			st.pop();
		} else {
			st.push(color);
		}
	}
	int beforeColor = -1;
	for(auto iter = d.begin(); iter != d.end(); iter++) {
		int color = iter->second;

		if(st.size() == 0) {
			st.push(color);
			beforeColor = color;
			continue;
		}

		if(st.top() == color) {
			if(beforeColor == color) {
				res2++;
			}
			st.pop();
		} else {
			st.push(color);
		}

		beforeColor = color;
	}

	printf("%d %d", res1, res2);

	return 0;
}
