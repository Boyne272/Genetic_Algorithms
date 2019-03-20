 // here is a few tests for the evaluatie methods on circuit class

#include "header.h"
#include "circuit.h"
#include "cunit.h"


int main(int argc, char** argv) {
	// ---------------------- test 1 -------------------------

		// setup the circuit
	int len1 = 5;
	circuit test1(len1);
	int input1[] = { 0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1 };
	copy(input1, input1 + 2*len1 + 1, test1.adjacency_list);

		// run the test
	test1.set_units();
	test1.evaluate();
	const double tmp1 = test1.fitness - 24.8162;
	if (fabs(tmp1) > 0.01) {
		cout << "failed test 1\n";
		return -1;
	}

	// ---------------------- test 2 -------------------------

		// setup the circuit
	int len2 = 15;
	circuit test2(len2);
	int input2[] = { 6, 16, 7, 7, 13, 11, 12, 15, 5, 3, 6, 0, 2, 14, 12, 
		1, 12, 14, 11, 5, 16, 11,9, 4, 1, 0, 8, 5, 10, 2, 6 };
	copy(input2, input2 + 2*len2 + 1, test2.adjacency_list);

		// run the test
	test2.set_units();
	test2.evaluate();
	const double tmp2 = test2.fitness - 10.4712;
	if (fabs(tmp2) > 0.01) {
		cout << "failed test 2\n";
		return -1;
	}


	// ---------------------- test 3 -------------------------
	// this is the same circuit as test 1 but with index ids swapped
	// also recycles the circuit instance which out main code will do

		// setup the circuit
	//int len3 = 5;
	//int input3[] = { 1, 0, 3, 2, 1, 5, 0, 0, 6, 2, 4 };
	//copy(input3, input3 + 2 * len3 + 1, test1.adjacency_list);


		// run the test
	//test1.set_units();
	//test1.evaluate();
	//const double tmp3 = test1.fitness - 24.8162;
	//if (fabs(tmp3) > 0.01) {
	//	cout << "failed test 3\n";
	//	return -1;
	//}

	
	
	
	cout << "all test passed \n";
	return 0;

	
}
//	int adj_length1 = sizeof(adj_test1) / sizeof(adj_test1[0]);
//	circuit *test1 = new circuit(adj_test1, &adj_length1);
//	test1->evaluate();
//	
//
//	const double tmp = test1->fitness - 24.8162;
//	if (!(fabs(tmp) < 0.01)) {
//		cout << "failed test 1\n";
//		return -1;
//	}
//
//
//		 // test 2 
//	int adj_test2[31]{ 6, 16, 7, 7, 13, 11, 12, 15, 5, 3, 6, 0, 2, 14, 12, 1, 12, 14, 11, 5, 16, 11,9, 4, 1, 0, 8, 5, 10, 2, 6 };
//	int adj_length2 = sizeof(adj_test2) / sizeof(adj_test2[0]);
//	circuit *test2 = new circuit(adj_test2, &adj_length2);
//	test2->evaluate();
//	
//	const double tmp2 = test2->fitness - 10.4712;
//	if (!(fabs(tmp2) < 0.01)) {
//		cout << "failed test 2\n";
//		return -1;
//	}
//
//
//	cout << test2->fitness << endl;
//		// finished
//
//	
//
//
//	//circuit *test3 = new circuit();
//	//test3->adjacency_list = adj_test1;
//	//test3->set_cunits();
//
//	//const double tmp3 = test3->fitness - 24.8162;
//	//if (!(fabs(tmp3) < 0.01)) {
//	//	cout << "failed test 1\n";
//	//	return -1;
//	//}
//	////int adj_test1[11]{ 0,4,3,2,0,5,4,4,6,2,1 };
//
//	//cout << "passed both tests\n";
//
//	//system("pause");
//	return 0;
//
//	
//}
