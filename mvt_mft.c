#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void mft();
void mvt();

typedef struct {
    int process_id;
    int memory_allocated;
    int internalfragmentation;
    bool allocation;
} Processes;

int main() {
    int choice;
    while (1) {
        printf("\nMemory Management Algorithms\n");
        printf("1. Multiprogramming with a variable number of processes\n");
        printf("2. Multiprogramming with a fixed number of processes\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                mvt();
                break;
            case 2:
                mft();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

void mvt() {
    int total_memory, remaining_memory, process_memory, total_allocated = 0,process_count=0;
    int process_id = 1;
    Processes proc[100];

    printf("Enter the total memory available (in Bytes): ");
    scanf("%d", &total_memory);
    remaining_memory = total_memory;

    while (remaining_memory > 0) {
        printf("Enter memory required for process %d (in Bytes): ", process_id);
        scanf("%d", &process_memory);

        if (process_memory <= remaining_memory) {
             proc[process_count].process_id = process_id;
            proc[process_count].memory_allocated = process_memory;
            total_allocated += process_memory;
            remaining_memory -= process_memory;
            process_count++;
            printf("Memory is allocated for Process %d\n", process_id);
        } else {
            printf("Memory is Full\n");
            break;
        }

        char choice;
        printf("Do you want to continue (y/n)? ");
        scanf(" %c", &choice);
        if (choice == 'n' || choice == 'N') {
            break;
        }
        process_id++;
    }

   // Print the table header
   
    printf("Process\t\tMemory Allocated\n");
    printf("-------\t\t----------------\n");

    // Print each process's memory allocation
    for (int i = 0; i < process_count; i++) {
        printf("%d\t\t\t\t%d\n", proc[i].process_id, proc[i].memory_allocated);
    }

    // Print summary information
    printf("\nTotal Memory Allocated: %d\n", total_allocated);
    printf("Total External Fragmentation: %d\n", remaining_memory);
}


void mft() {
    int total_memory, block_size, total_process, tif = 0, remaining_memory;
    printf("Enter the total memory available (in Bytes): ");
    scanf("%d", &total_memory);
    printf("Enter the block size (in Bytes): ");
    scanf("%d", &block_size);
    int block_count = total_memory / block_size;
    remaining_memory = total_memory;
    printf("Enter the number of processes: ");
    scanf("%d", &total_process);
    Processes proc[total_process];

    // Process Allocation
    for (int i = 0; i < total_process; i++) {
        proc[i].process_id = i + 1; // Start process ID from 1
        printf("Enter memory required for process %d (in Bytes): ",
               proc[i].process_id);
        scanf("%d", &proc[i].memory_allocated);

        if (proc[i].memory_allocated <= block_size && block_count > 0) {
            proc[i].internalfragmentation = block_size - proc[i].memory_allocated;
            proc[i].allocation = true;
            block_count--;
            remaining_memory -= block_size;
        } else if (block_count == 0) {
            printf(
                "Memory is full; the remaining processes cannot be accommodated.\n");
            proc[i].allocation = false;
        } else {
            printf("Process %d requires more memory than available in a block\n",
                   proc[i].process_id);
            proc[i].allocation = false;
        }
    }

    // Calculate total internal fragmentation
    for (int i = 0; i < total_process; i++) {
        if (proc[i].allocation) {
            tif += proc[i].internalfragmentation;
        }
    }

    // Print process information
    printf("Process\t Memory Required\t Allocated\t Internal Fragmentation\n");
    for (int i = 0; i < total_process; i++) {
        printf("%d\t\t\t %d\t\t\t\t %s\t\t\t\t %d\n", proc[i].process_id,
               proc[i].memory_allocated, proc[i].allocation ? "Yes" : "No",
               proc[i].allocation ? proc[i].internalfragmentation : 0);
    }

    printf("Total Internal Fragmentation is %d\n", tif);
    printf("Total External Fragmentation is %d\n", remaining_memory);
}
