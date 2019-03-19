// DESCRIBE ME 

#include "header.h"
#include "circuit.h"
#include "cunit.h"

int main(int argc, char** argv) {

	//	// Set up test for vald 3 node system
	//circuit test;
	//test.num_nodes = 3;
	//test.num_pipes = 2 * test.num_nodes + 1;
	//int input[] = { 0, 1, 2, 3, 0, 0, 4 };
	//test.connections = &input[0];
	//
	//	// make test
	//if (!test.validate_simple())
	//	return -1;
	//test.set_cunits();
	//if (!test.validate_connected())
	//	return false;
	//cout << "Check Vadility for 3 node system \n";
	//cout << test.validate_connected();




	// Set up test for an invald 5 node system

	//circuit test;
	//test.num_nodes = 6;
	//test.num_pipes = 2 * test.num_nodes + 1;
	//int input[] = { 0, 1, 2, 3, 7, 1, 7, 6, 7, 6, 7, 4 ,7 };
	//test.connections = &input[0];

	//cout << "Check Vadility for 6 node system \n";
	//// make test
	//if (!test.validate_simple())
	//	return -1;
	//test.set_cunits();
	//if (!test.validate_connected())
	//	return false;
	//cout << test.validate_connected();




	// Set up test for invald 6 node system breaks tail reach

	circuit test3(6, 2 * 6 + 1);
	int tmp3[] = { 4, 2, 3, 7, 0, 5, 3, 5, 6, 0, 1, 6 ,0 };
	test3.connections = tmp3;

		// run test
	if (!test3.validate_simple()) { // expected to pass
		cout << "validation test 3 failed\n";
		return -1;
	}
	test3.set_cunits();
	if (test3.validate_connected()) { // expected to fail
		cout << "validation test 3 failed\n";
		return -1;
	}
	//	cout << test4.validate_connected();


	cout << "here" << endl;

	   //Set up test for invald 6 node system breaks concentrate reach
	circuit test4(6, 2 * 6 + 1);
	int tmp[] = { 2, 6, 3, 5, 0, 1, 5, 6, 0, 0, 7, 4, 7 };
	test4.connections = tmp;

	//cout << "Check Vadility for 6 node system breaks concentrate reach: \n";
		// run test
	if (!test4.validate_simple()) { // expected to pass
		cout << "validation test 4 failed\n";
		return -1;
	}
	test4.set_cunits();
	if (test4.validate_connected()) { // expected to fail
		cout << "validation test 4 failed\n";
		return -1;
	}
	//	cout << test4.validate_connected();

}
