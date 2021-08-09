#include <iostream>
#include <queue>
using namespace std;

struct CHECK {
	int x, y;
	int likeCnt, spaceCnt;

	// ���� �����ϴ� ��� �ɱ� ���� �����ϱ�
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
int satisfaction[] = { 0, 1, 10, 100, 1000 }; // ������

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

		// �Էµ� ������ �ڸ� üũ�ؾ� �ϹǷ� �Ʒ�ó�� �Է� ����
		student[i] = { 0,0,a,{b,c,d,e} };
	}
}

void student_check() {
	// �л����� �ڸ� üũ�ϱ�
	for (int i = 0; i < N*N; ++i) {
		priority_queue<CHECK> check; //-> ��� �������ֱ� ���� ���⿡ ����

		int spaceCnt, likeCnt = 0;
		for (int x = 0; x < N; ++x) {
			for (int y = 0; y < N; ++y) {
				//�ƹ��� ���� ���� �ڸ��� üũ����.
				if (map[x][y] == 0) {

					// �����¿� Ȯ��
					int nx, ny = 0;
					for (int k = 0; k < 4; ++k) {
						nx = x + dx[k], ny = y + dy[k];

						if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;

						// ��ĭ Ȯ��
						if (map[nx][ny] == 0) spaceCnt++;

						// �����ϴ� �л� Ȯ��
						for (int j = 0; j < 4; ++j) {
							if (student[i].like[j] == map[nx][ny]) { likeCnt++; break; }
						}
					}
					check.push({ x,y,likeCnt,spaceCnt });
					likeCnt = 0, spaceCnt = 0;
				}
			}
		}

		// ���� ������ �ڸ� ã��
		int cx = check.top().x, cy = check.top().y;
		map[cx][cy] = student[i].number;
		student[i].x = cx, student[i].y = cy; // ������ ���� ����ϱ� ���� ���� ����.
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

			// ������
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

	// �л� �ڸ� üũ
	student_check();

	// ������ ���ϱ�
	answer = like_check();

	//print();
}

int main() {

	solution();

	cout << answer;

	return 0;
}