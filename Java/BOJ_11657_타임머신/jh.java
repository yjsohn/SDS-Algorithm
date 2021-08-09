import java.io.*;
import java.util.*;

public class Main {

    static int N, M;
    static long[] dist;
    static final int MAX = Integer.MAX_VALUE;
    static class Edge{
        int from, to, cost;
        public Edge(int from, int to, int cost){
            this.from = from;
            this.to = to;
            this.cost = cost;
        }
    }static Edge[] edges;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;

        st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        dist = new long[N+1];
        edges = new Edge[M];
        for (int i = 2; i <= N; i++)
            dist[i] = MAX;

        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());
            edges[i] = new Edge(a, b, c);
        }

        for (int i = 0; i < N-1; i++)
            for (Edge E : edges)
                if(dist[E.from]<MAX)
                    dist[E.to] = Math.min(dist[E.to], dist[E.from]+E.cost);

        if (!isCycle())
            for (int i = 2; i <= N; i++)
                if (dist[i]<MAX)
                    bw.write(dist[i]+"\n");
                else
                    bw.write("-1\n");
        else
            bw.write("-1\n");

        bw.flush();
        bw.close();
        br.close();
    }
    static boolean isCycle(){
        for (Edge E : edges)
            if(dist[E.from]!=MAX && dist[E.from]+E.cost < dist[E.to])
                return true;
        return false;
    }
}
