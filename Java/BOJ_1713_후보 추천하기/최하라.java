import java.io.*;
import java.util.*;

public class Main {
    static int N, stuNum;
    static ArrayList<Integer> candidates;
    static HashMap<Integer, Integer> countMap;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        // 1. 입력받기
        countMap = new HashMap<>();
        N = Integer.parseInt(br.readLine());
        stuNum = Integer.parseInt(br.readLine());

        // 2. 후보 찾기
        StringTokenizer st = new StringTokenizer(br.readLine());
        candidates = new ArrayList<>();
        for (int i = 0; i < stuNum; i++) {
            int student = Integer.parseInt(st.nextToken());

            if (countMap.containsKey(student)) { // 후보 리스트에 존재
                countMap.put(student, countMap.get(student) + 1);

            } else { // 후보 리스트에 존재하지 않음
                // 후보 리스트가 꽉 찼다면 후보 한명 제외 시키기
                if (candidates.size() == N) {
                    deleteCan();
                }

                // countMap에 넣기
                candidates.add(student);
                countMap.put(student, 1);
            }
        }

        // 3. 후보 정렬 & 출력
        Collections.sort(candidates);
        StringBuilder sb = new StringBuilder();
        for (Integer candidate : candidates) {
            sb.append(candidate + " ");
        }

        bw.write(sb.toString());
        bw.flush();
        bw.close();
        br.close();
    }

    static void deleteCan() {
        int min = Integer.MAX_VALUE;
        int stuPos = 0;

        // 최소 추천 받은 학생이며 게시된지 오래된 사진 찾기
        for (int i = 0; i < N; i++) {
            if (countMap.get(candidates.get(i)) < min) {
                min = countMap.get(candidates.get(i));
                stuPos = i;
            }
        }

        // 후보 리스트에서 삭제
        countMap.remove(candidates.get(stuPos));
        candidates.remove(stuPos);
    }
}