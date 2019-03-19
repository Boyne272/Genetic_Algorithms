// Here we setup tests fot the validate methods on the circuit class

#include "header.h"
#include "circuit.h"
#include "cunit.h"


//int main(int argc, char** argv) {
int tmp() {

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
	
	// ---------------------- test 2 -------------------------

	//	// setup invalid 6 node stysem ()
	circuit test_6(6);
	//int input2[] = { 0, 1, 2, 3, 7, 1, 7, 6, 7, 6, 7, 4 ,7 };
	//copy(input2, input2 + 13, test_6.adjacency_list);
	//test_6.set_units();


	//	// run test
	//if (test_6.validate_simple())
	//	cout << "test_6 simple passed\n";
	//if (test_6.validate_connected())
	//	cout << "test_6 connected passed\n";

	//system("pause");
	
	// ---------------------- test 3 -------------------------

		// setup invalid 6 node stysem (breaks tail reach)
		// here I reuse test_6 structure as should be possible
	int input3[] = { 4, 2, 3, 7, 0, 5, 3, 5, 6, 0, 1, 6 ,0 };
	copy(input3, input3 + 13, test_6.adjacency_list);
	test_6.set_units();

		// run test
	if (!test_6.validate_simple()) {
		cout << "test3 simple failed\n";
		return -1;
	}
	if (test_6.validate_connected()) {
		cout << "test3 connected passed when faile was expected \n";
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
		return - 1;
	}
	if (test_6.validate_connected()) {
		cout << "test4 connected passed when fail as expected \n";
		return -1;
	}

	// ---------------------- test 5 -------------------------
		
	// MAKE MEEEEEEEEEEEE
		// setup invalid 6 node stysem (breaks concentrate reach)
		// here I reuse test_6 structure as should be possible
	//circuit test_x(x);
	//int input5[] = {};
	//copy(input5, input5 + 13, test_x.adjacency_list);
	//test_x.set_units();

	//	// run test
	//if (test_x.validate_simple())
	//	cout << "test5 simple passed\n";
	//if (!test_x.validate_connected())
	//	cout << "test5 connected failed as expected \n";



	cout << "all tests passed\n";
	system("pause");

	return 0;
}