template<typename T>
struct fenwick_tree{
	int _n;
	std::vector<T> tree;
	fenwick_tree(): _n(0) {}
	fenwick_tree(int n): _n(n), tree(n) {}
	inline T lowbit(T x){
		return x & (-x);
	}
	void add(int p, T x) {
		for(; p <= _n; p += lowbit(p))
			tree[p] += x;
	}
	T query(int p) {
		T sum = 0;
		for(; p > 0; p -= lowbit(p))
			sum += tree[p];
		return sum;
	}
	T range(int l, int r) {
		return query(r) - query(l - 1);
	}
};
