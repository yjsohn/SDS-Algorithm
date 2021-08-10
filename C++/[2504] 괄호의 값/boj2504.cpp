#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isAnswer = true;

int parenthesis(int start, int end, string str) {
	stack<char> st;

	int index = start;
	char c = str[index];
	//cout << c;
	st.push(c);

	while (!st.empty() && index + 1 <= end) {
		index++;
		if (str[index] == '(' || str[index] == '[') {
			st.push(str[index]);
		}
		else if (st.top() == '(' && str[index] == ')') {
			st.pop();
		}
		else if (st.top() == '[' && str[index] == ']') {
			st.pop();
		}
		else {
			isAnswer = false;
			return -1;
		}
	}

	return index;
}

long long DFS(int start, int end, string str) {
	// 체크인
	// 정답이 없는가?
	if (!isAnswer) {
		return -1;
	}


	int index = parenthesis(start, end, str);
	
	if (index == end) {
		if (str[start] == '(' && str[end] == ')') {
			return 2 * DFS(start + 1, end -1 , str);
		}
		else if (str[start] == '[' && str[end] == ']') {
			return 3 * DFS(start + 1, end - 1, str);
		}
		else {
			isAnswer = false;
			return -1;
		}
	}


	if (start >= end) {
		return 1;
	}

	

	if (str[start] == '(' && str[index] == ')') {
		return DFS(start, index , str) + DFS(index + 1, end, str);
	}
	else if (str[start] == '[' && str[index] == ']') {
		return DFS(start, index, str) + DFS(index + 1, end, str);
	}

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string str;
	cin >> str;


	//cout << parenthesis(0, str.length() - 1, str);
	long long answer = DFS(0, str.length() - 1, str);

	
	if (isAnswer) {
		cout << answer << "\n";
	}
	else {
		cout << 0;
	}
	
	return 0;
}