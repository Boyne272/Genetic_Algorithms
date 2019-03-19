#include <vector>
#include <iostream>

using namespace std;

class CUnit
{
public:
	// index of the unit to which this unit¡¯s concentrate stream is connected
	int conc_num;
	// index of the unit to which this unit¡¯s tailing stream is connected
	int tails_num;
	// A Boolean that is changed to true if the unit has been seen
	bool mark = false;
	// other member functions and variables of CUnit
};


int num_units;      // set a value to num_units

vector<CUnit> units(num_units);


void mark_units(int unit_num)         // using recursion to traverse the circuit and to mark
{
	if (units[unit_num].mark)                 // If we have seen this unit already exit
	{
		if (units[units[unit_num].conc_num].mark == true && units[units[unit_num].tails_num].mark == true)  // If two streams already been marked
			return;
		else     // one of streams has not been marked yet, and it should be the tailing stream
		{
			if (units[unit_num].tails_num < num_units)
				mark_units(units[unit_num].tails_num);
			else
				// Potentially do something to indicate that you have seen an exit
				return;
		}
	}
	else
	{
		units[unit_num].mark = true;              // Mark that we have now seen the unit

		// If conc_num does not point at a circuit outlet recursively call the function
		if (units[unit_num].conc_num < num_units)
			mark_units(units[unit_num].conc_num);
		else
			// Potentially do something to indicate that you have seen an exit
			// If tails_num does not point at a circuit outlet recursively call the function
			if (units[unit_num].tails_num < num_units)
				mark_units(units[unit_num].tails_num);
			else
				// Potentially do something to indicate that you have seen an exit
				return;
	}
}

int start_unit = 0;

void recursion()
{
	// Use the specification vector to set the conc_num and tails_num values for every unit in the units array
	for (int i = 0; i < num_units; i++)
		units[i].mark = false;
	// Mark every cell that start_unit can see
	mark_units(start_unit);
	for (int i = 0; i < num_units; i++)
	{
		if (units[i].mark)
			cout << "unit: " << i << " has been seen." << endl;        	//  have seen unit i
		else
			cout << "unit: " << i << " has not been seen." << endl;  	// have not seen unit i
	}
}


bool Check_Validity(int *circuit_vector)
{
	// Use the specification vector to set the conc_num and tails_num values for every unit in the units array
	for (int i = 0; i < num_units; i++)
		units[i].mark = false;
	// Mark every cell that start_unit can see
	mark_units(start_unit);
	for (int i = 0; i < num_units; i++)
	{
		if (units[i].mark == false)             // check if every unit is accessible from the feed
		{
			cout << "unit: " << i << " has not been seen." << endl;        	// have not seen unit i
			cout << "Invalid Circuit" << endl;
			return false;
		}
		else
			cout << "Every unit is accessible from the feed." << endl;   // if u dont want these cout, just comment out

		if (units[i].conc_num && units[i].tails_num)   // check if every unit have a route forward to both of the outlet streams
			cout << "Every unit have a route forward to both of the outlet streams." << endl;
		else
		{
			cout << "unit: " << i << " does not have a route forward to both of the outlet streams." << endl;
			cout << "Invalid Circuit" << endl;
			return false;
		}

		if (units[i].conc_num == i || units[i].tails_num == i)   // check if unit is self-recycle
		{
			cout << "unit: " << i << " is self-recycle." << endl;
			cout << "Invalid Circuit" << endl;
			return false;
		}
		else
			cout << "No unit self-recycle." << endl;

		if (units[i].conc_num == units[i].tails_num)    // check if the destination for both products from a unit is the same.
		{
			cout << "unit: " << i << "'s destinations are the same." << endl;
			cout << "Invalid Circuit" << endl;
			return false;
		}
		else
			cout << "The destination for both products from a unit is not the same unit." << endl;
	}
	return true;
}

