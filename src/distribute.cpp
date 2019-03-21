#include <header.h>

	// find the workshare for each processor
void find_distribution(int population, int num_processors, int my_id, 
	int& my_population, int& my_start) {

		// divide work equally amoungst processors
	const int workshare = population / num_processors;
	const int remainder = population % num_processors;

		// find the start point of this processor
	const int offset = (my_id < remainder) ? remainder : my_id;
	my_start = my_id * workshare + offset;

		// find the size of this processors children list
	if (my_id < remainder)
		my_population = workshare + 1;
	else
		my_population = workshare;

		// if you are not the first node account for additional first child
	if (my_id > 0)
		my_population++;
}



int main() {
//void test_find_distribution()

	int p = 6;
	int population = 100;

	for (int id = 0; id < p; id++) {
		int my_start, my_pop;
		find_distribution(population, p, id, my_pop, my_start);
		cout << "processor " << id << " has "
			<< my_pop << " children (including padding) starting at " << my_start << "\n";
	}

	system("pause");

}