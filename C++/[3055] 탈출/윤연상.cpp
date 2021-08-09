#include <bits/stdc++.h>

using namespace std;

int r, c;						// 행, 열 크기
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
int dist[51][51];				// 거리 저장 배열
char forest[51][51];			// 숲 정보

// 좌표 구죠체
struct pos {
	int y, x;
	pos(int _y, int _x) : y(_y), x(_x) {};
};
deque<pos> q;					// bfs queue
deque<pos> water;				// 새로 추가된 물 queue

void extend_water();

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int tx, ty;
	int time = -1;

	// 입력 
	cin >> r >> c;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			char a; cin >> a;

			forest[i][j] = a;
			dist[i][j] = -1;	

			if (a == 'S') {
				dist[i][j] = 0;
				forest[i][j] = '.';
				q.push_back(pos(i, j));
			}
			else if (a == '*') {
				water.push_back(pos(i, j));
			}
			else if (a == 'D') {
				ty = i; tx = j;
			}
		}
	}

	// bfs 시작
	while (!q.empty()) {
		pos now = q.front(); q.pop_front();
		
		// 1분 뒤에 물 한칸 범람
		if (dist[now.y][now.x] > time) {
			extend_water();
			time = dist[now.y][now.x];
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny >= r || ny < 0 || nx >= c || nx < 0)
				continue;
			if (forest[ny][nx] == '*' || 
				forest[ny][nx] == 'X' || 
				dist[ny][nx] != -1)
				continue;

			dist[ny][nx] = dist[now.y][now.x] + 1;
			q.push_back(pos(ny, nx));
		}
		continue;
	}

	if (dist[ty][tx] == -1) {
		cout << "KAKTUS\n";
	}
	else {
		cout << dist[ty][tx] << '\n';
	}
}

// 1분 뒤 물이 범람해 forest를 갱신시키는 함수
void extend_water() {
	int len = water.size();

	for (int i = 0; i < len; i++) {
		pos now = water.front(); water.pop_front();

		for (int j = 0; j < 4; j++) {
			int ny = now.y + dy[j];
			int nx = now.x + dx[j];

			if (ny >= r || ny < 0 || nx >= c || nx < 0)
				continue;

			if (forest[ny][nx] == '.') {
				forest[ny][nx] = '*';
				water.push_back(pos(ny, nx));
			}
		}
	}
}