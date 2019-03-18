#include "cunit.h"
#include "Circuit.h"
#include <math.h>
#include <random>

using namespace std;



Circuit::Circuit(int *adjacency_array){
	// seting up cell units - can be given to another function to clean up.
	// copies in list.
	for (int i = 0; i < 21; i++) {
		this->adjacency_list[i] = adjacency_array[i];
	}
	
	// now initialise the Cell Units.
	for (int i = 1; i < 21; i += 2) {
		// initalise normal cells
		unit_list[i].id = i - 1;
		unit_list[i].conc_num = adjacency_list[i];
		unit_list[i].tail_num = adjacency_list[i + 1];
	}
	
	unit_list[10].id = 10;
	unit_list[11].id = 11;

}

Circuit::~Circuit() {}


int main() {
	int *adj_test = new int[21];
	for (int i = 0; i < 21; i++) {
		adj_test[i] = rand() % 9;
	}
	
	Circuit *test = new Circuit(adj_test);




}