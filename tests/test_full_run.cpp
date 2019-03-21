#include "header.h"
#include "genetic_algorithm.h"
#include "circuit.h"


int main() {

		// parameters to solve for
	const int population = 100;
	const int num_unit	 = 5;
	const int iterations = 2000;	// to be safe
	//srand(time(NULL));
	//srand(3);


		// create the parents and children list
	circuit* parents = new circuit[population];
	circuit* children = new circuit[population];


		// initalise the children
	for (int i = 0; i < population; i++)
		children[i] = circuit(num_unit);


		// initalise the parents and check find the fittness of them
	int i = 0;
	while (i < population) {
		parents[i] = circuit(num_unit);

		if (parents[i].validate_simple()) {  // if passes simple tests
			parents[i].set_units();	// set the cuits within it
			if (parents[i].validate_connected())  // if passes more complex tests
				if (parents[i].evaluate())
					i++;
		}
	}

		// iterate
	for (int it = 0; it < iterations; it++) {
		iterate_alg(parents, children, population);
			// swap parent and child list
		circuit* tmp = parents;
		parents = children;
		children = tmp;
	}

		// check solution matches what is expected
	// changed to fabs.
	const double diff = fabs(parents[0].fitness - 24.8126);
	if (diff > 0.001) {
		cout << "Failed full run test\n";
		return -1;
	}

		// print test passed
	cout << "5 unit full run gave expected 24.812\n";
	return 0;

}