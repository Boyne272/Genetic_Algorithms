#include "header.h"
#include "circuit.h"
#include "cunit.h"

using namespace std;

circuit::circuit() {
	
		// initalise the cunits
	this->units = new cunit[this->num_node + 2];

	/*for (int i = 0; i < num_node + 2; i++)
		this->units[i] = cunit(i);*/

}

bool circuit::validate_simple() {

		// for every nodes two pipes (not source pipe)
	for (int i = 1; i < numb_pipes; i+=2) {
		const int node = (i - 1) / 2;
		
			// conc and tail pipes have same target node
		if (adjacency_list[i] == adjacency_list[i + 1])
			return false;

			// if conc or tail pipe target there own node (self loop)
		if ((adjacency_list[i] == node) || (adjacency_list[i + 1] == node))
			return false;
	}

	return true;
}


void circuit::set_cunits() {
	// REWRITE.
	// externaly adjacency list will be updated.

	for (int i = 0; i < this->num_node; i++) {
		units[i].id = i;
		units[i].out_conc = adjacency_list[(2 * i) + 1];
		units[i].out_tail = adjacency_list[(2 * i) + 2];
		units[i].conc_mark = false;
		units[i].tail_mark = false;
		units[i].source_mark = false;
		units[i].reset_contents();
	}

	for (int i = this->num_node; i < this->num_node + 2; i++) {
		units[i].id = i;
		units[i].reset_contents();
	}



	

}


bool circuit::validate_connected() {

	units[adjacency_list[0]].mark(units);

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
	// CONSTRUCTOR
	// seting up cell units
	// copies in adjacency list of cells.

	this->adj_list_length = *adj_length;
	// num_node is number of REAL nodes, not including ghost concentrate and tail nodes. 
	this->num_node = (this->adj_list_length - 1) / 2;

	this->adjacency_list = new int[this->adj_list_length];
	for (int i = 0; i < this->adj_list_length; i++) {
		this->adjacency_list[i] = adjacency_array[i];
	}
	// now initialise the Cell Units.

	this->units = new cunit[this->num_node + 2];

	for (int i = 0; i < this->num_node; i++) {
		units[i].id = i;
		units[i].out_conc = adjacency_list[(2 * i) + 1];
		units[i].out_tail = adjacency_list[(2 * i) + 2];
	}

	for (int i = this->num_node; i < this->num_node + 2; i++) {
		units[i].id = i;
	}
}

circuit::~circuit()
{
	delete[] adjacency_list;
	delete[] units;
}

void circuit::step() {
	// stepping function: moves the data from each cell into their respective sending buffers.

	for (int i = 0; i < this->num_node + 2; i++) {
		// for each node, including the dummy outputs

		// PUT IN CALC YIELD 
		// copies the current contents into the old contents - this is used for convergence checks. 
		// and prepares the sending buffer contents.
		// resets current contents to 0, ready to recieve from the other cells.
		units[i].calc_yield();
	}

	// now to move data through the nodes. 
	// just for non dummy nodes.
	for (int i = 0; i < this->num_node; i++) {
		// for each c unit[i] find the c unit it is sending material to. 
		// then add the material being sent to it by c unit[i].

		units[(units[i].out_conc)].contents[0] += units[i].conc_send[0];
		units[(units[i].out_conc)].contents[1] += units[i].conc_send[1];

		units[(units[i].out_tail)].contents[0] += units[i].tail_send[0];
		units[(units[i].out_tail)].contents[1] += units[i].tail_send[1];
	}
}

bool circuit::evaluate() {
	// main evaluation loop.
	// limit is maximum number of iterations if no convergence. 
	int limit = 2000;
	int count = 0;
	double tolerance = 1e-4;
	bool converged = false;


	for (int i = 0; i < this->num_node; i++) {
		this->units[i].reset_contents();
	}

	while ((converged == false) && (count < limit)){
		this->units[this->adjacency_list[0]].contents[0] += 10;
		this->units[this->adjacency_list[0]].contents[1] += 100;
		converged = this->convergence_check(tolerance);
		this->step();
		count++;
	}


	double profit = 0;
	profit = (this->units[this->num_node].contents[0] * 100) - (this->units[this->num_node].contents[1] * 500);

	// if not converged, give worst possible score.
	if (converged == false) {
		this->fitness = (-500 * 100);
	}

	else {
		this->fitness = profit;
	}



	// retuns boolean 
	return converged;
}

bool circuit::convergence_check(double tol) {
	// checks the convergence for each cell.
	for (int i = 0; i < num_node + 2; i++) {
		if (units[i].within_tol(tol) == false) {
			return false;
		}
	}
	return true;
}
