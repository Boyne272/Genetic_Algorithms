#pragma once
#include "header.h"


class cunit {
public:

	int id;			// the number of this unit
	int out_conc;	// concentrate pipe link node
	int out_tail;	// tail pipe link node
	int num_node;	// total number of nodes
	
	int mark = 0;
	bool conc_found = false;
	bool tail_found = false;
	
<<<<<<< HEAD
	void mark_input(cunit* units, int start_node);
	void mark_output(cunit* units, int start_node);

	//void mark(cunit* cunits);
	//cunit(int id) : id(id) {}





	// SIMULATION TEAM CODE 
	cunit(int id, int dest_1, int dest_2);
	cunit();
	// default
	//int conc_num;
	void reset_contents();
	//index of the unit to which this unit’s concentrate stream is connected 
	//int tail_num;
	// the values to send. -i.e have to store the percentage before sending it
	// need a send func. all the sends must come at the same time
	// index 0 is gormanium 
	// index 1 is waste
	double conc_send[2];
	double tail_send[2];
	double contents[2];
	double old_contents[2];
	bool within_tol(double tol);
=======
	void mark(cunit* units, int num_nodes);
>>>>>>> origin/Validation

	void calc_yield();
};
