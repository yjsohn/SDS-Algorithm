#include <iostream>
#include <vector>
#include <queue>

using namespace std;
vector<int> parent;
struct Edge {
	int start;
	int end;
	int cost;

	Edge(int start, int end, int cost) {
		this->start = start;
		this->end = end;
		this->cost = cost;
	}
};

struct compare {
	bool operator()(Edge a, Edge b) {
		return a.cost > b.cost;
	}
};

int find(int i) {
	if (parent[i] == i) return i;
	else {
		return parent[i] = find(parent[i]);
	}
}

void Union(int a, int b) {
	int pa = parent[a];
	int pb = parent[b];

	parent[pb] = pa;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int V, E;
	cin >> V >> E;

	// �׷����� ������ 1������ V������ ��ȣ�� �Ű��������Ƿ�.
	parent = vector<int>(V + 1);
	// ���� �迭�� �ڱ� �ڽ����� �ʱ�ȭ
	for (int i = 1; i <= V; i++) {
		parent[i] = i;
	}
	priority_queue<Edge, vector<Edge>, compare> pq;

	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		pq.push(Edge(a, b, c));
	}

	int cnt = 0;
	int sum = 0;
	while (!pq.empty()) {
		Edge e = pq.top();
		pq.pop();

		// MST �� Ư¡ ������ ������ V-1���̴�.
		if (cnt == V - 1) {
			break;
		}

		// ��ǥ ������ ���� ������?? => ����Ǿ����� �ʴ�. �����Ű��
		if (find(e.start) != find(e.end)) {
			Union(e.start, e.end);
			cnt++;
			sum += e.cost;
		}
	}

	cout << sum << "\n";
	return 0;
}