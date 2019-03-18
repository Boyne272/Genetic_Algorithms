// class defined. 
#include "cunit.h"

CUnit::CUnit(int id, int dest_1, int dest_2): id(id), conc_num(dest_1), tail_num(dest_2) {

	for (int i = 0; i < 2; i++) {
		 // initialise values.
		
		this->contents[i] = 0;
	}
}

void CUnit::calc_yield() {
	// first the conc to send
	this->conc_send = 0.2 * this->contents[0] + 0.05 * this->contents[1];
	//this->conc_send[1] = 0.05 * this->contents[1];

	// then the waste stream
	this->tail_send = 0.8 * this->contents[0] + 0.95 * this->contents[1];
	

	// now that the material has moved into the exit buffer we reset the contents of the cell
	this->contents[0] = 0;
	this->contents[1] = 0;
}
// default constructor
CUnit::CUnit() {}
