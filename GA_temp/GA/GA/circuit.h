#pragma once
#include "header.h"
#include "cunit.h"

class circuit {
public:


	// SET BY USER. 
	double mutate_prob;
	double cross_prob;
	double num_units;
	double ppkg_gormaium;
	double ppkg_waste;

	// SIMULATION TEAM CODE.
	int num_node;
	int adj_list_length;
	int *adjacency_list;
	double fitness = 0;
	// SIMULATION TEAM CODE END.

	cunit* units;

	// GA TEAM CODE
	int *bit = new int[2 * num_node + 1];           // gene of a chrom
	double fit = 0;            // fitness default 0
	double rfit = 0;        // relative fitness, the percentage of all fitness default 0
	double cfit = 0;        // cumulative fitness default 0
	//GA TEAM CODE


	// run parameters



	// methods
	circuit();
	// constructor
	circuit(int *adjacency_array, int *adj_length); // delete later.
	// destructor
	~circuit();

	void reproduce(circuit cother_circuit, int* &new_connections);

	bool validate_simple();
	void set_cunits();
	bool validate_connected();
	// SIMULATION METHODS.
	void step();
	bool evaluate();
	bool convergence_check(double tol);
};
