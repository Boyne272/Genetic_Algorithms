#pragma once
#include "header.h"


class cunit {
public:

//	int id; // the number of this unit
	int out_conc;
	int out_tail;
	
	bool conc_mark = false;
	bool tail_mark = false;
	bool source_mark = false;
	
	void mark(cunit* cunits);
	cunit(int id) : id(id) {}


	// SIMULATION TEAM CODE 
	cunit(int id, int dest_1, int dest_2);
	// default
	cunit();
	//int conc_num;
	void reset_contents();
	//index of the unit to which this unit’s concentrate stream is connected 
	//int tail_num;
	int id;// id num of the cunit.
	//A Boolean that is changed to true if the unit has been seen 
	//bool mark;
	// the values to send. -i.e have to store the percentage before sending it
	// need a send func. all the sends must come at the same time
	// index 0 is gormanium 
	// index 1 is waste
	double conc_send[2];
	double tail_send[2];
	double contents[2];
	double old_contents[2];
	bool within_tol(double tol);

	void calc_yield();
};
