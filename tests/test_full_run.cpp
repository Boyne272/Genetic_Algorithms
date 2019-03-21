#include "header.h"
#include "genetic_algorithm.h"
#include "circuit.h"


int main() {

		// parameters to solve for
	const int population = 100;
	const int num_unit	 = 5;
	const int iterations = 10000;	// to be safe
	//srand(100);
	srand(time(NULL));


	// create the parents and children list
	circuit* parents = new circuit[population];
	circuit* children = new circuit[population];

		// initalise the children and parents then set the desired parameters
	for (int i = 0; i < population; i++) {
		children[i] = circuit(num_unit, population);
		parents[i] = circuit(num_unit, population);
	}


		// randomise the parents genes, check they are valid and find their fittness 
	int cnt = 0;
	while (cnt < population) {
		parents[cnt].radomise();
		if (parents[cnt].validate_simple()) {   // if passes simple tests
			parents[cnt].set_units();			// set the cuits within it
			if (parents[cnt].validate_connected())  // if passes more complex tests
				if (parents[cnt].evaluate())		// if it converges to a steady state
					cnt++;
		}
	}


		// vairables for convergence criteria
	double old_best;
	int count(1), it(0);

		// iteration loop
	while (it < iterations) {

		// keep previous best
		old_best = parents[0].fitness;

		// iterate
		iterate_alg(parents, children, population);
		it++;

		// check with previous beast
		if (children[0].fitness != old_best)
			count = 1;
		else {
			count++;
			if (count == 2000)
				break;
		}

		// swap parent and child list
		circuit* tmp = parents;
		parents = children;
		children = tmp;
	}

		// check solution matches what is expected
	const double diff = fabs(children[0].fitness - 24.8162);
	if (diff > 0.001) {
		cout << "Failed full run test\n";
		return -1;
	}

		// print test passed
	cout << "5 unit full run gave expected 24.812\n";
	return 0;

}
