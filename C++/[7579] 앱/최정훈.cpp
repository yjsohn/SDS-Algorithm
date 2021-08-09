#include <iostream>
#include <memory.h>

using namespace std;

struct APP {
    int mem, cost;
    APP() { }
};

int N, M;
int costSum, minCost;

APP* appList;
int** memDP;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> N >> M;

// 1. Get Input
    appList = new APP [N + 1];
    for (int i = 1; i <= N; i++) {
        cin >> appList[i].mem;
    }

    costSum = 0;
    for (int i = 1; i <= N; i++) {
        cin >> appList[i].cost;
        costSum += appList[i].cost;  // calculate cost sum
    }

// 2. Initialize DP Table
    memDP = new int* [N + 1];
    for (int appCount = 0; appCount <= N; appCount++) {
        memDP[appCount] = new int [costSum + 1];
        memset(memDP[appCount], 0, (costSum + 1) * sizeof(int));
    } 

// 3. Fill DP Table
    for (int appCount = 1; appCount <= N; appCount++) {
        for (int cost = 0; cost <= costSum; cost++) {
            APP App = appList[appCount];

            // 앱이 n-1개에서 n번째 앱을 추가할 때
            // n번째 앱을 끄지 않고, 그대로 진행한 것과
            // n번째 앱을 꺼서, cost[n]의 비용이 발생하고 memory[n]의 메모리를 추가로 확보한 것 중, 최댓값을 DP[n][cost]에 저장.
            if (cost - App.cost >= 0) {
                memDP[appCount][cost] = max(memDP[appCount - 1][cost], memDP[appCount - 1][cost - App.cost] + App.mem);
            }
            else {
                memDP[appCount][cost] = max(memDP[appCount - 1][cost], memDP[appCount][cost]);
            }
        }
    }

// 4. Find Minimum Cost
    minCost = 0;
    for (int cost = 0; cost <= costSum; cost++) {
        // 메모리 M 이상 확보한 최소 비용
        if (memDP[N][cost] >= M) {
            minCost = cost;
            break;
        }
    }

// 5. Print Result
    cout << minCost << endl;

    return 0;
}