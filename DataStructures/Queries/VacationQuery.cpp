//連続した 0, 1 を数える
struct VacationQuery {
	struct Data {
		int llen0, rlen0, llen1, rlen1;
		int maxlen0, maxlen1;
		int size;
		Data() {}
		Data(int llen0, int rlen0, int llen1, int rlen1, int maxlen0, int maxlen1, int size) : 
			llen0(llen0), rlen0(rlen0), llen1(llen1), rlen1(rlen1), maxlen0(maxlen0), maxlen1(maxlen1), size(size) {}
	};
	using valueTypeT = Data;
	using valueTypeE = int;
	static inline Data ti = Data(0, 0, 0, 0, 0, 0, 0);
	static inline int ei = 0;
	static Data f(const Data &a, const Data &b) {
		Data ans;
		ans.maxlen0 = max({a.maxlen0, b.maxlen0, a.rlen0+b.llen0});
		ans.maxlen1 = max({a.maxlen1, b.maxlen1, a.rlen1+b.llen1});
		ans.llen0 = a.llen0 == a.size ? a.llen0 + b.llen0 : a.llen0;
		ans.llen1 = a.llen1 == a.size ? a.llen1 + b.llen1 : a.llen1;
		ans.rlen0 = b.rlen0 == b.size ? b.rlen0 + a.rlen0 : b.rlen0;
		ans.rlen1 = b.rlen1 == b.size ? b.rlen1 + a.rlen1 : b.rlen1;
		ans.size = a.size + b.size;
		return (ans);
	}
	static Data g(const Data &a, int f) {
		if (!f) return (a);
		return (Data(a.llen1, a.rlen1, a.llen0, a.rlen0, a.maxlen1, a.maxlen0, a.size));
	}
	static int h(int a, int b) {
		return (a^b);
	}
};
