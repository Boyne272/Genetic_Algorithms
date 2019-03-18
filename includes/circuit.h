#include "header.h"
#include "Cunit.h"

class circuit {
public:
	
		// vairables for solving
	int* connections;
	double out_conc = 0;
	double out_tail = 0;
	double fitness 	= 0;
	// need add the cells list
	
		// run parameters
	double mutate_prob;
	double cross_prob;
	double num_units;
	double ppkg_gormaium;
	double ppkg_waste;
	

		// methods
	void reproduce(other_circuit, &new_connections);
	bool validate();
	void evaluate();
	void costs(); 		// possibly merge with the evalutae
	
};