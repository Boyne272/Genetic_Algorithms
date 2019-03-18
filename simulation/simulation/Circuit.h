#pragma once
class Circuit {
public:
	// loose definition for circuit.
	int adjacency_list[21];
	// storage for the units.
	CUnit unit_list[12];
	// constructor
	Circuit(int *adjacency_array);
	// destructor
	~Circuit();




};