#include <stdlib.h>
#include <stdio.h>


void* numbers_in(int *points) {

	long p_in = 0;

	for( int i = 0; i < points; i++ )
		{
			double x = rand();
			double y = rand();

			if(&x * &x + &y * &y <= 1*1)
				p_in++;
		}
	return p_in;
}

int main( int argc, const char* argv[] )
{
	int threads = argv[2];
	int points = argv[1]/&threads;
	long p_in = 0;


	for( int i = 0; i < threads; i++ )
		{
			pthread_create(i, NULL, numbers_in, points);
		}

	double pi_esti = p_in/points * 4.0;

}
