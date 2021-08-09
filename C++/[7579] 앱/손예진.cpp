#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
long long dp[101][10001];	//1~i의 앱을 종료했을 때 j만큼의 cost로 얻을 수 있는 최대의 메모리
pair<long long, int> app[101];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> M;

	for (int i = 1; i <= N; i++) {	//memory
		cin >> app[i].first;
	}
	int total_cost = 0;
	for (int i = 1; i <= N; i++) {	//cost
		cin >> app[i].second;
		total_cost += app[i].second;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= total_cost; j++) {
			int c = app[i].second;
			long long m = app[i].first;
			if (c > j)
				dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = max(dp[i - 1][j - c] + m, dp[i - 1][j]);
		}
	}
	for (int j = 0; j <= total_cost; j++) {
		if (dp[N][j] >= M) {
			cout << j << "\n";
			return 0;
		}
	}
}
