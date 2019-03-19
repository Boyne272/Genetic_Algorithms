 //here is a simple test to check travis is working

#include <iostream>
#include "circuit.h"
#include "cunit.h"


int main(int argc, char** argv) {

		// test 1
	int adj_test1[11]{ 0,4,3,2,0,5,4,4,6,2,1 };
	int adj_length1 = sizeof(adj_test1) / sizeof(adj_test1[0]);
	circuit *test1 = new circuit(adj_test1, &adj_length1);
	test1->evaluate();
	

	if (!(abs(test1->fitness - 24.8162)  < 0.01))
	{
		cout << "failed test 1\n";
		//return -1;
	}


		 //test 2 
	int adj_test2[31]{ 6, 16, 7, 7, 13, 11, 12, 15, 5, 3, 6, 0, 2, 14, 12, 1, 12, 14, 11, 5, 16, 11,9, 4, 1, 0, 8, 5, 10, 2, 6 };
	int adj_length2 = sizeof(adj_test2) / sizeof(adj_test2[0]);
	circuit *test2 = new circuit(adj_test2, &adj_length2);
	test2->evaluate();
	

	if (!(abs(test2->fitness - 10.4723) < 0.01))
	{
		cout << "failed test 2\n";
		//return -1;
	}

	else
	{
		cout << "passed both tests\n";
		system("pause");
		//return 0;
	}
}
