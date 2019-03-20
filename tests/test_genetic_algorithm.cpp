// here is a simple test to check travis is working

#include "header.h"
#include "circuit.h"

void test_fitness(circuit *instance, circuit *ref)    // get the fitness
{
	double sum = 0;
	for (int i = 0; i < instance->adj_list_length; i++)
		sum += abs((double)instance->adjacency_list[i] - (double)ref->adjacency_list[i]);
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

	circuit * parents = new circuit(100)[100];

}
//	int num = 100000;                                  // iteration round£»
//	int i, Max;
//	Max = 0;
//	circuit *parent_chroms = new chrom[SIZE];
//	circuit *children_chroms = new chrom[SIZE];
//	srand(time(0));
//	circuit a_chrom;
//	for (int i = 0; i < N; i++) a_chrom.bit[i] = (1.0 + (double)rand()) / (double)(RAND_MAX + 1)*1000.0;
//
//	initialize(parent_chroms, a_chrom);    // generate initial population
//
//
//
//	for (i = 0; i < num; i++)                        //start iteration num ROUNDS
//	{
//
//		reproduction(parent_chroms, children_chroms);
//
//		for (int j = 0; j < SIZE; j++)
//			parent_chroms[j] = children_chroms[j];
//		for (int j = 0; j < SIZE; j++)
//			fitness(&parent_chroms[j], &a_chrom);
//
//		/*for (int j = 0; j < SIZE; j++)
//		{
//			for (int k = 0; k < N; k++)
//				cout << parent_chroms[j].bit[k] << "   ";
//			cout << endl;
//			cout << "Fitness: " << parent_chroms[j].fit << endl;
//
//		}
//		cout << endl;*/
//	}
//	cout << "final = " << endl;
//	for (int i = 0; i < SIZE; i++)
//	{
//		for (int j = 0; j < N; j++)
//			cout << parent_chroms[i].bit[j] << "   ";
//		cout << "rfit =" << parent_chroms[i].rfit;
//		cout << endl;
//	}
//	cout << "a_circuit = " << endl;
//	for (int i = 0; i < N; i++)
//	{
//		cout << a_chrom.bit[i] << "   ";
//	}
//	cout << "a_circuit 's fitness: " << a_chrom.fit << endl;
//	cout << endl;
//	system("pause");
//}
