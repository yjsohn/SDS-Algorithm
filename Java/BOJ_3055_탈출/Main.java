import java.io.*;
import java.util.*;

public class Main {
    static class Coord {
        int x, y;

        public Coord(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static int N, M, move;
    static int[][] map;
    static boolean[][] visit;
    static Deque<Coord> waterDequeue, goDequeue;
    static boolean root;
    static int[] dx = new int[] { 0, 0, -1, 1 };
    static int[] dy = new int[] { -1, 1, 0, 0 };

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st = new StringTokenizer(br.readLine());
        StringBuilder sb = new StringBuilder();

        // 1. 입력 받기
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        map = new int[N][M];
        visit = new boolean[N][M];
        goDequeue = new ArrayDeque<>();
        waterDequeue = new ArrayDeque<>();

        for (int i = 0; i < N; i++) {
            String str = br.readLine();
            for (int j = 0; j < M; j++) {
                map[i][j] = str.charAt(j);
                // 물인 부분은 위치를 stack에 넣어준다.
                if (map[i][j] == '*')
                    waterDequeue.addLast(new Coord(i, j));
                else if (map[i][j] == 'S')
                    goDequeue.addLast(new Coord(i, j));
            }
        }

        // 2. dfs를 사용해 루트 확인
        root = false;
        move = 0;
        dfs();
        sb.append(root ? move : "KAKTUS");

        // 3. 결과 출력
        bw.write(sb.toString());
        bw.flush();
        bw.close();
        br.close();
    }

    static void dfs() {
        // 이동
        while (!goDequeue.isEmpty()) {

            int size = goDequeue.size();
            for (int j = 0; j < size; j++) {
                Coord cur = goDequeue.pollFirst();

                // 이미 방문했다면 패스
                if (visit[cur.x][cur.y])
                    continue;

                // 다음 방문루트 저장
                visit[cur.x][cur.y] = true;
                for (int i = 0; i < 4; i++) {
                    int mx = dx[i] + cur.x;
                    int my = dy[i] + cur.y;
                    if (mx >= 0 && my >= 0 && mx < N && my < M) {
                        if (map[mx][my] == '.' && !visit[mx][my]) {
                            goDequeue.addLast(new Coord(mx, my));
                        } else if (map[mx][my] == 'D') {
                            root = true;
                            move++;
                            return;
                        }
                    }
                }
            }

            // 물 업데이트
            updateWater();
            move++;
        }
    }

    static void updateWater() {
        int size = waterDequeue.size();
        for (int i = 0; i < size; i++) {
            Coord cur = waterDequeue.pollFirst();
            for (int j = 0; j < 4; j++) {
                int mx = dx[j] + cur.x;
                int my = dy[j] + cur.y;
                if (mx >= 0 && my >= 0 && mx < N && my < M) {
                    if (map[mx][my] == '.') {
                        map[mx][my] = '*';
                        waterDequeue.addLast(new Coord(mx, my));
                        visit[mx][my] = true;
                    }
                }
            }
        }
    }
}