// Q3. Task Scheduler — LeetCode 621
public class Q3_TaskScheduler {
    public int leastInterval(char[] tasks, int n) {
        int[] c = new int[26];
        int max = 0, count = 0;
        for (char t : tasks) c[t - 'A']++;
        for (int v : c) if (v > max) max = v;
        for (int v : c) if (v == max) count++;
        int ans = (max - 1) * (n + 1) + count;
        return Math.max(tasks.length, ans);
    }
}
