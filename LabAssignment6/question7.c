#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<pthread.h>

int circle_points = 0;
int square_points = 0;

double rand_x; double rand_y; double original_distance;

int interval;

void *runner(void *parameter);

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("This is not allowed\n");
	}
	else
	{
		interval = atoi(argv[1]);
		pthread_t tid[interval * interval];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		srand(time(NULL));
		
		for(int i = 0; i < (interval * interval); i = i+1)
		{
			pthread_create(&tid[i], &attr, runner, NULL);
		}
		
		for(int i = 0; i < (interval * interval); i = i+1)
		{
			pthread_join(tid[i], NULL);
		}	
		
		double pi = (double)(4 * circle_points) / square_points;
		printf("\nFinal Estimated value of Pi is = %f\n", pi);
	} 
	printf("\n");
	return 0;
}

void *runner(void *parameter)
{
	rand_x = (double)(rand() % (interval + 1)) / interval;
	rand_y = (double)(rand() % (interval + 1)) / interval;	
	
	original_distance = (rand_x * rand_x) + (rand_y * rand_y);
	
	if(original_distance <= 1)
	{
		circle_points = circle_points + 1;
	}
	square_points = square_points + 1;
	
	pthread_exit(NULL);
}
