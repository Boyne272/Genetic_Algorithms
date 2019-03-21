#include "header.h"
#include "genetic_algorithm.h"
#include "cunit.h"


void cunit::mark_input(cunit* units, int start_node) {
	
	mark = start_node;  // mark self

	for (auto node : { out_conc, out_tail })		// for each out pipe
		if (node < num_node) {					// if pipe not an exit
			//cout << "we are looking at node: " << node << " from node: " << this->id << "\n";
			if (units[node].mark != start_node)		// if pipe has not been marked
				units[node].mark_input(units, start_node);	// mark it
		}
}

void cunit::mark_output(cunit* units, int start_node) {

	mark = start_node;  // mark self

	for (auto node : { out_conc, out_tail }) {  	// for each out pipe
		
		if (node < num_node) {					// if pipe not an exit
			if (units[node].mark != start_node)	// if pipe has not been marked
				units[node].mark_output(units, start_node);	// mark it
		}
		else if (node == num_node) { // if is an exit tell the start node
			//cout << "node " << this->id << " found exit for node" << start_node << "\n";
			units[start_node].conc_found = true;
			}
		else if (node == num_node + 1) {  // if is an exit tell the start node
			//cout << "node " << this->id << " found exit for node" << start_node << "\n";
			units[start_node].tail_found = true;
		}
	}
}


// ------------------------------- simulation -------------------------------------------


cunit::cunit(int id, int dest_1, int dest_2) : id(id), out_conc(dest_1), out_tail(dest_2) {

	for (int i = 0; i < 2; i++) {
		// initialise values.

		this->contents[i] = 0; // reset out contents aswell?
	}
}

void cunit::reset_contents() {
	int test_mode = 3; // parameter for testing different methods of initialisation 
	// test mode 0 -> resets empty
	// test mode 1 -> resets full with 10 g, 100 w. 
	// test mode 2 -> resets with contents from previous parent simulation
	// test mode 3 -> resets using diff allocations of input
	if (test_mode == 2) {
		this->contents[0] = this->old_contents[0]; // changed to initialise with full pipes - converges faster.
		this->contents[1] = this->old_contents[1];

	}
	
	for (int i = 0; i < 2; i++) {
		// initialise values.
		this->old_contents[i] = 1; 
		// resets old contents as differently to contents 
		// this means that they will not be detected as converged on the first step.
		if (test_mode == 0) {
			this->contents[i] = 0;
		}
		
	}
	if (test_mode == 1) {
		this->contents[0] = 10; // changed to initialise with full pipes - converges faster.
		this->contents[1] = 100;
	}
	if (test_mode == 3) {
		this->contents[0] = input_gor; // changed to initialise with full pipes - converges faster.
		this->contents[1] = input_waste;
	}


	
}
void cunit::calc_yield() {
	// first the conc to send

	// copies the current contents into old contents.
	this->old_contents[0] = this->contents[0];
	this->old_contents[1] = this->contents[1];

	this->conc_send[0] = 0.2 * this->contents[0];
	this->conc_send[1] = 0.05 * this->contents[1];
	//this->conc_send[1] = 0.05 * this->contents[1];

	// then the waste stream
	this->tail_send[0] = 0.8 * this->contents[0];
	this->tail_send[1] = 0.95 * this->contents[1];


	// now that the material has moved into the exit buffer we reset the contents of the cell
	this->contents[0] = 0;
	this->contents[1] = 0;
}

bool cunit::within_tol(double tol) {
	// checks if within 
	if ((fabs((double)(contents[0] - old_contents[0])) < tol) &&
		(fabs((double)(contents[1] - old_contents[1])) < tol)) {
		return true;
	}
	else {
		return false;
	}
}

