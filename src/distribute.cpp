#include <header.h>

	// find the workshare for each processor
void find_distribution(int population, int num_processors, int my_id, 
	int& my_population, int& my_start) {

		// divide work equally amoungst processors
	my_population = population / num_processors;
	
		// find the remainder and distribute it
	const int remainder = population % num_processors;
	if (my_id < remainder)
		my_population++;

		// if you are not the first node account for additional first child
	if (my_id > 0)
		my_population++;
}