#include "header.h"
#include "circuit.h"
#include "genetic_algorithm.h"
//#define PRINT
	
void prep_parents(circuit* parents, circuit* best_child) {

	const int population = best_child->population;

	// find max and min fitness parent
	double max_fit = parents[0].fitness;
	double min_fit = parents[0].fitness;
	int max_index = 0;
	int min_index = 0;
	for (int i = 1; i < population; i++)
		if (parents[i].fitness > max_fit)
		{
			cout << "child " << i << " beat child " << max_index << " (" << parents[i].fitness << " to " << parents[max_index].fitness << ")\n";
			max_fit = parents[i].fitness;
			max_index = i;
		}
		else if (parents[i].fitness < min_fit) {
			min_fit = parents[i].fitness;
			min_index = i;
		}

		// if every parent is the same atrifically make one bad to prevent pick lock
	if (min_index == max_index) {
		max_fit = parents[0].fitness;
		max_index = 0;			
		min_fit = parents[1].fitness - 1;
		min_index = 1;
	}

		// remain the best parent and first child
	for (int i = 0; i < best_child->adj_list_length; i++)
		best_child->adjacency_list[i] = parents[max_index].adjacency_list[i];


		// in case thats min is negative scale all
	for (int i = 0; i < population; i++)
		parents[i].fitness -= min_fit; // -1 ensures positive


		// find the total fitness of the population
	double sum = 0.0;
	for (int i = 0; i < population; i++)
		sum = sum + parents[i].fitness;

		// calculate the relative fitness of each member
	for (int i = 0; i < population; i++)
		parents[i].rfit = parents[i].fitness / sum;

		// calculate the cumulative fitness for sampling
	parents[0].cfit = parents[0].rfit;
	for (int i = 1; i < population; i++) {
		parents[i].cfit = parents[i].rfit + parents[i - 1].cfit;
		//cout << "c-value " << i << " is " << parents[i].cfit << "\n";
	}
	
		// artificially set the final value to be 1 incase of floating point issues
	parents[population - 1].cfit = 1.;
}


//pick a circuit base on fitness value choose next populartion
void pick_parents(circuit* parents, circuit* &father, circuit* &mother) {
	
	const int population = parents[0].population;
	double p1, p2;
	int father_index = 0, mother_index = 0;
	
		// find the father
	p1 = (double)rand() / (double)RAND_MAX;
	for (int i = 0; i < population; i++) {
		if (p1 < parents[i].cfit) {
			father_index = i;
			father = parents + i;
			break;
		}
	}	

	do {
			// find a mother
		p2 = (double)rand() / (double)RAND_MAX;
		for (int i = 0; i < population; i++) {
			if (p2 < parents[i].cfit) {
				mother_index = i;
				mother = parents + i;
				break;
			}
		}
	} while (father_index == mother_index); // repeat if picked same parent
	
}


void breed(circuit *father, circuit *mother, circuit *son, circuit *daughter) {

	const int num_genes = father->adj_list_length;
	const double prob_cross = father->cross_prob;

		// crossover
	int random = 0;
	const double pick = (double)rand() / RAND_MAX;
	if (pick < prob_cross) {
			// get a random number between 1 to ( N - 1 ) where to swap genes
		random = rand() % (num_genes - 2) + 1;
	}

		// put in fathers genes to son and mother genes to daughter
	for (int i = 0; i < random; i++) {
		son->adjacency_list[i]		= father->adjacency_list[i];
		daughter->adjacency_list[i] = mother->adjacency_list[i];
	}
		// put in mother genes to son and fathers genes to daughter
	for (int i = random; i < num_genes; i++) {
		son->adjacency_list[i] = mother->adjacency_list[i];
		daughter->adjacency_list[i] = father->adjacency_list[i];
	}

		// mutate
	son->mutate();
	daughter->mutate();
}


	// if we only weant one child at the end
void breed(circuit *father, circuit *mother, circuit *child) {

	const int num_genes = father->adj_list_length;
	const double prob_cross = father->cross_prob;

		// on a 50/50 chance swap son and daughter so it is random which one we use
	if (rand() % 2) {
		circuit* tmp = father;
		father = mother;
		mother = tmp;
	}

		// crossover
	int random = 0;
	const double pick = (double)rand() / RAND_MAX;
	if (pick < prob_cross) {
		// get a random number between 1 to ( N - 1 ) where to swap genes
		random = rand() % (num_genes - 2) + 1;
	}

	// put in fathers genes to son and mother genes to daughter
	for (int i = 0; i < random; i++) {
		child->adjacency_list[i] = father->adjacency_list[i];
	}
	// put in mother genes to son and fathers genes to daughter
	for (int i = random; i < num_genes; i++) {
		child->adjacency_list[i] = mother->adjacency_list[i];
	}

		// mutate
	child->mutate();
}



void iterate_alg(circuit* &parents, circuit* &children, int child_len) {

		// find the cfit values for sampling parents and set the best child
	prep_parents(parents, children);  // ISSUE in paralisation (only one node needs)
		// recalculate best childs fiteness
	children[0].set_units();
	children[0].evaluate();

	circuit* mom = nullptr;
	circuit* dad = nullptr;  
	int index_1(1), index_2(2);
	bool alive_1, alive_2;

	// while we want two children
	while (index_2 < child_len) {

			// make the children
		pick_parents(parents, mom, dad);
		breed(mom, dad, children + index_1, children + index_2);
		
			// find if they survived

			// child 1
		alive_1 = false;
		if (children[index_1].validate_simple()) {			// if passes simple tests
			children[index_1].set_units();					// set the cuits within it
			if (children[index_1].validate_connected()) {	// if passes more complex tests
				alive_1 = children[index_1].evaluate();		// chcek convergence and find value
			}
		}

			// child 2
		alive_2 = false;
		if (children[index_2].validate_simple()) {			// if passes simple tests
			children[index_2].set_units();					// set the cuits within it
			if (children[index_2].validate_connected()) {	// if passes more complex tests
				alive_2 = children[index_2].evaluate();		// chcek convergence and find value
			}
		}
		
		
			// if they both survived
		if (alive_1 && alive_2) {
			index_1 = index_2 + 1;
			index_2 += 2;
		}
			// if one survived
		else if (!alive_1 && alive_2) {
			index_2 += 1;
		}
			// if the other survived
		else if (alive_1 && !alive_2) {
			index_1 = index_2; //swap so index_1 < index_2
			index_2 += 1;
		}
	}

		// if we still need one child at the end
	while (index_1 < child_len) {

			// make a single child
		pick_parents(parents, mom, dad);
		breed(mom, dad, children + index_1);

			// child 1
		alive_1 = false;
		if (children[index_1].validate_simple()) {  // if passes simple tests
			children[index_1].set_units();	// set the cuits within it
			if (children[index_1].validate_connected())  // if passes more complex tests
				alive_1 = children[index_1].evaluate();
		}

			// if it survived break the loop
		if (alive_1)
			index_1 = child_len;
	}



		// print the best child
	#ifdef PRINT
		cout << "best child: ";
		for (int i = 0; i < num_nodes * 2 + 1; i++)
			cout << children[0].adjacency_list[i] << " ";
		cout << " value: " << children[0].fitness << "\n";
	#endif // PRINT


}
