#pragma once
class Circuit {
public:
	// loose definition for circuit.
	int num_node = 5;
	int adj_list_length = 11;
	
	int adjacency_list[11];
	// storage for the units.
	CUnit unit_list[7];
	// constructor
	Circuit(int *adjacency_array);
	// destructor
	~Circuit();

	void step();




};