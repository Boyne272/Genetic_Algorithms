#include "header.h"
#include "genetic_algorithm.h"
#include "cunit.h"

// cunits is a list of all cunit instances in order
void cunit::mark(cunit* units, int num_nodes) {

		// mark self as reached
	source_mark = true;

		// check if out node is not an exit
	if (out_conc < num_nodes) {

			// if it has bnot been source marked, marked it
		if (!units[out_conc].source_mark)
			units[out_conc].mark(units, num_nodes);
	
	}
		// if this node is next to an exit, mark it
	else if (out_conc == num_nodes)
		conc_mark = true;
	else if (out_conc == num_nodes + 1)
		tail_mark = true;

		// check if the connecting nodes have seen either exit
	if (units[out_conc].conc_mark)
		conc_mark = true;
	if (units[out_conc].tail_mark)
		tail_mark = true;


		// repeat for tail
	if (out_tail < num_nodes) {
		if (!units[out_tail].source_mark)
			units[out_tail].mark(units, num_nodes);
	}		
	else if (out_tail == num_nodes)
		conc_mark = true;
	else if (out_tail == num_nodes + 1)
		tail_mark = true;

	if (units[out_tail].conc_mark)
		this->conc_mark = true;
	if (units[out_tail].tail_mark)
		this->tail_mark = true;

}