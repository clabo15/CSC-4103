/*
Name:          Laborde, Curtis
Email:         clabo15@lsu.edu
Project:       PA-1 (Multithreading)
Instructor:    Feng Chen
Class:         cs4103-sp21
Login ID:      cs410344
*/

//Libraries used in this assignment
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

//Define matrix sizes
#define N 3
#define M 3
#define K 2

//Number of threads to use
#define NUM_THREADS 9

//Construction of matrices
int matA [M][K] = { {1,4}, {2,5}, {3,6} };
int matB [K][N] = { {8,7,6}, {5,4,3} };
int matC [M][N]; //Product of the matrix multiplication

//Temporary structure of i (row) and j (column) to be used in math
struct tmp {
   int i; 
   int j; 
};

//Function to run the thread with no return type
void *thread_func(void *parameter);


//Driver code (main)
int main(int argc, char *argv[]) {

   int a, b; //Used inplace of i and j for driving the for loop for less confusion
   int increment = 0;
   for(a = 0; a < M; a++) {
      for(b = 0; b < N; b++) {
         //Row and column assignment per thread
         struct tmp *entities = (struct tmp *) malloc(sizeof(struct tmp));
         
         //Pass the entity data
         entities->i = a;
         entities->j = b;
         
         //Construction of thread, acknowledging thread id and set of attributes
         pthread_t id;       
         pthread_attr_t attributes;
         
         
         pthread_attr_init(&attributes); //default attributes
         pthread_create(&id,&attributes,thread_func,entities); //build thread
         
         
         pthread_join(id, NULL);
         increment++;
      }
   }

   //For loop to parse though product of the two matrices and print them to screen
   for(a = 0; a < M; a++) {
      for(b = 0; b < N; b++) {
         printf("%d ", matC[a][b]);
      }
      printf("\n");
   }
} //end of main



//Thread function
void *thread_func(void *parameter) {
    
   //Tmp structure to store data
   struct tmp *entities = parameter;
   int a, add = 0; //a used to increment

   //Multiplication of Row by Column
   for(a = 0; a< K; a++){
      add += matA[entities->i][a] * matB[a][entities->j];
   }
   
   //Positioning sum
   matC[entities->i][entities->j] = add;

   //Exit the thread
   pthread_exit(0);
}
