#pragma once
#include "header.h"
#include "cunit.h"

class circuit {
public:
	
		// VIRABLES SET BY USER
	double mutate_prob	= 0.01;		// probability of mutating
	double cross_prob	= 0.8;		// probability of ginetic crossing
	double ppkg_gor		= 100;		// price per kg gormanium
	double ppkg_waste	= 500;		// cost per kg waste
	double ga_tol		= 1000;		// IMPLEMENT ME!!!
	double sim_tol		= 1e-6;		// used as convergence tolerance // IMPLEMENTED.
	double input_gor	= 10;		// IMPLEMENT ME!!!
	double input_waste  = 100;		// used as convergence tolerance // IMPLEMENTED.
	

		// SIMULATION VAIRABLES
	int population;					// the total number of circuits
	int num_node;					// number of units
	int adj_list_length;			// number of pipes
	int *adjacency_list = nullptr;	// array of pipes
	double fitness;					// fitness value
	cunit* units = nullptr;			// list of unit objects
	

		// GENETIC ALGORITHM VAIRABLES
	double rfit = 0;        // relative fitness, the percentage of all fitness default 0
	double cfit = 0;        // cumulative fitness default 0


		// methods - setup
	circuit() {}	// default constructor
	~circuit() {}	// memory is handled through the kill me function
	circuit(int num_node, int pop = -1);
	void radomise();	// randomise genese for initial selection
	void killme();		// manually delete memory due to reassignment issue

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

		// methods - analysis
	void save(int fitness, ofstream &file, string additional = "");
};
