vector<int> sz(n);
vector<char> visit(n, false);
auto getsz = [&](auto&& self, int cur, int pre) -> int {
	sz[cur] = 1;
	for(int nxt : g[cur]) {
		if(nxt == pre || visit[nxt]) continue;
		sz[cur] += self(self, nxt, cur);
	}
	return sz[cur];
};
auto getcen = [&](auto&& self, int cur, int pre, int size) -> int {
	for(int nxt : g[cur]) {
		if(nxt == pre || visit[nxt]) continue;
		if(sz[nxt] > size / 2) return self(self, nxt, cur, size);
	}
	return cur;
};

auto search = [&](auto&& self, int cur, int pre) -> void {
	for(int nxt : g[cur]) {
		if(nxt == pre || visit[nxt]) continue;
		self(self, nxt, cur);
	}
};

vector<int> cenPar(n);
auto centroid = [&](auto&& self, int cur, int pre) -> void {
	int sz = getsz(getsz, cur, -1);
	int cen = getcen(getcen, cur, -1, sz);

	visit[cen] = true;
	cenPar[cen] = pre;
	search(search, cen, -1);

	for(int nxt : g[cen]) {
		if(nxt == pre || visit[nxt]) continue;
		self(self, nxt, cen);
	}
};
centroid(centroid, 0, -1);
