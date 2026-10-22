// Q8. LFU Cache — LeetCode 460
import java.util.*;

class LFUCache {
    private final int capacity;
    private int minFreq = 0;
    private final Map<Integer, Node> keyNode = new HashMap<>();
    private final Map<Integer, LinkedHashSet<Node>> freqMap = new HashMap<>();

    private static class Node {
        int key, val, freq;
        Node(int k, int v) { key = k; val = v; freq = 1; }
    }

    public LFUCache(int capacity) {
        this.capacity = capacity;
    }

    public int get(int key) {
        Node node = keyNode.get(key);
        if (node == null) return -1;
        update(node);
        return node.val;
    }

    public void put(int key, int value) {
        if (capacity == 0) return;
        Node node = keyNode.get(key);
        if (node != null) {
            node.val = value;
            update(node);
            return;
        }
        if (keyNode.size() == capacity) {
            // evict LRU from minFreq list
            LinkedHashSet<Node> set = freqMap.get(minFreq);
            Node evict = set.iterator().next();
            set.remove(evict);
            keyNode.remove(evict.key);
        }
        Node newNode = new Node(key, value);
        keyNode.put(key, newNode);
        freqMap.computeIfAbsent(1, k -> new LinkedHashSet<>()).add(newNode);
        minFreq = 1;
    }

    private void update(Node node) {
        int freq = node.freq;
        LinkedHashSet<Node> set = freqMap.get(freq);
        set.remove(node);
        if (freq == minFreq && set.isEmpty()) {
            minFreq++;
        }
        node.freq++;
        freqMap.computeIfAbsent(node.freq, k -> new LinkedHashSet<>()).add(node);
    }
}
