// Q1. Single-Threaded CPU — LeetCode 1834
import java.util.*;

public class Q1_SingleThreadedCPU {
    public int[] getOrder(int[][] tasks) {
        int n = tasks.length, i = 0, k = 0;
        int[][] a = new int[n][3];
        for (int j = 0; j < n; j++)
            a[j] = new int[]{tasks[j][0], tasks[j][1], j};
        Arrays.sort(a, (x, y) -> Integer.compare(x[0], y[0]));
        PriorityQueue<int[]> q = new PriorityQueue<>((x, y) ->
            x[1] != y[1] ? Integer.compare(x[1], y[1])
                         : Integer.compare(x[2], y[2]));
        int[] ans = new int[n];
        long time = 0;
        while (k < n) {
            if (q.isEmpty() && i < n && time < a[i][0])
                time = a[i][0];
            while (i < n && a[i][0] <= time) q.offer(a[i++]);
            int[] t = q.poll();
            ans[k++] = t[2];
            time += t[1];
        }
        return ans;
    }
}
