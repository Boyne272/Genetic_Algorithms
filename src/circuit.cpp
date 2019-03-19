#include "header.h"
#include "circuit.h"
#include "cunit.h"

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

}