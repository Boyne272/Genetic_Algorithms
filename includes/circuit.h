#include "header.h"
#include "cunit.h"

class circuit {
public:
	
		// vairables for solving
	int num_nodes = 3;
	int num_pipes = 2 * num_nodes + 1;
	int* connections;
	double out_conc = 0;
	double out_tail = 0;
	double fitness 	= 0;
	cunit* units;
	
		// run parameters
	double mutate_prob;
	double cross_prob;
	double num_units;
	double ppkg_gormaium;
	double ppkg_waste;
	

		// methods
	circuit();
	~circuit();
	void reproduce(circuit cother_circuit, int* &new_connections);
	bool validate_simple();
	void set_cunits();
	bool validate_connected();
	void evaluate();
	void costs(); 		// possibly merge with the evalutae
	
};
