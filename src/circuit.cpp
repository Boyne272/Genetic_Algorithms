#include "header.h"
#include "circuit.h"
#include "cunit.h"

<<<<<<< HEAD
using namespace std;

// -------------------------- setup ------------------------------

circuit::circuit(int num_node) : num_node(num_node), adj_list_length(1 + 2*num_node) {
	
		// initalise the cunits (include the exit nodes too)
	units = new cunit[num_node + 2];
	for (int i = 0; i < num_node + 2; i++) {
		units[i].num_node = num_node;
		units[i].id = i;
	}

		// setup the adjasency list
	adjacency_list = new int[adj_list_length];
=======
circuit::circuit() {

		// initalise the cunits
	units = new cunit[num_nodes];
	for (int i = 0; i < num_nodes; i++)
		units[i].id = i;

}

circuit::~circuit() {

	delete[] this->units;
>>>>>>> origin/Validation

}

circuit::~circuit()
{
	delete[] adjacency_list;
	delete[] units;
}

// -------------------------- validation ------------------------------

bool circuit::validate_simple() {

		// for every nodes two pipes (not source pipe)
<<<<<<< HEAD
	for (int i = 1; i < adj_list_length; i+=2) {
=======
	for (int i = 1; i < num_pipes; i+=2) {
>>>>>>> origin/Validation
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


void circuit::set_units() {

<<<<<<< HEAD
		// set all internal nodes to new adjaceny list
	for (int i = 0; i < this->num_node; i++) {
		units[i].id = i;
		units[i].out_conc	= adjacency_list[(2 * i) + 1];
		units[i].out_tail	= adjacency_list[(2 * i) + 2];
		units[i].mark		= false;
		units[i].conc_found	= false;
		units[i].tail_found	= false;
		units[i].reset_contents();
=======
	for (int i = 0; i < num_nodes; i++) {
		units[i].out_conc = connections[2 * i + 1];
		units[i].out_tail = connections[2 * i + 2];
		units[i].conc_mark = false;
		units[i].tail_mark = false;
		units[i].source_mark = false;
>>>>>>> origin/Validation
	}

		// for the two exit nodes
	for (int i = this->num_node; i < this->num_node + 2; i++) {
		units[i].id = i;
		units[i].reset_contents();
	}
}


bool circuit::validate_connected() {

<<<<<<< HEAD
		// start enterance test
	const int in_node = adjacency_list[0];
	units[in_node].mark_input(units, in_node);

		// check each node was reached
	for (int i = 0; i < num_node; i++)
		if (units[i].mark != in_node)
			return false;

		// for each node do the exit tests
	for (int i = 0; i < num_node; i++) {

			// the source node by reaching very other node much reach both exits
		if (i == adjacency_list[0])
			continue;

			// start that nodes backwards test
		units[i].mark_output(units, i);
		
			// if either the exit pipes were not found fail
		//cout << "node " << node << " " << units[node].tail_found << " "
		//	<< units[node].conc_found << "\n";
		if (!(units[i].tail_found && units[i].conc_found))
			return false;
	}

	return true;
}


// -------------------------- simulation ------------------------------

//circuit::circuit(int *adjacency_array, int *adj_length) {
//	// CONSTRUCTOR
//	// seting up cell units
//	// copies in adjacency list of cells.
//
//	this->adj_list_length = *adj_length;
//	// num_node is number of REAL nodes, not including ghost concentrate and tail nodes. 
//	this->num_node = (this->adj_list_length - 1) / 2;
//
//	this->adjacency_list = new int[this->adj_list_length];
//	for (int i = 0; i < this->adj_list_length; i++) {
//		this->adjacency_list[i] = adjacency_array[i];
//	}
//	// now initialise the Cell Units.
//
//	this->units = new cunit[this->num_node + 2];
//
//	for (int i = 0; i < this->num_node; i++) {
//		units[i].id = i;
//		units[i].out_conc = adjacency_list[(2 * i) + 1];
//		units[i].out_tail = adjacency_list[(2 * i) + 2];
//	}
//
//	for (int i = this->num_node; i < this->num_node + 2; i++) {
//		units[i].id = i;
//	}
//}


	// moves the data from each cell into their respective sending buffers.
void circuit::step() {

		// for each node, including the outputs
	for (int i = 0; i < this->num_node + 2; i++) {

		// PUT IN CALC YIELD 
		// copies the current contents into the old contents - this is used for convergence checks. 
		// and prepares the sending buffer contents.
		// resets current contents to 0, ready to recieve from the other cells.
		units[i].calc_yield();
	}

	// now to move data through non dummy nodes.
	for (int i = 0; i < this->num_node; i++) {
		// find the unit each pipe sends to and add the material sent by unit[i].

		const int conc = (units[i].out_conc);
		units[conc].contents[0] += units[i].conc_send[0];
		units[conc].contents[1] += units[i].conc_send[1];

		const int tail = (units[i].out_tail);
		units[tail].contents[0] += units[i].tail_send[0];
		units[tail].contents[1] += units[i].tail_send[1];
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
=======
		// set the input pipe to start marking nodes
	units[connections[0]].mark(units, num_nodes);

		// check all nodes see source and both exits
	for (int i = 0; i < num_nodes; i++) {
		if (!units[i].conc_mark)
			return false;
		if (!units[i].tail_mark)
			return false;
		if (!units[i].source_mark)
			return false;
	}
	return true;
}
>>>>>>> origin/Validation
