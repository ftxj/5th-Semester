#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 100000

long long fa[MAXN];
long long co[MAXN];
long long ro[MAXN];
long long su[MAXN];

void init() {
	for (long long i = 0; i < MAXN; ++i) {
		ro[i] = 0;
		fa[i] = i;
		co[i] = 0;
	}
}

long long find(long long u) {
	long long pfa = fa[u];
	if (pfa == u) {
		return u;
	}
	else {
		ro[pfa] = 0;
		fa[u] = find(pfa);
		ro[fa[u]] = 1;
		co[u] = (co[u] + co[pfa]) % 2;
		return fa[u];
	}
}

long long merge(long long u, long long v, int c) {
	long long pu = find(u - 1);
	long long pv = find(v);
	if (pu == pv) {
		if (c != (co[u - 1] ^ co[v])) {
			return 0;
		}
		else {
			return 1;
		}
	}
	fa[v] = pu;
	int old = co[v];
	co[v] = (co[u - 1] + c) % 2;
	ro[pu] = 1;
	if (ro[pv]) {
		if(pu < pv){
			fa[pv] = pu;
			ro[pv] = 0;
			co[pv] = (co[v] ^ old) % 2;
		}
		if(pv < pu){
			fa[pu] = pv;
			ro[pu] = 0;
			co[pu] = (co[v] ^ old) % 2;
		}
	}
	return 1;
}

int main() {
	long long N, Q, u, v, flag = 0, res = 0;
	while(cin >> N){
	cin >> Q;
	vector<long long> left(Q, 0);
	vector<long long> right(Q, 0);
	vector<bool> op(Q, 0);
	map<long long, long long> hash;
	string s;
	res = Q;
	init();
	for (int i = 0; i < Q; ++i) {
		cin >> u >> v >> s;
		left[i] = u;
		right[i] = v;
		op[i] = s != "even";
		hash[u] = 1;
		hash[v] = 1;
	}
	for(map<long long, long long>::iterator i = hash.begin(); i != hash.end(); ++i){
		hash[(*i).first] = ++flag;
	}
	for(int i = 0; i < Q; ++i){
		if(merge(hash[left[i]], hash[right[i]], op[i]) == 0){
			res = i;
			break;
		}
	}
	cout << res << endl;
	}
	return 0;
}