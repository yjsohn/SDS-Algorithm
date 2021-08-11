package P11266; // 단절점 
import java.io.*;
import java.util.*;

public class Main{
    static int V; // 최대 만
    static int E; // 최대 십만
    static ArrayList<Integer>[] Edge; // 인접리스트

    static int o = 1; // 방문순서 세는용
    static int root;
    static int rootChild;
    static int[] visit; // 방문순서 저장
    static Boolean[] ans; // 단절점 여부 저장
    public static void main(String[]args) throws IOException{
        System.setIn(new FileInputStream("P11266/input.txt"));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st = new StringTokenizer(br.readLine());

        V = Integer.parseInt(st.nextToken());
        E = Integer.parseInt(st.nextToken());
        Edge = new ArrayList[V+1];
        visit = new int[V+1];
        ans = new Boolean[V+1];

        for(int i = 1 ; i <=V ; i++){
            Edge[i] = new ArrayList<Integer>();
            ans[i] = false;
        }
        for(int i = 0 ; i<E ; i++){
            // 간선 입력받기
            st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());

            if(a==b) continue;
            Edge[a].add(b);
            Edge[b].add(a);
        }

        // 모든 노드가 연결되어 있지 않을수도 있음.
        for(int i = 1 ; i<=V ; i++){
            if(visit[i]==0){
                root = i;
                dfs(root,0);
                if(rootChild >= 2) ans[root] = true;
            }
        }

        int count = 0;
        for(int i =1 ; i<=V ; i++){
            if(ans[i]){
                 bw.write(i+" ");
                 count++;
            }
        }
        System.out.println(count);
        bw.flush();
        bw.close();
        br.close();
    }

    public static int dfs(int current, int parent){
        int order = o;
        int low = o;
        
        // 시작노드 라면 자신과 연결된 자식 트리의 개수를 세어봐야 함.
        if(current == root) rootChild = Edge[current].size();

        // 1. 체크인
        visit[current] = o;
        o++;
        // 2. 목적지 확인 - 할일 없음.
        // 3. 연결된 노드
        for(int i = 0 ; i<Edge[current].size(); i++){
            int next = Edge[current].get(i);
            // 4. 방문가능하면
            if(next != parent){
                if(next == root) rootChild--;
                // 5. 방문
                if(visit[next]==0){ // 안 가본 노드
                    int ret = dfs(next,current);
                    low = Math.min(ret, low);
                    if(ret>=order && current!=root)  ans[current]=true;
                }else{ // 가본 노드
                    low = Math.min(visit[next], low);
                }
            }
        }
        return low;        
    }
}
