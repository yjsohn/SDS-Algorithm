import java.io.*;
import java.util.*;

public class Main {

    static int N, M;
    static int[] parent, weight;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;

        do{
            st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());

            parent = new int[N+1];
            weight = new int[N+1];
            for (int i = 1; i <= N; i++)
                parent[i] = i;

            int a, b, w;
            for (int i = 0; i < M; i++) {
                st = new StringTokenizer(br.readLine());
                String t = st.nextToken();
                a = Integer.parseInt(st.nextToken());
                b = Integer.parseInt(st.nextToken());
                if (t.equals("!")){
                    w = Integer.parseInt(st.nextToken());
                    union(a, b, w);
                } else{
                    if(find(a)==find(b))
                        bw.write(weight[b]-weight[a]+"\n");
                    else
                        bw.write("UNKNOWN\n");
                }
            }
        } while(N!=0 && M!=0);

        bw.flush();
        bw.close();
        br.close();
    }
    public static void union(int a, int b, int w){
        int pa = find(a);
        int pb = find(b);
        if (pa!=pb){
            weight[pb] = weight[a] - weight[b] + w;
            parent[pb] = pa;
        }
    }
    public static int find(int id){
        if (parent[id]==id)
            return id;
        int pid = find(parent[id]);
        weight[id] += weight[parent[id]];
        return parent[id] = pid;
    }
}
