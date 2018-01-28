#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
struct interval {
	double s;
	double f;
	int w;
	int th;
};
bool cmp(interval a, interval b) {
	return a.f < b.f;
}
int binary_find(vector<interval> &v, int b, int e, double s);
int main() {
	int n;
	cin >> n;

	interval temp;
	int* p = new int[n];
	int* dp = new int[n];
	memset(p, -1, n * sizeof(int));
	memset(dp, 0, n * sizeof(int));
	vector<interval> list;
	vector<int> ll;
	for (int i = 0; i < n; ++i) {
		cin >> temp.s >> temp.f >> temp.w;
		temp.th = i + 1;
		dp[i] = temp.w;
		list.push_back(temp);
	}

	sort(list.begin(), list.end(), cmp);

	for (int i = 0; i < n; ++i) {
		double s = list[i].s;
		p[i] = binary_find(list, 0, i, s);
	}

	for (int i = 1; i < n; ++i) {
		dp[i] = dp[i] > dp[i - 1] ? dp[i] : dp[i - 1];
		if (p[i] != -1) {
			dp[i] = dp[i] > dp[p[i]] + list[i].w ? dp[i] : dp[p[i]] + +list[i].w;
		}
	}
	int res = dp[n - 1];
	int index = n - 1;

	while (res != 0) {
		if (res == dp[index - 1]) {
			index = index - 1;
		}
		else {
			res -= list[index].w;
			ll.push_back(list[index].th);
			index -= 1;
		}
	}

	cout << dp[n - 1] << ":";
	for (auto i : ll) {
		cout << i << " ";
	}
	return 0;
}

int binary_find(vector<interval> &v, int b, int e, double s) {
	if (b >= e) {
		return -1;
	}
	int mid = (b + e) / 2;
	if (v[mid].f > s) {
		e = mid;
	}
	else if (v[mid].f == s || b + 1 == e) {
		return mid;
	}
	else {
		b = mid;
	}
	return binary_find(v, b, e, s);
}