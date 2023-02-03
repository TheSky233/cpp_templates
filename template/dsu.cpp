struct DSU{
	std::vector<int> fa, siz;
	DSU(int n): fa(n + 1), siz(n + 1) {iota(fa.begin(), fa.end(), 0);}
	int find(int x) {
		if(x == fa[x]) return x;
		return fa[x] = find(fa[x]);
	}
	bool same(int x, int y) {return find(x) == find(y); }
	bool merge(int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y) return false;
		siz[x] += siz[y];
		fa[y] = x;
		return true;
	}
	int size(int x) {
		return siz[find(x)];
	}
};
