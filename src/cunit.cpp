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


//void cunit::mark(cunit* units) {
//
//		// mark self as reached
//	source_mark = true;
//
//		// check if out node is not an exit
//	if (out_conc < numb_nodes) {
//
//			// if it has bnot been source marked, marked it
//		if (!units[out_conc].source_mark)
//			units[out_conc].mark(units);
//		
//			// on way back if liked node has found an exit
//			// mark this node as connected to the exit
//		if (units[out_conc].conc_mark)
//			conc_mark = true;
//		if (units[out_conc].tail_mark)
//			tail_mark = true;
//	
//	}
//		// if this node is next to an exit, mark it
//	else if (out_conc == numb_nodes)
//		conc_mark = true;
//	else if (out_conc == numb_nodes + 1)
//		tail_mark = true;
//
//
//		// repeat for tail
//	if (out_tail < numb_nodes) {
//		if (!units[out_tail].source_mark)
//			units[out_tail].mark(units);
//		if (units[out_tail].conc_mark)
//			this->conc_mark = true;
//		if (units[out_tail].tail_mark)
//			this->tail_mark = true;
//	}		
//	else if (out_tail == numb_nodes)
//		conc_mark = true;
//	else if (out_tail == numb_nodes + 1)
//		tail_mark = true;
//
//}


// ------------------------------- simulation -------------------------------------------


cunit::cunit(int id, int dest_1, int dest_2) : id(id), out_conc(dest_1), out_tail(dest_2) {

	for (int i = 0; i < 2; i++) {
		// initialise values.

		this->contents[i] = 0;
	}
}

void cunit::reset_contents() {
	for (int i = 0; i < 2; i++) {
		// initialise values.
		this->old_contents[i] = 1; 
		// resets old contents as differently to contents 
		// this means that they will not be detected as converged on the first step.
		this->contents[i] = 0;
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
	//cout << abs(contents[0] - old_contents[0]) << "    " << abs(contents[1] - old_contents[1]) << "     " << id <<endl;
	if ((std::abs((double)(contents[0] - old_contents[0])) < tol) && (std::abs((double)(contents[1] - old_contents[1])) < tol)) {
		//cout << "within tolerance" << endl;
		return true;

	}
	//cout << abs(contents[0] - old_contents[0]) << "    " << abs(contents[1] - old_contents[1]) << endl;
	else {
		//cout << " not in tolerance" << endl;
		return false;
	}
}

// default constructor
cunit::cunit() {}		///////////// do we still need this !?!?!?!?