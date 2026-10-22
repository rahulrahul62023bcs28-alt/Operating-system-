// Q2. Process Tasks Using Servers — LeetCode 1882
import java.util.*;

public class Q2_ProcessTasksUsingServers {
    public int[] assignTasks(int[] servers, int[] tasks) {
        PriorityQueue<int[]> free = new PriorityQueue<>((a, b) ->
            a[0] != b[0] ? Integer.compare(a[0], b[0])
                         : Integer.compare(a[1], b[1]));
        PriorityQueue<long[]> busy = new PriorityQueue<>((a, b) ->
            a[0] != b[0] ? Long.compare(a[0], b[0])
                         : Long.compare(a[1], b[1]));
        for (int i = 0; i < servers.length; i++)
            free.offer(new int[]{servers[i], i});
        int[] ans = new int[tasks.length];
        long time = 0;
        for (int i = 0; i < tasks.length; i++) {
            time = Math.max(time, i);
            if (free.isEmpty()) time = Math.max(time, busy.peek()[0]);
            while (!busy.isEmpty() && busy.peek()[0] <= time) {
                long[] b = busy.poll();
                free.offer(new int[]{servers[(int)b[1]], (int)b[1]});
            }
            int[] s = free.poll();
            ans[i] = s[1];
            busy.offer(new long[]{time + tasks[i], s[1]});
        }
        return ans;
    }
}
