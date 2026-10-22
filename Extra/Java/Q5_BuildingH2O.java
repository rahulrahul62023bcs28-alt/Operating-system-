// Q5. Building H2O — LeetCode 1117
import java.util.concurrent.*;

class H2O {
    private final Semaphore h = new Semaphore(2, true);
    private final Semaphore o = new Semaphore(1, true);
    private final CyclicBarrier b = new CyclicBarrier(3);
    private final CyclicBarrier done = new CyclicBarrier(3);

    public void hydrogen(Runnable releaseHydrogen) throws InterruptedException {
        h.acquire();
        try {
            b.await();
            releaseHydrogen.run();
            done.await();
        } catch (BrokenBarrierException e) {
            throw new RuntimeException(e);
        } finally {
            h.release();
        }
    }

    public void oxygen(Runnable releaseOxygen) throws InterruptedException {
        o.acquire();
        try {
            b.await();
            releaseOxygen.run();
            done.await();
        } catch (BrokenBarrierException e) {
            throw new RuntimeException(e);
        } finally {
            o.release();
        }
    }
}
