#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

void *numbers_in(void *points)
{

	long p_in = 0;
	long p = (long)points;
	unsigned int seed = getpid() ^ pthread_self();

	for (int i = 0; i < p; i++)
	{
		double x = ((double)rand_r(&seed) / RAND_MAX);
		double y = ((double)rand_r(&seed) / RAND_MAX);

		if (x * x + y * y <= 1)
		{
			p_in++;
		}
	}

	return (void *)p_in;
}

int main(int argc, char *argv[])
{
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	int flags, threads;
	double points;

	flags = 0;
	threads = 1;
	points = 0;

	int option;
	while ((option = getopt(argc, argv, "p:t:b")) != -1)
	{ //get option from the getopt() method
		switch (option)
		{
		case 'p':
			points = atof(optarg);
			break;
		case 't':
			threads = atoi(optarg);
			break;
		case 'b':
			flags = 1;
			break;
		case '?': //used for some unknown options
			printf("unknown option: %c\n", optopt);
			break;
		}
	}

	long points_per_thread = points / threads;
	long sum = 0;

	pthread_t workers[threads];

	for (int i = 0; i < threads; i++)
	{
		pthread_create(&workers[i], NULL, numbers_in, (void *)points_per_thread);
	}

	for (int i = 0; i < threads; i++)
	{
		void *ret_from_thread;
		pthread_join(workers[i], &ret_from_thread);
		sum += (long)ret_from_thread;
	}

	clock_gettime(CLOCK_MONOTONIC, &end);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e9;
	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

	if (flags == 1)
	{
		printf("%.1e \n", points);
		printf("%d \n", threads);
		printf("%.3lf \n", time_taken);
	}
	else
	{
		printf("Total number of points: %.1e \n", points);
		printf("Points within circle: %.1e \n", (double)sum);
		printf("PI estimation: %lf \n", (double)sum / points * 4.0);
		printf("Execution time (s): %.3lf \n", time_taken);
	}

	return 0;
}
