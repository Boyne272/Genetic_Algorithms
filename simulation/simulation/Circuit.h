#pragma once
class Circuit {
public:
	// loose definition for circuit.
	int num_node;
	int adj_list_length;
	

	int *adjacency_list;
	// storage for the units.
	CUnit *unit_list;
	//CUnit unit_list[7];
	// constructor
	Circuit(int *adjacency_array, int *adj_length);
	// destructor
	~Circuit();
	double fitness = 0;

	void step();
	void evaluate();





};