#include "header.h"
#include "circuit.h"
#include "cunit.h"

using namespace std;

circuit::circuit() {
	
		// initalise the cunits
	for (int i = 0; i < numb_nodes; i++)
		this->units[i] = cunit(i);

}

bool circuit::validate_simple() {

		// for every nodes two pipes (not source pipe)
	for (int i = 1; i < numb_pipes; i+=2) {
		const int node = (i - 1) / 2;
		
			// conc and tail pipes have same target node
		if (connections[i] == connections[i + 1])
			return false;

			// if conc or tail pipe target there own node (self loop)
		if ((connections[i] == node) || (connections[i + 1] == node))
			return false;
	}

	return true;
}


void circuit::set_cunits() {

	for (int i = 0; i < numb_nodes; i++) {
		units[i].out_conc = connections[2 * i + 1];
		units[i].out_tail = connections[2 * i + 2];
		units[i].conc_mark = false;
		units[i].tail_mark = false;
		units[i].source_mark = false;
	}

}


bool circuit::validate_connected() {

	units[connections[0]].mark(units);

	for (int i = 0; i < numb_nodes; i++) {
		if (units[i].conc_mark)
			return false;
		if (units[i].tail_mark)
			return false;
		if (units[i].source_mark)
			return false;
	}

	return true;
}

// SIMULATION TEAM CODE: 
// Constructor.

circuit::circuit(int *adjacency_array, int *adj_length) {
	// seting up cell units - can be given to another function to clean up.
	// copies in list.

	this->adj_list_length = *adj_length;
	this->num_node = (this->adj_list_length - 1) / 2;

	this->adjacency_list = new int[this->adj_list_length];
	for (int i = 0; i < this->adj_list_length; i++) {
		this->adjacency_list[i] = adjacency_array[i];
	}



	//cout << "Number of nodes:\t\t" << this->num_node << endl;
	//cout << "Length of adjacency list:\t" << this->adj_list_length << endl;




	// now initialise the Cell Units.
	this->unit_list = new cunit[this->num_node + 2];


	for (int i = 0; i < this->num_node; i++) {
		unit_list[i].id = i;
		unit_list[i].conc_num = adjacency_list[(2 * i) + 1];
		unit_list[i].tail_num = adjacency_list[(2 * i) + 2];
	}
	for (int i = this->num_node; i < this->num_node + 2; i++) {
		unit_list[i].id = i;
	}

	//for (int i = 0; i < this->num_node; i++)
	//{
	//	cout << "i: " << i << " , id:\t" << unit_list[i].id;
	//}

}

circuit::~circuit()
{
	delete[] adjacency_list;
	//delete[] unit_list;
}

void circuit::step() {

	for (int i = 0; i < this->num_node + 2; i++) {
		// for each node, including the dummy outputs
		unit_list[i].calc_yield();
		// calcing the yield on each node resets the internat storage of the output nodes. 
	}
	// now to move data through the nodes. 
	// just for non dummy nodes.
	for (int i = 0; i < this->num_node; i++) {
		// bit complicated
		// for each c unit[i] find the c unit it is sending material to. 
		// then add the material being sent to it by c unit[i].
		//cout << "dest_num: \t" << unit_list[i].conc_num;
		unit_list[(unit_list[i].conc_num)].contents[0] += unit_list[i].conc_send[0];
		unit_list[(unit_list[i].conc_num)].contents[1] += unit_list[i].conc_send[1];

		unit_list[(unit_list[i].tail_num)].contents[0] += unit_list[i].tail_send[0];
		unit_list[(unit_list[i].tail_num)].contents[1] += unit_list[i].tail_send[1];

	}
}

void circuit::evaluate() {
	// for basic limit case - will change to convergence later.

	int limit = 200;

	for (int i = 0; i < this->num_node; i++) {
		this->unit_list[i].reset_contents();
	}

	for (int i = 0; i < limit; i++) {
		//cout << "INDEX" << i << endl;
		//initial feed
		this->unit_list[this->adjacency_list[0]].contents[0] += 10;
		this->unit_list[this->adjacency_list[0]].contents[1] += 100;
		this->step();
	}

	double profit = 0;
	profit = (this->unit_list[this->num_node].contents[0] * 100) - (this->unit_list[this->num_node].contents[1] * 500);

	//cout << profit << endl;
	this->fitness = profit;
}
