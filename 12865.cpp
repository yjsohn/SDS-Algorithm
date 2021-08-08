#include <iostream>
#include <algorithm>

using namespace std;

int N, K, dp[101][100001];
pair<int, int> bag [100001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		int w, v;
		cin >> w >> v;
		bag[i] = { w, v };
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= K; j++) {
			int w = bag[i].first;
			int v = bag[i].second;
			if (j < w)	//j만큼 넣을 수 있는 가방이 i를 넣지 않았을 때 가지는 최대 가중치
				dp[i][j] = dp[i - 1][j];
			else  //"(j - w) 가방의 최댓값 + v" VS. "i를 넣지 않은 j 가방의 최댓값"
				dp[i][j] = max(dp[i - 1][j - w] + v, dp[i - 1][j]);
		}
	}
	cout << dp[N][K] << "\n";

}