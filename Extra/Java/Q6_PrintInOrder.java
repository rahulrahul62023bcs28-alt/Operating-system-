// Q6. Print in Order — LeetCode 1114
import java.util.concurrent.*;

class Foo {
    private final Semaphore a = new Semaphore(0);
    private final Semaphore b = new Semaphore(0);

    public void first(Runnable printFirst) {
        printFirst.run();
        a.release();
    }

    public void second(Runnable printSecond) throws InterruptedException {
        a.acquire();
        printSecond.run();
        b.release();
    }

    public void third(Runnable printThird) throws InterruptedException {
        b.acquire();
        printThird.run();
    }
}
