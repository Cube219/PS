#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
using namespace std;

using lli = long long int;

int n, m;
int score[100001], penalty[100001];
vector<int> upperTeams;

bool isGreater(int s1, int p1, int s2, int p2)
{
	if(s1 == s2) return p1 < p2;
	else return s1 > s2;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int t, p;
		scanf("%d %d", &t, &p);

		int beforeScore, beforePenalty;
		beforeScore = score[t];
		beforePenalty = penalty[t];
		score[t]++;
		penalty[t] += p;

		if(t != 1) {
			if(isGreater(beforeScore, beforePenalty, score[1], penalty[1]) == false &&
				isGreater(score[t], penalty[t], score[1], penalty[1]) == true) {
				upperTeams.push_back(t);
			}
		} else {
			vector<int> newUpperTeams;
			for(auto team: upperTeams) {
				if(isGreater(score[team], penalty[team], score[1], penalty[1]) == true) {
					newUpperTeams.push_back(team);
				}
			}
			upperTeams = std::move(newUpperTeams);
		}

		printf("%d\n", upperTeams.size() + 1);
	}

	return 0;
}
