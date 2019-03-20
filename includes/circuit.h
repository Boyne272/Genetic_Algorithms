#pragma once
#include "header.h"
#include "cunit.h"

class circuit {
public:
	
		// VIRABLES SET BY USER
	int population = 100;
	double mutate_prob	= 0.01;
	double cross_prob	= 0.8;
	double ppkg_gor		= 100;
	double ppkg_waste	= 500;
	
		// SIMULATION VAIRABLES
	int num_node;					// number of units
	int adj_list_length;			// number of pipes
	int *adjacency_list = nullptr;	// array of pipes
	double fitness = 0;				// fitness value
	cunit* units = nullptr;			// list of unit objects
	
		// GENETIC ALGORITHM VAIRABLES
	double rfit = 0;        // relative fitness, the percentage of all fitness default 0
	double cfit = 0;        // cumulative fitness default 0


		// methods - setup
	bool default_const = true;
	circuit() {}  // default constructor
	circuit(int num_nodes);
	~circuit();

		// methods - GA
	void mutate();

		// methods - Validate
	bool validate_simple();
	void set_units();
	bool validate_connected();

		// methods - simulation
	void step();
	bool evaluate();
	bool convergence_check(double tol);	
};
