#include <iostream>
#include <algorithm>
#include <vector>
#define INF 1000000

using namespace std;

int N, M, ans, cmp[501], dist[501][501];
vector<int> graph[501];

void Floyd() {	//a -> b로 가는 최단 경로 탐색
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

void FindPath() {	//i로 연결된 경로 여부 확인 (i -> j 또는 j -> i). 경로가 없다면 INF 값을 가짐.
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (dist[i][j] != INF || dist[j][i] != INF) {
				cmp[i]++;
			}
		}
		if (cmp[i] == N)	//모든 노드가 i와 연결돼있음
			ans++;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j)
				continue;
			dist[i][j] = INF;
		}
	}
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		dist[a][b] = 1;
	}
	Floyd();
	FindPath();
	cout << ans << "\n";
}
