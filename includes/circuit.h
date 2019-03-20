#include "header.h"
#include "cunit.h"

class circuit {
public:
	
<<<<<<< HEAD
		// VIRABLES SET BY USER.
	double mutate_prob	= 0.01;
	double cross_prob	= 0.8;
	double ppkg_gor		= 100;
	double ppkg_waste	= 500;

=======
		// vairables for solving
	int num_nodes = 3;
	int num_pipes = 2 * num_nodes + 1;
	int* connections;
	double out_conc = 0;
	double out_tail = 0;
	double fitness 	= 0;
	cunit* units;
>>>>>>> origin/Validation
	
		// SIMULATION TEAM CODE.
	int num_node;			// number of units
	int adj_list_length;	// number of pipes
	int *adjacency_list;	// array of pipes
	double fitness = 0;		// fitness value
	cunit* units;			// list of unit objects
	

<<<<<<< HEAD
		// methods - setup
	circuit(int num_nodes);
	~circuit();

		// methods - GA
=======
		// methods
	circuit();
	~circuit();
>>>>>>> origin/Validation
	void reproduce(circuit cother_circuit, int* &new_connections);

		// methods - Validate
	bool validate_simple();
	void set_units();
	bool validate_connected();

		// methods - simulation
	void step();
	bool evaluate();
	bool convergence_check(double tol);	
};
