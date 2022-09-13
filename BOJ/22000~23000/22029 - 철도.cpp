#include "railroad.h"

#include <cassert>
#include <queue>

using ll = long long int;

std::vector<std::pair<int, int> > encode_map(int N, int K, int &X, std::vector<std::pair<int, int> > E) {
	using namespace std;
	vector<vector<int>> g(N + 1);
	for(auto [u, v] : E) {
		g[u].push_back(v);
		g[v].push_back(u);
	}

	auto cal = [&](int rt) -> ll {
		ll res = 0;
		vector<int> dep(N + 1, -1);
		int curDep = 0, num = 0;
		dep[rt] = 0;

		queue<int> q;
		q.push(rt);
		while(!q.empty()) {
			int cur = q.front(); q.pop();
			if(curDep != dep[cur]) {
				if(num > 0) res += num * (num - 1) / 2;
				num = 0;
				curDep = dep[cur];
			}
			num++;

			for(int nxt : g[cur]) {
				if(dep[nxt] != -1) continue;
				dep[nxt] = dep[cur] + 1;
				q.push(nxt);
			}
		}
		if(num > 0) res += num * (num - 1) / 2;
		return res;
	};

	int rt = -1;
	for(int i = 1; i <= N; ++i) {
		if(cal(i) >= K) {
			rt = i;
			break;
		}
	}
	assert(rt != -1);

	vector<pair<int, int>> res;
	vector<int> dep(N + 1, -1), list;
	int curDep = 0;
	dep[rt] = 0;

	queue<int> q;
	q.push(rt);
	while(!q.empty()) {
		int cur = q.front(); q.pop();
		if(curDep != dep[cur]) {
			for(int i = 0; i < list.size() && K > 0; ++i) {
				for(int j = i + 1; j < list.size() && K > 0; ++j) {
					res.push_back({ list[i], list[j] });
					K--;
				}
			}
			curDep = dep[cur];
			list.clear();
		}
		list.push_back(cur);
		if(K == 0) break;

		for(int nxt : g[cur]) {
			if(dep[nxt] != -1) continue;
			dep[nxt] = dep[cur] + 1;
			q.push(nxt);
		}
	}
	for(int i = 0; i < list.size() && K > 0; ++i) {
		for(int j = i + 1; j < list.size() && K > 0; ++j) {
			res.push_back({ list[i], list[j] });
			K--;
		}
	}

	X = rt;
	return res;
}

std::vector<std::pair<int, int> > decode_map(int N, int K, int X, std::vector<std::pair<int, int> > E) {
	using namespace std;
	vector<vector<char>> adj(N + 1, vector<char>(N + 1, false));
	for(auto [u, v] : E) {
		adj[u][v] = adj[v][u] = true;
	}

	vector<int> dep(N + 1, -1), list;
	int curDep = 0;
	dep[X] = 0;
	queue<int> q;
	q.push(X);
	auto eraseAll = [&]() {
		for(int i = 0; i < list.size(); ++i) {
			for(int j = i + 1; j < list.size(); ++j) {
				int u = list[i], v = list[j];
				adj[u][v] = adj[v][u] = false;
			}
		}
	};
	while(!q.empty()) {
		int cur = q.front(); q.pop();
		if(curDep != dep[cur]) {
			eraseAll();
			list.clear();
			curDep = dep[cur];
		}
		list.push_back(cur);

		for(int nxt = 1; nxt <= N; ++nxt) {
			if(adj[cur][nxt] == false || dep[nxt] != -1) continue;
			dep[nxt] = dep[cur] + 1;
			q.push(nxt);
		}
	}
	eraseAll();

	vector<pair<int, int>> res;
	for(int i = 1; i <= N; ++i) {
		for(int j = i + 1; j <= N; ++j) {
			if(adj[i][j]) res.push_back({ i, j });
		}
	}
	return res;
}
