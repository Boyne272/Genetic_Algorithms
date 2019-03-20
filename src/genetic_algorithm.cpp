#include "header.h"
#include "circuit.h"
#include "genetic_algorithm.h"
	
void sample_prep(circuit* parents, circuit& best_child) {

	const int population = best_child.population;

	// find max and min fitness parent
	double max_fit = parents[0].fitness;
	double min_fit = parents[0].fitness;
	int max_index = 0;
	int min_index = 0;
	for (int i = 1; i < population; i++)
		if (parents[i].fitness > max_fit)
		{
			max_fit = parents[i].fitness;
			max_index = i;
		}
		else if (parents[i].fitness < min_fit) {
			min_fit = parents[i].fitness;
			min_index = i;
		}

	// remain the best parent and first child
	best_child = parents[max_index];			//////////////// watch this later


		// in case thats min is negative scale all
	if (min_fit < 0) {
		for (int i = 0; i < population; i++)
			parents[i].fitness -= min_fit - 1; // -1 ensures positive
	}

	// find the total fitness of the population
	double sum = 0.0;
	for (int i = 0; i < population; i++)
		sum = sum + parents[i].fitness;

	// calculate the relative fitness of each member
	for (int i = 0; i < population; i++)
		parents[i].rfit = parents[i].fitness / sum;

	// calculate the cumulative fitness for sampling
	parents[0].cfit = parents[0].rfit;
	for (int i = 1; i < population; i++)
		parents[i].cfit = parents[i].rfit + parents[i - 1].cfit;
}


//pick a circuit base on fitness value choose next populartion
void pick_parents(circuit* parents, circuit* &father, circuit* &mother, int population) {
	
	double p1, p2;
	int father_index = 0, mother_index = 0;
	
		// find the father
	p1 = (1.0 + (double)rand()) / (double)(RAND_MAX + 1);
	for (int i = 0; i < population; i++) {
		if (p1 < parents[i].cfit) {
			father_index = i;
			*father = parents[i];
			break;
		}
	}	

	do {
			// find a mother
		p2 = (1.0 + (double)rand()) / (double)(RAND_MAX + 1);
		for (int i = 0; i < population; i++) {
			if (p2 < parents[i].cfit) {
				mother_index = i;
				*mother = parents[i];
				break;
			}
		}
	} while (father_index == mother_index); // repeat if picked same parent
		
}


void breed(circuit *father, circuit *mother, circuit *son, circuit *daughter) {
	const int num_genes = father->num_node;
	const int prob_cross = father->cross_prob;

		// crossover
	int random = 0;
	if (((double)rand() / RAND_MAX) < prob_cross) {
			// get a random number between 1 to ( N - 1 ) where to swap genes
		random = rand() % (num_genes - num_genes) + 1;
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