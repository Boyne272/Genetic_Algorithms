#include "cunit.h"
#include "Circuit.h"
#include <math.h>
#include <random>
#include <iostream>

using namespace std;



Circuit::Circuit(int *adjacency_array){
	// seting up cell units - can be given to another function to clean up.
	// copies in list.
	adj_list_length = (2 * num_node) + 1;
	for (int i = 0; i < adj_list_length; i++) {
		this->adjacency_list[i] = adjacency_array[i];
	}
	
	// now initialise the Cell Units.
	int cnt = 0;

	for (int i = 0; i < num_node; i++) {
		unit_list[i].id = i;
		unit_list[i].conc_num = adjacency_list[(2 * i) + 1];
		unit_list[i].tail_num = adjacency_list[(2 * i) + 2];
	}
	for (int i = num_node; i < num_node+2; i++) {
		unit_list[i].id = i;
	}



	//for (int i = 1; i < 21; i += 2) {
	//	// initalise normal cells
	//	cout << i << endl;
	//	unit_list[i].id = i - 1;
	//	unit_list[i].conc_num = adjacency_list[i];
	//	unit_list[i].tail_num = adjacency_list[i + 1];
	//}
	
	unit_list[num_node].id = num_node;
	unit_list[num_node+1].id = num_node+1;

}

Circuit::~Circuit() {}

void Circuit::step() {

	for (int i = 0; i < num_node + 2; i++) {
		// for each node, including the dummy outputs
		unit_list[i].calc_yield();
		// calcing the yield on each node resets the internat storage of the output nodes. 
	}
	// now to move data through the nodes. 
	// just for non dummy nodes.
	for (int i = 0; i < num_node; i++) {
		// bit complicated
		// for each c unit[i] find the c unit it is sending material to. 
		// then add the material being sent to it by c unit[i].
		unit_list[(unit_list[i].conc_num)].contents[0] += unit_list[i].conc_send[0];
		unit_list[(unit_list[i].conc_num)].contents[1] += unit_list[i].conc_send[1];

		unit_list[(unit_list[i].tail_num)].contents[0] += unit_list[i].tail_send[0];
		unit_list[(unit_list[i].tail_num)].contents[1] += unit_list[i].tail_send[1];
		
	}
}


int main() {
	//int *adj_test = new int[11];
	
	int adj_test[11]{ 0,4,3,2,0,5,4,4,6,2,1 };


	/*for (int i = 0; i < 11; i++) {
		adj_test[i] = i % 9;
	}
	*/

	Circuit *test = new Circuit(adj_test);

	for (int i = 0; i < 7; i++) {
		test->unit_list[i].reset_contents();
		cout << "ID : "<< test->unit_list[i].id << endl;
		cout << "CONC: " << test->unit_list[i].conc_num << " TAIL: " << test->unit_list[i].tail_num << endl;
		cout << "GORMANIUM: " << test->unit_list[i].contents[0] << " WASTE: " << test->unit_list[i].contents[1] << endl;
	}
	system("pause");

	int limit = 200;

	for (int i = 0; i < limit; i++){
		//cout << "INDEX" << i << endl;
		test->unit_list[0].contents[0] = 10;
		test->unit_list[0].contents[1] = 100;
		test->step();
	}

	/*test->unit_list[0].contents[0] = 10;
	test->unit_list[0].contents[1] = 100;

	test->step();*/

	for (int i = 0; i < 7; i++) {
		cout << "ID : " << test->unit_list[i].id << endl;
		cout << "CONTENTS: GOOD:" << test->unit_list[i].contents[0] << " BAD: " << test->unit_list[i].contents[1] << endl;

	}

	double profit = 0;
	profit = (test->unit_list[5].contents[0] * 100) - (test->unit_list[5].contents[1] * 500);
	cout << "PROFIT: " << profit << endl;







	system("pause");
}