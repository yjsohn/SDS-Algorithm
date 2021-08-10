#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;
	
	for (int t = 0; t < T; t++) {
		int N;
		cin >> N;

		unordered_set<int> s;

		for (int i = 0; i < N; i++) {
			int n;
			cin >> n;

			s.insert(n);
		}

		int M;
		cin >> M;
		for (int i = 0; i < M; i++) {
			int n;
			cin >> n;

			if (s.find(n) == s.end()) {
				cout << 0 << "\n";
			}
			else {
				cout << 1 << "\n";
			}
		}
	}
	

	return 0;
}