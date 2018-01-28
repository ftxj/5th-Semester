#include <iostream>
#include <cstring>
#include <string>
#include <vector>
//二分图匹配问题，匈牙利算法，增广路定理
using namespace std;
int* Matching;
int* check;
int **G;

vector<int> L;
vector<int> R;

bool findMaxMatching();
bool dfs(int u);

int m, n, N, a, b;
int main() {
	cin >> m >> n >> N;
	int totalNode = 0;
	totalNode = m * n - N;
	int *noNode;
	noNode = new int[m * n];
	memset(noNode, 0, m * n * sizeof(int));
	vector<string> res(m, string(n, ' '));

	while (N > 0) {
		cin >> a >> b;
		noNode[a * n + b] = 1;
		N--;
	}
	G = new int*[m * n];

	for (int i = 0; i < m * n; ++i) {
		G[i] = new int[4];
		memset(G[i], -1, 4 * sizeof(int));
	}

	Matching = new int[m * n];
	memset(Matching, -1, m * n * sizeof(int));

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (noNode[i * n + j] == 0) {
				if ((i + j) % 2 == 0) {
					L.push_back(i * n + j);
				}
				else {
					R.push_back(i * n + j);
				}
				// top
				if (i != 0 && noNode[i * n + j - n] == 0) {
					G[i * n + j][0] = i * n + j - n;
				}
				// down
				if (i != n - 1 && noNode[i * n + j + n] == 0) {
					G[i * n + j][1] = i * n + j + n;
				}
				// left
				if (j != 0 && noNode[i * n + j - 1] == 0) {
					G[i * n + j][2] = i * n + j - 1;
				}
				// right
				if (j != n - 1 && noNode[i * n + j + 1] == 0) {
					G[i * n + j][3] = i * n + j + 1;
				}
			}
		}
	}

	if (findMaxMatching()) {
		cout << "true" << endl;
		for (auto i : L) {
			int j = Matching[i];
			if (j + 1 == i || j - 1 == i) {
				res[i / n][i % n] = '#';
				res[j / n][j % n] = '#';
			}
			else {
				res[i / n][i % n] = '0';
				res[j / n][j % n] = '0';
			}
		}
		for (int i = 0; i < m; ++i) {
			cout << res[i] << "\n";
		}
	}
	else {
		cout << "false" << endl;
	}
	return 0;
}

bool dfs(int u) {
	for (int i = 0; i < 4; ++i) {
		if (G[u][i] == -1)
			continue;
		int v = G[u][i];
		if (!check[v]) {
			check[v] = true;
			if (Matching[v] == -1 || dfs(Matching[v])) {
				Matching[v] = u;
				Matching[u] = v;
				return true;
			}
		}
	}
	return false;
}

bool findMaxMatching() {
	int ans = 0;
	if (L.size() != R.size()) {
		return false;
	}
	check = new int[m * n];
	for (int i = 0; i < L.size(); ++i) {
		int node = L[i];
		if (Matching[node] == -1) {
			memset(check, 0, m * n * sizeof(int));
			if (dfs(node)) {
				ans++;
			}
		}
	}
	return ans == L.size();
}