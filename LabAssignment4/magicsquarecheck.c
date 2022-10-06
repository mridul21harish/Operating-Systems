#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define MAX 1024

struct magic_square
{
    	int values[MAX][MAX];
};

int coloumn_sum(struct magic_square* matrix, int n, int coloumn);

int row_sum(struct magic_square* matrix, int n, int row);

int diagonal1_sum(struct magic_square* matrix, int n);

int diagonal2_sum(struct magic_square* matrix, int n);

void input_matrix(struct magic_square* matrix, int n);

int check_equivalence(int* a, int n);

void print_array(int* a, int n);

int main()
{
    	printf("Enter the size of the square matrix\n");
    	int n;
    	scanf("%d", &n);

    	int shmid = shmget(IPC_PRIVATE, 2*(n+1)*sizeof(int), 0777 | IPC_CREAT);

        struct magic_square* magicSq = (struct magic_square*) malloc(sizeof(struct magic_square));
    
    	input_matrix(magicSq, n);

    	for(int i = 0; i < n; i = i+1)
   	{
        	pid_t pid = fork();

        	if(pid == 0)
        	{
            		int* a = (int*) shmat(shmid, 0, 0);
			a[i] = coloumn_sum(magicSq, n, i);

     			shmdt(a);
                       exit(0);
        	}
    	}

    
    	for(int i = 0; i < n; i = i+1)
   	{
        	pid_t pid = fork();

        	if(pid == 0)
        	{
            		int* a = (int*) shmat(shmid, 0, 0);
                       a[i+n] = row_sum(magicSq, n, i);

            		shmdt(a);
                       exit(0);
        	}
    	}

    	pid_t pid_1 = fork();
    	if(pid_1 == 0)
    	{
		int* a = (int*) shmat(shmid, 0, 0);
		a[2*n] = diagonal1_sum(magicSq, n);

		shmdt(a);
		exit(0);
    	}

        pid_t pid_2 = fork();
    	if(pid_2 == 0)
   	{
                int* a = (int*) shmat(shmid, 0, 0);
                a[2*n+1] = diagonal2_sum(magicSq, n);

                shmdt(a);
        	exit(0);
    	}

    
    	int status;
    	wait(NULL);
    	waitpid(pid_2, &status, 0);
    
    	int* a = (int*) shmat(shmid, 0, 0);

        if(check_equivalence(a, 2*(n+1)) )
        	printf("\nIt is a magic square");
    	else
        	printf("\nIt's not a magic square");

	shmdt(a);
	shmctl(shmid, IPC_RMID, NULL);
        
	return 0;
}

int coloumn_sum(struct magic_square* matrix, int n, int coloumn)
{
    	int sum = 0;

    	for(int i = 0; i < n; i = i+1)
        	sum = sum + matrix->values[i][coloumn];

    	return sum;
}

int row_sum(struct magic_square* matrix, int n, int row)
{
    	int sum = 0;

    	for(int i = 0; i < n; i = i+1)
        	sum = sum + matrix->values[row][i];

    	return sum;
}

int diagonal1_sum(struct magic_square* matrix, int n)
{
    	int sum = 0;

    	for(int i = 0; i < n; i = i+1)
        	sum = sum + matrix->values[i][i];

    	return sum;
}

int diagonal2_sum(struct magic_square* matrix, int n)
{
    	int sum = 0;

    	for(int i = 0; i < n; i = i+1)
        	sum = sum + matrix->values[i][n - 1 - i];

    	return sum;
}

void input_matrix(struct magic_square* matrix, int n)
{
	printf("Enter the matrix row by row\n");
    	for(int i = 0; i < n; i = i+1)
		for(int j = 0; j < n; j = j+1)
            		scanf("%d", &(matrix->values[i][j]));
    
}

int check_equivalence(int* a, int n)
{
    	for(int i = 0; i < n-1; i = i+1)
        	if(a[i] != a[i+1])
			return 0;
        
    	return 1;
}

void print_array(int *a, int n)
{
    	for(int i = 0; i < n; i = i+1)
        	printf(" %d", a[i]);
    	printf("\n");
}
