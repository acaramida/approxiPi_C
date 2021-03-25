#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* numbers_in(void* points) {

		long p_in = 0;
		long p = (long)points;
		unsigned int seed = getpid() ^ pthread_self();

		for( int i = 0; i < p; i++ )
		{
			double x = ((double)rand_r(&seed) / RAND_MAX);
	    double y = ((double)rand_r(&seed) / RAND_MAX);

			if(x * x + y * y <= 1) {
				p_in++;
			}
		}

		return (void*) p_in;
}

void main( int argc, char* argv[] )
{
	int threads = atoi(argv[2]);
  	double points = atof(argv[1]);
	long points_per_thread = points/threads;
	long sum = 0;

	pthread_t workers[threads];

	for( int i = 0; i < threads; i++ )
	{
		pthread_create(&workers[i], NULL, numbers_in, (void *)points_per_thread);
	}

	for (int i = 0; i < threads; i++)
	{
		void* ret_from_thread;
		pthread_join(workers[i], &ret_from_thread);
		sum += (long)ret_from_thread;
	}

	printf("points: %.10e \n", points);
  	printf("points in: %.10e \n", (double)sum);
  	printf("PI estimation: %lf \n", (double)sum/points * 4.0);

}
