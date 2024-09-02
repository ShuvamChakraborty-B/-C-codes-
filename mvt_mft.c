#include<stdio.h>
#include<stdlib.h>
//Function Prototype
void mvt();
void mft ();

typedef struct{
  int process_id;
  int memory_allocated;
}Processes;
int main(){
  int choice;
  while(1){
    printf("\n Memory Management Algorithms\n");
    printf("1. Multiprogramming with a variable number of processes\n");
    printf("2. Multiprogramming with a fixed number of processes\n");
    printf("3.Exit\n");
    printf("4.Enter your choice: ");
    scanf("%d",&choice);
    switch(choice){
      case 1:
        mvt();
      case 2:
        mft();
      case 3:
        exit(0);
      case 4:
        printf("Invalid choice");
      
    }
  }
  return 0;
}
