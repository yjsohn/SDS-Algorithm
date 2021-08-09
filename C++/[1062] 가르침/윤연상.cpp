#include <bits/stdc++.h>

using namespace std;

int n, k;
bool selected[26];				// 선택된 알파벳 저장
vector<string> words;			// 단어 

int dfs(int idx, int count);
int check_word();

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		words.push_back(s);
	}

	// anta + tica => a, n, t, i, c (5개)는 무조건 선택
	for (int i = 0; i < 26; i++) {
		selected[i] = false;
	}
	selected['a' - 'a'] = true; selected['n' - 'a'] = true;
	selected['t' - 'a'] = true; selected['i' - 'a'] = true;
	selected['c' - 'a'] = true;

	// k가 5보다 작으면 무조건 0
	if (k >= 5)
		cout << dfs(0, 0);
	else
		cout << 0;
}

// dfs 수행해서 k-5개의 알파벳 선택
int dfs(int idx, int count) {
	if (count == k - 5) {
		return check_word();	// 알파벳 모두 선택한 다음 읽을 수 있는 단어 확인
	}

	int retval = 0;

	for (int i = idx; i < 26; i++) {
		if (selected[i])
			continue;
		selected[i] = true;
		retval = max(retval, dfs(i, count + 1));
		selected[i] = false;
	}

	return retval;
}

// 현재 선택된 알파벳(selected배열) 기준으로 읽을 수 있는 단어 카운팅
int check_word() {
	int cnt = 0;

	for (string& s : words) {
		bool flag = true;
		for (int i = 4; i < s.size() - 4; i++) {	// 앞뒤로 4개는 건너뜀
			if (!selected[s[i] - 'a'])
				flag = false;
		}
		if (flag) cnt++;
	}

	return cnt;
}