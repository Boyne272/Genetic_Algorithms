#include "header.h"
#include "genetic_algorithm.h"
#include "cunit.h"

// cunits is a list of all cunit instances in order
void cunit::mark(cunit* units) {

		// mark self as reached
	source_mark = true;

		// check if out node is not an exit
	if (out_conc < numb_nodes) {

			// if it has bnot been source marked, marked it
		if (!units[out_conc].source_mark)
			units[out_conc].mark(units);
		
			// on way back if liked node has found an exit
			// mark this node as connected to the exit
		if (units[out_conc].conc_mark)
			conc_mark = true;
		if (units[out_conc].tail_mark)
			tail_mark = true;
	
	}
		// if this node is next to an exit, mark it
	else if (out_conc == numb_nodes)
		conc_mark = true;
	else if (out_conc == numb_nodes + 1)
		tail_mark = true;


		// repeat for tail
	if (out_tail < numb_nodes) {
		if (!units[out_tail].source_mark)
			units[out_tail].mark(units);
		if (units[out_tail].conc_mark)
			this->conc_mark = true;
		if (units[out_tail].tail_mark)
			this->tail_mark = true;
	}		
	else if (out_tail == numb_nodes)
		conc_mark = true;
	else if (out_tail == numb_nodes + 1)
		tail_mark = true;

}