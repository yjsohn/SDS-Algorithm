import java.io.*;
import java.util.*;

public class Main {

    static int V, E;
    static ArrayList<Integer>[] tree;
    static Set<Integer> answer;
    static int[] order;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;

        st = new StringTokenizer(br.readLine());
        V = Integer.parseInt(st.nextToken());
        tree = new ArrayList[V+1];
        for (int i = 1; i <= V; i++)
            tree[i] = new ArrayList<>();

        E = Integer.parseInt(st.nextToken());
        for (int i = 0; i < E; i++) {
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            tree[a].add(b);
            tree[b].add(a);
        }

        order = new int[V+1];
        answer = new HashSet();
        for (int i = 1; i <= V; i++)
            if (order[i]==0)
                dfs(i, true, 0);

        ArrayList<Integer> tmp = new ArrayList<>(answer);
        Collections.sort(tmp);
        bw.write(tmp.size()+"\n");
        for (int item : tmp)
            bw.write(item+" ");

        bw.flush();
        bw.close();
        br.close();
    }
    static int cnt=1;
    static int dfs(int id, boolean isRoot, int parent){
        order[id] = cnt++;
        int ret = order[id];
        int child = 0;
        for (int now : tree[id]) {
            if (now == parent) continue;
            
            if (order[now]==0){
                child++;
                int low = dfs(now, false, id);
                if (!isRoot && low >= order[id])
                    answer.add(id);
                ret = Math.min(ret, low);
            } else
                ret = Math.min(ret, order[now]);
        }
        if (isRoot && child>=2)
            answer.add(id);
        return ret;
    }
}
