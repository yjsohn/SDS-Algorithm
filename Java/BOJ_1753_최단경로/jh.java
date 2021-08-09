import java.io.*;
import java.util.*;

public class Main {

    static int V, E, K;
    static class edge{
        int to, weight;
        public edge(int to, int weight){
            this.to = to;
            this.weight = weight;
        }
    } static ArrayList<edge>[] nodes;
    static final int MAX = 200000;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;

        st = new StringTokenizer(br.readLine());
        V = Integer.parseInt(st.nextToken());
        nodes = new ArrayList[V+1];
        for (int i = 1; i <= V; i++)
            nodes[i] = new ArrayList<edge>();

        E = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(br.readLine());
        for (int i = 0; i < E; i++) {
            st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());
            int w = Integer.parseInt(st.nextToken());
            nodes[u].add(new edge(v, w));
        }

        int[] dist = new int[V+1];
        for (int i = 1; i <= V; i++)
            if(i!=K) dist[i] = MAX;

        PriorityQueue<edge> pq = new PriorityQueue<>((a, b)->a.weight-b.weight);
        pq.add(new edge(K, 0));
        
        while (!pq.isEmpty()){
            edge now = pq.poll();
            if(now.weight > dist[now.to])
                continue;

            for (edge next : nodes[now.to])
                if (dist[next.to] > now.weight + next.weight){
                    dist[next.to] = now.weight + next.weight;
                    pq.add(new edge(next.to, dist[next.to]));
                }
        }

        for (int i = 1; i <= V; i++)
            if (dist[i]<MAX)
                bw.write(dist[i]+"\n");
            else
                bw.write("INF\n");

        bw.flush();
        bw.close();
        br.close();
    }
}
