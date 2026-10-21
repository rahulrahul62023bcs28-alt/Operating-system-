// Q1. Single-Threaded CPU — LeetCode 1834
#include <stdlib.h>

typedef struct {
    int enq, proc, idx;
} Task;

typedef struct {
    long long a;
    int b;
} Item;

int cmpTask(const void *x, const void *y) {
    Task *a = (Task *)x, *b = (Task *)y;
    if (a->enq != b->enq) return a->enq < b->enq ? -1 : 1;
    return a->idx - b->idx;
}

int less(Item a, Item b) {
    return a.a < b.a || (a.a == b.a && a.b < b.b);
}

void push(Item *h, int *n, Item x) {
    int i = (*n)++;
    while (i && less(x, h[(i - 1) / 2])) {
        h[i] = h[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h[i] = x;
}

Item pop(Item *h, int *n) {
    Item ans = h[0], x = h[--(*n)];
    int i = 0, c;
    while ((c = 2 * i + 1) < *n) {
        if (c + 1 < *n && less(h[c + 1], h[c])) c++;
        if (less(x, h[c])) {
            h[i] = h[c];
            i = c;
        } else break;
    }
    if (*n) h[i] = x;
    return ans;
}

int* getOrder(int** tasks, int tasksSize, int* tasksColSize, int* returnSize) {
    Task *a = malloc(tasksSize * sizeof(Task));
    Item *h = malloc(tasksSize * sizeof(Item));
    int *ans = malloc(tasksSize * sizeof(int));
    int i = 0, n = 0, k = 0;
    long long time = 0;

    for (i = 0; i < tasksSize; i++)
        a[i] = (Task){tasks[i][0], tasks[i][1], i};

    qsort(a, tasksSize, sizeof(Task), cmpTask);

    while (k < tasksSize) {
        if (!n && i >= 0 && k < tasksSize && time < a[i].enq)
            time = a[i].enq;

        while (i < tasksSize && a[i].enq <= time) {
            push(h, &n, (Item){a[i].proc, a[i].idx});
            i++;
        }

        Item t = pop(h, &n);
        ans[k++] = t.b;
        time += t.a;
    }

    free(a);
    free(h);
    *returnSize = tasksSize;
    return ans;
}

/* Simple driver to allow compilation as executable */
int main() {
    // No test harness provided – program compiles successfully.
    return 0;
}
