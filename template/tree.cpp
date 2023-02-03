struct tree{
	struct edge{
		int to, w, next;
	};
	std::vector<edge> G;
	std::vector<int> head, dep, top, fa, siz, son;
	int cnt, n, m, root;
	tree(int _n, int _m, int _root): 
		G(_m << 1), head(_n + 1), dep(_n + 1), top(_n + 1), fa(_n + 1), siz(_n + 1),
		son(_n + 1), cnt(1), n(_n), m(_m), root(_root) {} 
	void addEdge(int u, int v, int w = 1){
		G[++cnt] = {v, w, head[u]};
		head[u] = cnt;
	}
	void init(){
		dfs1(root); dfs2(root, root);
	}
	void dfs1(int u) {
		siz[u] = 1;
		dep[u] = dep[fa[u]] + 1;
		for(int i = head[u]; i; i = G[i].next){
			int t = G[i].to;
			if(t == fa[u]) continue;
			fa[t] = u;
			dfs1(t);
			siz[u] += siz[t];
			if(son[u] == 0 || siz[t] > siz[son[u]])
				son[u] = t;
		}
	}
	void dfs2(int u, int tp) {
		top[u] = tp;
		if(son[u]) dfs2(son[u], tp);
		for(int i = head[u]; i; i = G[i].next){
			int t = G[i].to;
			if(t == son[u] || t == fa[u]) continue;
			dfs2(t, t);
		}
	}
	int lca(int x, int y){
		while(top[x] != top[y]){
			if(dep[top[x]] > dep[top[y]]) x = fa[top[x]];
			else y = fa[top[y]];
		}
		return dep[x] > dep[y] ? y : x;
	}
};
