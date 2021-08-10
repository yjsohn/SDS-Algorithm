#include <bits/stdc++.h>

using namespace std;

static int n, m;	// n : 사진틀 크기, m : 추천 횟수

struct student {
	int id, upCount, time;	// id : 학생 번호, upCount : 추천 횟수, time : 등록 시간
	bool isIn;				// 사진틀 등록 여부
	student() { id = 0; upCount = 0; time = 0; isIn = false; }
};
struct compare {
	bool operator()(student* a, student* b) {
		if (a->upCount == b->upCount) {
			return a->time < b->time;
		}
		return a->upCount > b->upCount;
	}
};
priority_queue<student*, vector<student*>, compare> pq;	// 사진틀
student* students[101];									// 학생 배열


// funtions
void init();
void updateTime();
void push_student(int id);
void remove_student();

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	init();		// 학생 배열 초기화(1~100번)
	
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		updateTime();		// 등록 후보 시간 갱신

		int id; cin >> id;
		push_student(id);	// 후보 추천
		continue;

	}

	priority_queue<int, vector<int>, greater<int>> ans;
	while (!pq.empty()) {
		ans.push(pq.top()->id);
		pq.pop();
	}
	while (!ans.empty()) {
		cout << ans.top() << ' ';
		ans.pop();
	}
}

// 학생 배열 초기화(1 ~ 100번)
void init() {
	for (int i = 0; i <= 100; i++) {
		student* s = new student;
		s->id = i;
		students[i] = s;
	}
}

// 사진틀에 게시된 시간 갱신
void updateTime() {
	while (!pq.empty()) {
		student* now = pq.top(); pq.pop();
		now->time++;
	}
	for (int i = 1; i <= 100; i++) {
		if (students[i]->isIn) {
			pq.push(students[i]);
		}
	}
}

// 사진틀에 학생 추가
void push_student(int id) {
	student* now = students[id];

	if (now->isIn) {		// 이미 등록된 후보는 추천 횟수만 증가
		now->upCount++;
	}
	else {
		if (pq.size() >= n)	// 사진틀이 꽉차면 한명 제거
			remove_student();
		now->isIn = true;
		now->upCount = 1;
		now->time = 0;
		pq.push(now);
	}
}

// 가장 추천횟수가 적고 오래된 후보 제거
void remove_student() {
	student* now = pq.top(); pq.pop();

	now->isIn = false;
	now->time = 0;
	now->upCount = 0;
}