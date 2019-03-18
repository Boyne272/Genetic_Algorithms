#include "header.h"
#include "genetic_algorithm.h"

int main(int argc, char *argv[]) {
	
		// seed the RNG
	srand(time(NULL));
	
		// check an input file was given
	if (argc != 2)
		throw "Invalid number of arguments";
	
		// unpack the input argument
	string input = argv[1];
	ifstream file(input);
	if (!file.is_open())
		throw input + " not found";
	
		// load the file
	stringstream ss;
	string buffer;
	ss << file.rdbuf();
	file.close();
	
		// read in the system size
	getline(ss, buffer, ',');
	const int system_size = stoi(buffer);
	
		// here is where we do things
	
}
