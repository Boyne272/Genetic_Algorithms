// here is a simple test to check travis is working

#include "header.h"
#include "genetic_algorithm.h"
#include "circuit.h"

void test_fitness(circuit *instance, int *ref)    // get the fitness
{
	double sum = 0;
	for (int i = 0; i < instance->adj_list_length; i++)
		sum += abs((double)instance->adjacency_list[i] - (double)ref[i]);
	instance->fitness = -(sum);
}


bool test_valid(circuit *instance)
{
	if (rand() % 100 < 90)
		return true;
	else
		return false;
}



int main(int argc, char** argv) {
//
//		// initalise the parents and childeren
//	const int pop = 100;
//	const int num_nodes = 10;
//	const int num_genes = 2 * num_nodes + 1;
//
//	circuit* parents = new circuit[pop];
//	circuit* children = new circuit[pop];
//	for (int i = 0; i < pop; i++) {
//		parents[i] = circuit(num_nodes);
//		children[i] = circuit(num_nodes);
//	}
//
//		// initalise the reference
//	int reference[num_genes];
//	for (int i = 0; i < num_genes; i++)
//		reference[i] = rand() % (num_nodes + 2);
//
//		// intalise parents genes
//	for (int i = 0; i < pop; i++) {
//		/*for (int j = 0; j < num_genes; j++) {
//			parents[i].adjacency_list[j] = rand() % (num_nodes + 2);
//		}*/
//		test_fitness(parents + i, reference);
//	}
//
//		// iterate
//	const int iterations = 100;
//	circuit* mom = nullptr;
//	circuit* dad = nullptr;
//	int index_1, index_2;
//
//	for (int it = 0; it < iterations; it++) {
//		
//			// find the cfit values for sampling parents
//		prep_parents(parents, children);
//
//			// recalculate best childs fiteness
//		test_fitness(children, reference);
//
//			// set the child list indexs (always index1 < index2)
//		index_1 = 1;
//		index_2 = 2;
//
//			// while we want two children
//		while (index_2 < pop) {
//
//			pick_parents(parents, mom, dad);
//
//			// make the children and find if they survived
//			breed(mom, dad, children + index_1, children + index_2);
//			bool alive_1 = test_valid(children + index_1);
//			bool alive_2 = test_valid(children + index_2);
//
//			// if they both survived
//			if (alive_1 && alive_2) {
//				// find there fitness
//				test_fitness(children + index_1, reference);
//				test_fitness(children + index_2, reference);
//				// update the indexs
//				index_1 = index_2 + 1;
//				index_2 += 2;
//			}
//			else if (!alive_1 && alive_2) {
//				// find the live ones fitness fitness
//				test_fitness(children + index_2, reference);
//				// update the survived index
//				index_2 += 1;
//			}
//			else if (alive_1 && !alive_2) {
//				// find the live ones fitness fitness
//				test_fitness(children + index_1, reference);
//				// update the survived index
//				index_1 = index_2; //swap so index_1 < index_2
//				index_2 += 1;
//			}
//		}
//
//			// if we still need one child
//		while(index_1 < pop) {
//			pick_parents(parents, mom, dad);
//
//				// make a single child and find if it survived
//			breed(mom, dad, children + index_1);
//			bool alive_1 = test_valid(children + index_1);
//
//				// if it survived break the loop
//			if (alive_1) {
//				test_fitness(children + index_1, reference);
//				index_1 = pop;
//			}
//		}
//
//			// print the best child
//		cout << "best child: ";
//		for (int i = 0; i < num_nodes * 2 + 1; i++)
//			cout << children[0].adjacency_list[i] << " ";
//		cout << " value: " << children[0].fitness << "\n";
//
//			// swap parent and child list
//		circuit* tmp = parents;
//		parents = children;
//		children = tmp;
//
//	}
//
//		// print finished 
//	cout << "finalchild: ";
//	for (int i = 0; i < num_nodes * 2 + 1; i++)
//		cout << reference[i] << " ";
//	cout << "\n";
//
}
