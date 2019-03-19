// DESCRIBE ME 

#include "header.h"
#include "circuit.h"
#include "cunit.h"

int main(int argc, char** argv) {

		// Set up test for vald 3 node system
	circuit test;
	test.num_nodes = 3;
	test.num_pipes = 2 * test.num_nodes + 1;
	int input[] = { 0, 1, 2, 3, 0, 0, 4 };
	test.connections = &input[0];
	
		// make test
	if (!test.validate_simple())
		return -1;
	test.set_cunits();
	if (!test.validate_connected())
		return false;
	cout << "Check Vadility for 3 node system \n";

	    


}
