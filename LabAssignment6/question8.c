#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

int N = 2;

struct data
{
    int** arr;
    int** temp;
    int p;
    int q;
    int n;
};

struct data init_data(int** A, int i, int j, int N);
void* getCofactor(void* params);
int determinant(int** A, int n);
void adjoint(int** A,int** adj);
bool inverse(int** A, float** inverse);
void display(float** A);

int main()
{ 
    printf("Enter the size of the matrix: ");
    scanf("%d", &N);
    int** A;
    A = (int **) malloc(sizeof(int*)*N);
    for(int k = 0; k < N; k++)
        A[k] = (int*)malloc(sizeof(int)*N);
   
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            printf("Enter number [%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
	float** inv;
    inv = (float **) malloc(sizeof(float*)*N);
    for(int k = 0; k < N; k++)
        inv[k] = (float*)malloc(sizeof(float)*N);
	
	printf("\nThe Inverse is :\n"); 
	if (inverse(A, inv))
		display(inv); 
	return 0; 
}

struct data init_data(int** A, int i, int j, int N)
{
    struct data params;
    params.arr = (int **) malloc(sizeof(int*)*N);
    for(int k = 0; k < N; k++)
        params.arr[k] = (int*)malloc(sizeof(int)*N);
    params.arr = A;
    params.temp = (int **) malloc(sizeof(int*)*N);
    for(int k = 0; k < N; k++)
        params.temp[k] = (int*)malloc(sizeof(int)*N);
    params.p = i;
    params.q = j;
    params.n = N;
    return params;
}

void* getCofactor(void* params)
{ 
    struct data* temp = (struct data* )params;
	int i = 0, j = 0; 

	for (int row = 0; row < temp->n; row++)
	{ 
		for (int col = 0; col < temp->n; col++)
		{ 
			if (row != temp->p && col != temp->q)
			{
				temp->temp[i][j++] = temp->arr[row][col]; 
				 
				if (j == temp->n - 1)
				{ 
					j = 0; 
					i++; 
				} 
			} 
		} 
	} 
	
    pthread_exit(0);
} 


int determinant(int** A, int n)
{ 
	int D = 0;
	 
	if (n == 1) 
		return A[0][0];
	int sign = 1;
	
    pthread_t tid[n];
    struct data params[n];
    for(int i = 0; i < n; i++)
	{
        params[i] = init_data(A, 0, i, n);
        pthread_create(&tid[i], NULL, getCofactor, &params[i]);
    }
	
    for(int i = 0; i < n; i++)
        pthread_join(tid[i], NULL);
	
	for (int f = 0; f < n; f++)
	{ 
		 
		D += sign * A[0][f] * determinant(params[f].temp, n - 1); 
		
		sign = -sign; 
	}
	return D;
} 


void adjoint(int** A,int** adj)
{ 
	if (N == 1){ 
		adj[0][0] = 1; 
		return; 
	}
	int sign = 1; 

    pthread_t tid[N][N];
    struct data params[N][N];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
		{
            params[i][j] = init_data(A, i, j, N);
            pthread_create(&tid[i][j], NULL, getCofactor, &params[i][j]);
        }
    }

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            pthread_join(tid[i][j], NULL);
	
	for (int i=0; i<N; i++)
	{ 
		for (int j=0; j<N; j++)
		{
			sign = ((i+j)%2==0)? 1: -1; 
			
			adj[j][i] = (sign)*(determinant(params[i][j].temp, N-1)); 
		} 
	} 
} 


bool inverse(int** A, float** inverse)
{ 

	int det = determinant(A, N); 
	if (det == 0)
	{
		printf("Singular matrix, can't find its inverse\n"); 
		return false; 
	}
	int** adj;
    adj = (int **) malloc(sizeof(int*)*N);
    for(int k = 0; k < N; k++)
        adj[k] = (int*)malloc(sizeof(int)*N); 

	adjoint(A, adj);

	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
			inverse[i][j] = adj[i][j]/(float)det;
	return true; 
} 


void display(float** A)
{ 
	for (int i=0; i<N; i++)
	{ 
		for (int j=0; j<N; j++) 
			printf("%.6f ", A[i][j]);
		printf("\n");
	} 
} 
