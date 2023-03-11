template<typename T>
struct segment_tree{
	#define L(rt) rt << 1
	#define R(rt) rt << 1 | 1 
	const long long INF = numeric_limits<T>::max();
	int n;
	std::vector<T> data, add, down, _min, _max;
	segment_tree(int _n):
		data(_n<<2), add(_n<<2), down(_n<<2), _min(_n<<2), _max(_n<<2) {}
	void pushup(int rt) {
		data[rt] = data[L(rt)] + data[R(rt)];
		_min[rt] = std::min(_min[L(rt)], _min[R(rt)]);
		_max[rt] = std::max(_max[L(rt)], _max[R(rt)]);
	}
	void pushdown(int rt, int l, int r) {
		int mid = (l + r) >> 1;
		if(down[rt] != INF) {
			down[L(rt)] = down[R(rt)] = down[rt];
			_max[L(rt)] = _min[L(rt)] = _max[R(rt)] = _min[R(rt)] = down[rt];
			data[L(rt)] = (mid - l + 1) * down[rt];
			data[R(rt)] = (r - mid) * down[rt];
			add[L(rt)] = add[R(rt)] = 0;
			down[rt] = INF;
		}
		if(add[rt] != 0) {
			_max[L(rt)] += add[rt];
			_min[L(rt)] += add[rt];
			_max[R(rt)] += add[rt];
			_min[R(rt)] += add[rt];
			data[L(rt)] += (mid - l + 1) * add[rt];
			data[R(rt)] += (r - mid) * add[rt];
			add[L(rt)] += add[rt];
			add[R(rt)] += add[rt];
			add[rt] = 0;
		}
	}
	void build(int rt, int l, int r, T *a) {
		add[rt] = 0; down[rt] = INF;
		if(l == r) {
			data[rt] = _min[rt] = _max[rt] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(L(rt), l, mid, a);
		build(R(rt), mid + 1, r, a);
		pushup(rt);
	}
	void update_add(int rt, int l, int r, int L, int R, T delta) {
		if(L <= l && r <= R) {
			_max[rt] += delta;
			_min[rt] += delta;
			data[rt] += (r - l + 1) * delta;
			add[rt] += delta;
			return;
		}
		pushdown(rt, l, r);
		int mid = (l + r) >> 1;
		if(L <= mid) update_add(L(rt), l, mid, L, R, delta);
		if(R > mid) update_add(R(rt), mid + 1, r, L, R, delta);
		pushup(rt);
	}
	void update_down(int rt, int l, int r, int L, int R, T delta) {
		if(L <= l && r <= R) {
			_max[rt] = _min[rt] = delta;
			data[rt] = (r - l + 1) * delta;
			down[rt] = delta;
			add[rt] = 0;
			return;
		}
		pushdown(rt, l, r);
		int mid = (l + r) >> 1;
		if(L <= mid) update_down(L(rt), l, mid, L, R, delta);
		if(R > mid) update_down(R(rt), mid + 1, r, L, R, delta);
		pushup(rt);
	}
	T qmax(int rt, int l, int r, int L, int R) {
		if(L <= l && r <= R) return _max[rt];
		pushdown(rt, l, r);
		int mid = (l + r) >> 1;
		T max_val = std::numeric_limits<T>::min();
		if(L <= mid) max_val = std::max(max_val, qmax(L(rt), l, mid, L, R));
		if(R > mid) max_val = std::max(max_val, qmax(R(rt), mid + 1, r, L, R));
		return max_val;
	}
	T qmin(int rt, int l, int r, int L, int R) {
		if(L <= l && r <= R) return _min[rt];
		pushdown(rt, l, r);
		int mid = (l + r) >> 1;
		T min_val = std::numeric_limits<T>::max();
		if(L <= mid) min_val = std::min(min_val, qmin(L(rt), l, mid, L, R));
		if(R > mid) min_val = std::min(min_val, qmin(R(rt), mid + 1, r, L, R));
		return min_val;
	}
	T query(int rt, int l, int r, int L, int R) {
		if(L <= l && r <= R) return data[rt];
		pushdown(rt, l, r);
		int mid = (l + r) >> 1;
		T val = 0;
		if(L <= mid) val += query(L(rt), l, mid, L, R);
		if(R > mid) val += query(R(rt), mid + 1, r, L, R);
		return val;
	}
};
