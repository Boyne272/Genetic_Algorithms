#pragma once
class CUnit {
public:
	//index of the unit to which this unit’s concentrate stream is connected 
	CUnit(int id, int dest_1, int dest_2);
	// default
	CUnit();
	int conc_num;
	void reset_contents();
	//index of the unit to which this unit’s concentrate stream is connected 
	int tail_num;
	int id;// id num of the cunit.
	//A Boolean that is changed to true if the unit has been seen 
	bool mark;
	// the values to send. -i.e have to store the percentage before sending it
	// need a send func. all the sends must come at the same time
	// index 0 is gormanium 
	// index 1 is waste
	double conc_send[2];
	double tail_send[2];
	double contents[2];

	void calc_yield();

	/*

	  ...other member functions and variables of CUnit

	*/
};
