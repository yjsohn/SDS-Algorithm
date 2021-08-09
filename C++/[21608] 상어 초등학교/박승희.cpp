#include <iostream>
#include <queue>
using namespace std;

struct CHECK {
	int x, y;
	int likeCnt, spaceCnt;

	// 조건 만족하는 대로 앉기 위해 정렬하기
	bool operator<(const CHECK &i) const {
		if (likeCnt == i.likeCnt) {
			if (spaceCnt == i.spaceCnt) {
				if (x == i.x) return y > i.y;
				else return x > i.x;
			}
			else return spaceCnt < i.spaceCnt;
		}
		else return likeCnt < i.likeCnt;
	}
};

int map[21][21];

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

struct STUDENT {
	int x, y;
	int number;
	int like[4] = { 0, };
};
STUDENT student[401];

int N;
int satisfaction[] = { 0, 1, 10, 100, 1000 }; // 만족도

int answer;

void print() {
	for (int x = 0; x < N; ++x) {
		for (int y = 0; y < N; ++y) {
			cout << map[x][y] << ' ';
		}cout << endl;
	}
}

void input_data() {
	cin >> N;
	for (int i = 0; i < N*N; ++i) {
		int a, b, c, d, e; cin >> a >> b >> c >> d >> e;

		// 입력된 순으로 자리 체크해야 하므로 아래처럼 입력 받음
		student[i] = { 0,0,a,{b,c,d,e} };
	}
}

void student_check() {
	// 학생마다 자리 체크하기
	for (int i = 0; i < N*N; ++i) {
		priority_queue<CHECK> check; //-> 계속 갱신해주기 위해 여기에 선언

		int spaceCnt, likeCnt = 0;
		for (int x = 0; x < N; ++x) {
			for (int y = 0; y < N; ++y) {
				//아무도 앉지 않은 자리만 체크하자.
				if (map[x][y] == 0) {

					// 상하좌우 확인
					int nx, ny = 0;
					for (int k = 0; k < 4; ++k) {
						nx = x + dx[k], ny = y + dy[k];

						if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;

						// 빈칸 확인
						if (map[nx][ny] == 0) spaceCnt++;

						// 좋아하는 학생 확인
						for (int j = 0; j < 4; ++j) {
							if (student[i].like[j] == map[nx][ny]) { likeCnt++; break; }
						}
					}
					check.push({ x,y,likeCnt,spaceCnt });
					likeCnt = 0, spaceCnt = 0;
				}
			}
		}

		// 가장 적절한 자리 찾기
		int cx = check.top().x, cy = check.top().y;
		map[cx][cy] = student[i].number;
		student[i].x = cx, student[i].y = cy; // 만족도 쉽게 계산하기 위해 따로 저장.
	}
}

int like_check() {
	int ret = 0;

	for (int i = 0; i < N*N; ++i) {
		int x = student[i].x, y = student[i].y;

		int likeCnt = 0;
		for (int k = 0; k < 4; ++k) {
			int nx = x + dx[k], ny = y + dy[k];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;

			// 만족도
			for (int j = 0; j < 4; ++j) {
				if (student[i].like[j] == map[nx][ny]) { likeCnt++; break; }
			}
		}
		ret += satisfaction[likeCnt];
	}

	return ret;
}

void solution() {
	input_data();

	// 학생 자리 체크
	student_check();

	// 만족도 구하기
	answer = like_check();

	//print();
}

int main() {

	solution();

	cout << answer;

	return 0;
}