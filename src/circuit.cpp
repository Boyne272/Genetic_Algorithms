#include "header.h"
#include "circuit.h"
#include "cunit.h"

using namespace std;

// -------------------------- setup ------------------------------

circuit::circuit(int num_node, int pop) 
	: population(pop), num_node(num_node), adj_list_length(1 + 2*num_node){

		// setup the adjasency list and initalise it as random nodes
	adjacency_list = new int[adj_list_length];
	
		// initalise the cunits (include the exit nodes too)
	units = new cunit[num_node + 2];
	for (int i = 0; i < num_node + 2; i++) {
		units[i].num_node = num_node;
		units[i].id = i;
	}
}

void circuit::killme() {
	// this is need becuase for some reason if you overwirte one instance
	// with a second instance the 1st deconstructor is called after the 2nd
	// constructor, meaning that memory is immidiately killed after assigned
	delete[] adjacency_list;
	delete[] units;
}


void circuit::radomise() {
	for (int i = 0; i < adj_list_length; i++)
		this->adjacency_list[i] = rand() % (num_node + 2);
}

// -------------------------- validation ------------------------------

bool circuit::validate_simple() {

		// for every nodes two pipes (not source pipe)
	for (int i = 1; i < adj_list_length; i+=2) {

		const int node = (i - 1) / 2;
			// conc and tail pipes have same target node
		if (adjacency_list[i] == adjacency_list[i + 1])
			return false;

			// if conc or tail pipe target there own node (self loop)
		if ((adjacency_list[i] == node) || (adjacency_list[i + 1] == node))
			return false;
	}

		// check if every node is present
	for (int i = 0; i < num_node; i++) {
		bool found = false;
		for (int j = 0; j < adj_list_length; j++) {
			if (adjacency_list[j] == i)
				found = true;
		}
		if (!found)
			return false;
	}

		// check the input node is not an exit node
	if (adjacency_list[0] >= num_node)
		return false;

	return true;
}


void circuit::set_units() {

		// set all internal nodes to new adjaceny list
	for (int i = 0; i < this->num_node; i++) {
		units[i].input_gor = input_gor;
		units[i].input_waste = input_waste;
		units[i].id = i;
		units[i].out_conc = adjacency_list[(2 * i) + 1];
		units[i].out_tail = adjacency_list[(2 * i) + 2];
		units[i].mark = -1;
		units[i].conc_found = false;
		units[i].tail_found = false;
		units[i].reset_contents();
	}

		// for the two exit nodes
	for (int i = this->num_node; i < this->num_node + 2; i++) {
		units[i].input_gor = input_gor;
		units[i].input_waste = input_waste;
		units[i].id = i;
		units[i].reset_contents();
	}
}


bool circuit::validate_connected() {

		// start enterance test
	const int in_node = adjacency_list[0];
	units[in_node].mark_input(units, in_node);

		// check each node was reached
	for (int i = 0; i < num_node; i++)
		if (units[i].mark != in_node)
			return false;

		// for each node do the exit tests
	for (int i = 0; i < num_node; i++) {

			// the source node by reaching every other node much reach both exits
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


	// moves the data from each cell into their respective sending buffers.
void circuit::step() {

		// for each node, including the outputs
	for (int i = 0; i < this->num_node + 2; i++) {

		// calcs the yeild for this step by flowing fluid through all the pipes 
		units[i].calc_yield();
	}

	// now to move data through non dummy nodes.
	for (int i = 0; i < this->num_node; i++) {
		// find the unit each pipe sends to and add the material sent by unit[i].


		const int conc = (units[i].out_conc); // slow?


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
	int limit = 20000;  // limit is maximum number of iterations if no convergence. 
	int count = 0;
	double tolerance = sim_tol;
	bool converged = false;
	bool convergence_debug_flag = false;


	for (int i = 0; i < this->num_node; i++) {
		this->units[i].reset_contents(); // sets contets to 10 gormanium 100 waste.
	}

	while ((converged == false) && (count < limit)){
			// change in and out conc flows.
		this->units[this->adjacency_list[0]].contents[0] += input_gor; // input feed to the circuit. 
		this->units[this->adjacency_list[0]].contents[1] += input_waste;
		converged = this->convergence_check(tolerance);
		this->step();
		count++;
	}

	if (convergence_debug_flag) cout << "count was: " << count << endl;


	double profit = 0;
	profit = (this->units[this->num_node].contents[0] * ppkg_gor) - (this->units[this->num_node].contents[1] * ppkg_waste);
	//cout << this->units[this->num_node].contents[0] << "  " << this->units[this->num_node].contents[1] << endl;
	
	// if not converged, give worst possible score.
	if (converged == false) {
		this->fitness = (-ppkg_waste * input_waste);
	}

	else {
		this->fitness = profit;
	}

		// retruns boolean on wether converged or not
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




// -------------------------- reproduction ------------------------------

void circuit::mutate()
{
	double random;
	int random_change;

		// for each gene
	for (int i = 0; i < adj_list_length; i++) {
		random = (double)rand() / RAND_MAX;
		if (random < mutate_prob) {
			random_change = rand() % (num_node + 2);
			this->adjacency_list[i] = random_change;
		}
	}
}

// ------------------------- analysis ------------------------------------

void circuit::save(int iterations, ofstream &file, string additional) {

	// headings for the save columns
	// iterations, fitness, num_node, Concentrate gor amount, 
	// Concentrate waste amount, Tail gor amount, Tail waste amount, ppk gor, ppk conc, config\n

	file << iterations << ","
		<< fitness << ","
		<< num_node << ","
		<< units[num_node].contents[0] << ","
		<< units[num_node].contents[1] << ","
		<< units[num_node + 1].contents[0] << ","
		<< units[num_node + 1].contents[1] << ","
		<< ppkg_gor << ","
		<< ppkg_waste << ","
		<< adjacency_list[0];
	for (int i = 1; i < adj_list_length; i++)
		file << "-" << adjacency_list[i];
	file << "," << additional << "\n";

}
