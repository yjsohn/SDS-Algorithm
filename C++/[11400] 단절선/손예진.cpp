#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//단절선: 특정 선을 끊었을 때 연결됐던 정점들이 서로 다른 continent에 속하게 되는 것
//dfs로 정점들 순회하며 방문 순서 결정 -> 단절선 여부 확인

int V, E, idx, order[100001];
vector<pair<int, int>> ans;
vector<int> graph[100001];

int LowestOrder(int node, int parent) {
	order[node] = ++idx;
	int size = graph[node].size();
	int lowest = order[node];
	for (int i = 0; i < size; i++) {
		int next = graph[node][i];
		if (next == parent)
			continue;
		
		if (!order[next]) {	//아직 방문하지 않은 노드
			int tmp = LowestOrder(next, node);
			if (tmp > order[node]) {	//dfs의 return 값을 통해 사이클 여부를 확인
				int a = node, b = next;
				if (a > b)
					swap(a, b);
				ans.push_back({ a, b });
			}
			lowest = min(tmp, lowest);
		}
		else {	//이미 방문한 노드
			lowest = min(lowest, order[next]);
		}
	}
	return lowest;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> V >> E;
	for (int i = 0; i < E; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	for (int i = 1; i <= V; i++) {
		if (order[i] == 0)
			LowestOrder(i, 0);
	}
	sort(ans.begin(), ans.end());

	int size = ans.size();
	cout << size << "\n";
	for (int i = 0; i < size; i++) {
		cout << ans[i].first << " " << ans[i].second << "\n";
	}
}
