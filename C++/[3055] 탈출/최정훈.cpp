#include <iostream>
#include <queue>

using namespace std;

struct Point {
    int x, y, type;

    Point() { }

    Point(int x, int y, char type) {
        this->x = x;
        this->y = y;
        this->type = type;
    }
};

const int dirX[] = { 0, 1, 0, -1 };
const int dirY[] = { 1, 0, -1, 0 };
const int WATER = -1;
const int SOURCE = 0;

char graph[52][52] = { 0, }; // array padded with zeros
queue<Point> q;              // queue for BFS

void BFS();

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    freopen("../input.txt", "r", stdin);

    int R, C;
    cin >> R >> C;

// 1. get input & push water point
    Point src; // strating point

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> graph[i][j];

            // water push first
            if (graph[i][j] == '*') {
                q.push(Point(i, j, WATER));
            }
            // starting point push later
            else if (graph[i][j] == 'S') {
                src = Point(i, j, SOURCE);
            }
        }
    }

// 2. push starting point
    q.push(src);
    
// 3. BFS until destination
    BFS();

    return 0;
}

void BFS() {
    while (!q.empty()) {
        // get current point
        Point now = q.front(); q.pop();

        // for all direction
        for (int i = 0; i < 4; i++) {
            // get next point
            Point next = Point(now.x + dirX[i], now.y + dirY[i], now.type);
            
            // if current is water, update to water
            if (now.type == WATER) {
                if (graph[next.x][next.y] == '.' || graph[next.x][next.y] == 'S') {
                    graph[next.x][next.y] = '*';
                    q.push(next);
                }
            }
            // if current is source, count up & update to source
            else if (now.type >= 0) {
                // count up
                next.type = now.type + 1;
                if (graph[next.x][next.y] == '.') {
                    graph[next.x][next.y] = 'S';
                    q.push(next);
                }
                // if next is destination, print & exit
                else if (graph[next.x][next.y] == 'D') {
                    cout << next.type << '\n';
                    return;
                }
            }
        }
    }
    // if destination not visited,
    cout << "KAKTUS" << '\n';
}