import java.io.*;
import java.util.*;

public class Main {
    static int N, M, K;
    static int[][] parent;
    static int[] depth;
    static ArrayList<Integer> edgeList[];

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;

        //1. 입력 받기
        N = Integer.parseInt(br.readLine());

        //2. 2^K 트리 최대 높이 구하기
        K = 0;
        for (int i = 1; i <= N; i *= 2) K++;

        //build graph
        edgeList = new ArrayList[N + 1];
        depth = new int[N + 1];
        parent = new int[K][N + 1];
        for (int i = 1; i <= N; i++) edgeList[i] = new ArrayList<>();

        for (int i = 0; i < N - 1; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());

            edgeList[a].add(b);
            edgeList[b].add(a);
        }

        //find depth using dfs
        dfs(1, 1);

        //fill parent
        fillParent();

        //print result
        M = Integer.parseInt(br.readLine());
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            sb.append(LCA(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()))).append("\n");
        }

        bw.write(sb.toString());
        bw.flush();
        bw.close();
        br.close();
    }

    static void dfs(int id, int cnt) {
        //부모 depth set
        depth[id] = cnt;

        //자식 depth set
        int size = edgeList[id].size();
        for (int i = 0; i < size; i++) {
            int next = edgeList[id].get(i);
            if (depth[next] == 0) {
                dfs(next, cnt + 1);
                parent[0][next] = id;
            }
        }
    }

    static void fillParent() {
        for (int i = 1; i < K; i++) {
            for (int j = 1; j <= N; j++) {
                parent[i][j] = parent[i - 1][parent[i - 1][j]];
            }
        }
    }

    static int LCA(int a, int b) {
        //1. let depth[a] >= depth[b]
        if (depth[a] < depth[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }

        //2. set to same depth
        for (int i = K - 1; i >= 0; i--) {
            if (Math.pow(2, i) <= depth[a] - depth[b]) {
                a = parent[i][a];
            }
        }

        //3. check if a == b
        if (a == b) return a;

        //4. same depth but different parent
        for (int i = K - 1; i >= 0; i--) {
            if (parent[i][a] != parent[i][b]) {
                a = parent[i][a];
                b = parent[i][b];
            }
        }
        return parent[0][a];
    }
}