// Q4. The Dining Philosophers — LeetCode 1226
import java.util.concurrent.*;

class DiningPhilosophers {
    private final Semaphore room = new Semaphore(4, true);
    private final Semaphore[] fork = new Semaphore[5];

    public DiningPhilosophers() {
        for (int i = 0; i < 5; i++) {
            fork[i] = new Semaphore(1, true);
        }
    }

    public void wantsToEat(int philosopher,
                           Runnable pickLeftFork, Runnable pickRightFork,
                           Runnable eat, Runnable putLeftFork, Runnable putRightFork) throws InterruptedException {
        int l = philosopher;
        int r = (philosopher + 1) % 5;
        room.acquire();
        fork[l].acquire();
        fork[r].acquire();
        try {
            pickLeftFork.run();
            pickRightFork.run();
            eat.run();
            putLeftFork.run();
            putRightFork.run();
        } finally {
            fork[r].release();
            fork[l].release();
            room.release();
        }
    }
}
