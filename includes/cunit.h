#pragma once
#include "header.h"


class cunit {
public:

	int id;			// the number of this unit
	int out_conc;	// concentrate pipe link node
	int out_tail;	// tail pipe link node
	int num_node;	// total number of nodes
	
	int mark = 0;				// mark if this node has been reached by another node
	bool conc_found = false;	// mark if this node can find conc exit
	bool tail_found = false;	// mark if this node can find tail exit
	
	void mark_input(cunit* units, int start_node);
	void mark_output(cunit* units, int start_node);


	// SIMULATION TEAM CODE 
	cunit(int id, int dest_1, int dest_2);
	cunit();
	void reset_contents();

	//index of the unit to which this unit’s concentrate stream is connected 
	// the values to send. -i.e have to store the percentage before sending it
	// need a send func. all the sends must come at the same time
	// index 0 is gormanium 
	// index 1 is waste
	
	double conc_send[2];		// comment me!!!
	double tail_send[2];
	double contents[2];
	double old_contents[2];
	bool within_tol(double tol);

	void calc_yield();
};
