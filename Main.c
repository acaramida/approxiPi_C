#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

double points = 0;
double sum = 0;

void* numbers_in(void *arg) {

	unsigned int seed = time(NULL);
	double p_in = 0;
	int *threads = (int*)arg;

	for( int i = 0; i < points/ *threads; i++ )
	{
			double x = ((double)rand_r(&seed) / RAND_MAX);
      double y = ((double)rand_r(&seed) / RAND_MAX);

			if(x * x + y * y <= 1) {
				p_in++;
			}
	}

	sum+=p_in;
}

int main( int argc, const char* argv[] )
{
	int threads = atof(argv[2]);
	points = atof(argv[1]);
	pthread_t workers[threads];

	for( int i = 0; i < threads; i++ )
		{
			pthread_create(&workers[i], NULL, numbers_in, (void*)&threads);
		}

	/* Waiting for threads to complete */
	for (int i = 0; i < threads; i++)
	{
		pthread_join(workers[i], NULL);
	}

	printf(" points: %lf \n", points);
  	printf(" points in: %lf \n", sum);
  	printf(" PI estimation: %lf \n", sum/points * 4.0);

	return 0;
}
