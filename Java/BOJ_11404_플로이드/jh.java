import java.io.*;
import java.util.*;

public class Main {

    static int N, M;
    static int[][] dist;
    static final int MAX = 10000000;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;

        N = Integer.parseInt(br.readLine());
        dist = new int[N+1][N+1];
        for (int i = 1; i <= N; i++)
            Arrays.fill(dist[i], MAX);

        M = Integer.parseInt(br.readLine());
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());
            int w = Integer.parseInt(st.nextToken());
            dist[u][v] = Math.min(dist[u][v], w);
        }

        for (int k = 1; k <= N; k++)
            for (int u = 1; u <= N; u++)
                for (int v = 1; v <= N; v++)
                    dist[u][v] = Math.min(dist[u][v], dist[u][k] + dist[k][v]);

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i==j || dist[i][j]==MAX) bw.write(0+" ");
                else bw.write(dist[i][j] + " ");
            }
            bw.write("\n");
        }

        bw.flush();
        bw.close();
        br.close();
    }

}
