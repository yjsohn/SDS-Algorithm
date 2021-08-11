package P1922;
import java.io.*;
import java.util.*;

public class Main {
	static int N; // 컴퓨터수 1000
	static int M; // 연결선의 수 100,000
	static PriorityQueue<Edge> pq = new PriorityQueue<>();

	static int ans;
	static int count = 0; // 사용한 edge수 기록
	static int[] connect; // 연결 여부 기록
	public static void main(String[] args) throws IOException{
		System.setIn(new FileInputStream("P1922/input.txt"));
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		N = Integer.parseInt(br.readLine());
		M = Integer.parseInt(br.readLine());
		

		// 연결선 저장 - from 과 to 가 같을수도, cost는 10,000이하 자연수 
		for(int i = 0 ; i<M ; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int from = Integer.parseInt(st.nextToken());
			int to = Integer.parseInt(st.nextToken());
			int cost = Integer.parseInt(st.nextToken());
			// 가지 치기를 위해 from과 to 가 같으면 저장하지 말자
			if(from==to) continue;
			pq.add(new Edge(from,to,cost));
		}
		
		// MST kruskal
		connect = new int[N+1];
		for(int i = 1 ; i<=N ; i++) {
			connect[i] = i;
		}
		while(!pq.isEmpty()) {
			Edge current = pq.poll();
			
			int from = current.from;
			int to = current.to;
			int cost = current.cost;
			
			if(find(from)==find(to)) continue;
			// to가 from보다 크다고 가정하고
			// 항상 큰쪽으로 union
			union(from, to);
			ans += cost;
			count ++;
			
			// 사용할 간선수는 최대 N-1개
			if(count == N-1) break;
		}
		System.out.println(ans);
		
	}
	
	public static class Edge implements Comparable<Edge>{
		int from;
		int to;
		int cost;
		
		@Override
		public String toString() {
			return "Edge [from=" + from + ", to=" + to + ", cost=" + cost + "]";
		}

		public Edge(int from, int to, int cost) {
			super();
			this.from = from;
			this.to = to;
			this.cost = cost;
		}

		@Override
		public int compareTo(Edge o) {
				return this.cost - o.cost;
		}
	}
	
	public static void union(int a , int b) {
		int pa = find(a);
		int pb = find(b);
		
		connect[pa] = pb;
	}
	
	public static int find(int a) {
		int pa = connect[a];
		
		if(pa== a) return pa;
		else return connect[a] = find(pa);
	}
}
