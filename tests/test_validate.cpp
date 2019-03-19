
#include "header.h"
#include "circuit.h"
#include "cunit.h"


int main(int argc, char ** argv) {

	// ---------------------- test 1 -------------------------

		// setup valid 3 node stysem
	circuit test_3(3);
	int input1[] = { 0, 1, 2, 3, 0, 0, 4 };
	copy(input1, input1 + 7, test_3.adjacency_list);
	test_3.set_units();

		// run test
	if (!test_3.validate_simple()) {
		cout << "test1 simple failed\n";
		return -1;
	}
	if (!test_3.validate_connected()) {
		cout << "test1 connected failed\n";
		return -1;
	}
	
	// ---------------------- test 3 -------------------------

		// setup invalid 6 node stysem (breaks tail reach)
		// here I reuse test_6 structure as should be possible
	circuit test_6(6);

	int input3[] = { 4, 2, 3, 7, 0, 5, 3, 5, 6, 0, 1, 6 ,0 };
	copy(input3, input3 + 13, test_6.adjacency_list);
	test_6.set_units();

	// run test
	if (!test_6.validate_simple()) {
		cout << "test3 simple failed\n";
		return -1;
	}
	if (test_6.validate_connected()) {
		cout << "test3 connected passed when fail expected \n";
    		return -1; 
	}

	// ---------------------- test 4 -------------------------

		// setup invalid 6 node stysem (breaks concentrate reach)
		// here I reuse test_6 structure as should be possible
	int input4[] = { 2, 6, 3, 5, 0, 1, 5, 6, 0, 0, 7, 4, 7 };
	copy(input4, input4 + 13, test_6.adjacency_list);
	test_6.set_units();

	// run test
	if (!test_6.validate_simple()) {
		cout << "test4 simple failed\n";
		return -1;
	}
	if (test_6.validate_connected()) {
		cout << "test4 connected passed when fail expected \n";
		return -1;
	}


	// ---------------------- test 6 -------------------------

		// setup invalid 6 node stysem (breaks forward reach)	
	int input6[] = { 0, 1, 2, 3, 7, 1, 7, 6, 7, 6, 7, 4 ,7 };
	copy(input6, input6 + 13, test_6.adjacency_list);
	test_6.set_units();

	// run test
	if (!test_6.validate_simple()) {
		cout << "test6 simple failed\n";
		return -1;
	}
	if (test_6.validate_connected()) {
		cout << "test6 connected passed when fail was expected\n";
		return -1;
	}


	// ---------------------- test 7 -------------------------
	//set test for 8 nodes system (break traverse forward )
	circuit test_8(8);
	int input7[] = { 0, 1, 2, 8, 3, 3, 4, 8, 9, 0, 9, 6, 7 ,5, 7, 5, 6};
	copy(input7, input7 + 17, test_8.adjacency_list);
	test_8.set_units();

	// run test
	if (!test_8.validate_simple()) {
		cout << "test7 simple failed\n";
		return -1;
	}
	if (test_8.validate_connected()) {
		cout << "test7 connected passerd when fail was expected \n";
	    	return -1;
	}


	// ---------------------- test 8 -------------------------
	//set test for valid 9 nodes system
	circuit test_9(9);
	int input8[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 10 ,9, 10, 9, 10, 9, 10 };
	copy(input8, input8 + 19, test_9.adjacency_list);
	test_9.set_units();

	// run test
	if (!test_9.validate_simple()) {
		cout << "test8 simple failed\n";
		return - 1;
	}
	if (!test_9.validate_connected()) {
		cout << "test8 connected failed\n";
		return -1;
	}

	// ---------------------- done ---------------------------
	
	cout << "all tests passed\n";
	return 0;

}
