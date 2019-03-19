#include "header.h"
#include "cunit.h"

class circuit {
public:
	
		// vairables for solving
	int* connections;

	double out_conc = 0;
	double out_tail = 0;

	// SIMULATION TEAM CODE.
	int num_node;
	int adj_list_length;
	int *adjacency_list;
	// storage for the units.
	cunit *unit_list;
	//CUnit unit_list[7];
	// constructor
	circuit(int *adjacency_array, int *adj_length);
	// destructor
	~circuit();
	double fitness = 0;
	void step();
	bool evaluate();
	bool convergence_check(double tol);

	// SIMULATION TEAM CODE END.


	cunit* units;
	
		// run parameters
	double mutate_prob;
	double cross_prob;
	double num_units;
	double ppkg_gormaium;
	double ppkg_waste;
	

		// methods
	circuit();
	void reproduce(circuit cother_circuit, int* &new_connections);
	bool validate_simple();
	void set_cunits();
	bool validate_connected();
	
	void costs(); 		// possibly merge with the evalutae
	
};
