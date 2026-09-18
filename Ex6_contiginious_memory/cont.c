#include <stdio.h>

#define MAX 20

// Structure to preserve original block IDs after sorting
typedef struct {
    int id;
    int size;
} MemoryBlock;

void sortBlocksAscending(MemoryBlock arr[], int m) {
    int i, j;
    MemoryBlock temp;
    for (i = 0; i < m - 1; i++) {
        for (j = 0; j < m - i - 1; j++) {
            if (arr[j].size > arr[j + 1].size) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortBlocksDescending(MemoryBlock arr[], int m) {
    int i, j;
    MemoryBlock temp;
    for (i = 0; i < m - 1; i++) {
        for (j = 0; j < m - i - 1; j++) {
            if (arr[j].size < arr[j + 1].size) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int process[MAX];
    MemoryBlock initial_blocks[MAX];
    MemoryBlock working_blocks[MAX];

    int allocated[MAX];
    int remaining_at_alloc[MAX];
    int n, m, choice;
    int i, j;

    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    printf("Enter size of each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &process[i]);
    }

    printf("\nEnter number of memory blocks: ");
    if (scanf("%d", &m) != 1) return 1;

    printf("Enter size of each memory block:\n");
    for (i = 0; i < m; i++) {
        initial_blocks[i].id = i + 1; // 1-based indexing for user visibility
        printf("B%d: ", i + 1);
        scanf("%d", &initial_blocks[i].size);
    }

    while (1) {
        // Reset allocation statuses
        for (i = 0; i < n; i++) {
            allocated[i] = -1;
            remaining_at_alloc[i] = -1;
        }

        // Restore initial block sizes to working array
        for (i = 0; i < m; i++) {
            working_blocks[i] = initial_blocks[i];
        }

        printf("\n=============================\n");
        printf("  Memory Allocation Methods\n");
        printf("=============================\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            printf("Exiting Program... Thank you!\n");
            break;
        } else if (choice < 1 || choice > 4) {
            printf("Invalid choice! Try again.\n");
            continue;
        }

        // Apply correct Sorting Logic based on Memory Management Rules
        if (choice == 2) {
            sortBlocksAscending(working_blocks, m);
        } else if (choice == 3) {
            sortBlocksDescending(working_blocks, m);
        }

        // Allocation Loop
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (working_blocks[j].size >= process[i]) {
                    allocated[i] = working_blocks[j].id; // Keep track of original ID
                    working_blocks[j].size -= process[i];
                    remaining_at_alloc[i] = working_blocks[j].size;
                    break; // Choice 1, 2, and 3 all break immediately upon finding the first match post-sorting!
                }
            }
        }

        // Output results table
        printf("\nProcess\tSize\tAllocated Block\tRemaining Block Size\n");
        for (i = 0; i < n; i++) {
            printf("P%d\t%d\t", i + 1, process[i]);
            if (allocated[i] != -1) {
                printf("B%d\t\t%d\n", allocated[i], remaining_at_alloc[i]);
            } else {
                printf("Not Allocated\t-\n");
            }
        }

        // Map the sorted working blocks back to display their final capacities chronologically
        printf("\n--- Final Status of All Blocks ---\n");
        for (i = 1; i <= m; i++) {
            for (j = 0; j < m; j++) {
                if (working_blocks[j].id == i) {
                    printf("B%d: %d\n", i, working_blocks[j].size);
                    break;
                }
            }
        }
    }

    return 0;
}
