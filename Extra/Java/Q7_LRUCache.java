// Q7. LRU Cache — LeetCode 146
import java.util.*;

class LRUCache {
    private final int capacity;
    private final Map<Integer, Node> map = new HashMap<>();
    private final Deque<Node> deque = new ArrayDeque<>();

    private static class Node {
        int key, val;
        Node(int k, int v) { key = k; val = v; }
    }

    public LRUCache(int capacity) {
        this.capacity = capacity;
    }

    public int get(int key) {
        Node node = map.get(key);
        if (node == null) return -1;
        // move to front
        deque.remove(node);
        deque.addFirst(node);
        return node.val;
    }

    public void put(int key, int value) {
        Node node = map.get(key);
        if (node != null) {
            node.val = value;
            deque.remove(node);
            deque.addFirst(node);
            return;
        }
        if (map.size() == capacity) {
            Node lru = deque.removeLast();
            map.remove(lru.key);
        }
        Node newNode = new Node(key, value);
        deque.addFirst(newNode);
        map.put(key, newNode);
    }
}
