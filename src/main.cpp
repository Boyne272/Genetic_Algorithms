#include "header.h"
#include "genetic_algorithm.h"
#include "circuit.h"

void read_file(ifstream& file, int& val) {
	string buff;
	stringstream ss;
	getline(file, buff, '\n');
	ss << buff;
	getline(ss, buff, ',');
	getline(ss, buff, ',');
	val = stoi(buff);
}

void read_file(ifstream& file, double& val) {
	string buff;
	stringstream ss;
	getline(file, buff, '\n');
	ss << buff;
	getline(ss, buff, ',');
	getline(ss, buff, ',');
	val = stod(buff);
}

int main(int argc, char *argv[]) {
	
		// seed the RNG
	srand(time(NULL));
	
		// open config file
	ifstream config;
	config.open("config.csv");
	if (!config.is_open()) {
		cout << "Error could not find config file\n";
		return -1;
	}

		// load the units
	int num_unit(0), population(0), iterations(0);
	double cross_prob(0), mute_prob(0), ppk_gorm(0), ppk_waste(0);
	read_file(config, num_unit);
	read_file(config, population);
	read_file(config, iterations);
	read_file(config, cross_prob);
	read_file(config, mute_prob);
	read_file(config, ppk_gorm);
	read_file(config, ppk_waste);

	cout << "Read in: \n"
		<< num_unit << "\n"
		<< population << "\n"
		<< cross_prob << "\n"
		<< mute_prob << "\n"
		<< ppk_gorm << "\n"
		<< ppk_waste << "\n";

	system("pause");
	
		// create the parents and children list
	circuit* parents = new circuit[population];
	circuit* children = new circuit[population];

		// initalise the children
	for (int i = 0; i < population; i++)
		children[i] = circuit(num_unit);

		// initalise the parents and check find the fittness of them
	int i = 0;
	while (i < population) {
		parents[i] = circuit(num_unit);

		if (parents[i].validate_simple()) {  // if passes simple tests
			parents[i].set_units();	// set the cuits within it
			if (parents[i].validate_connected())  // if passes more complex tests
				if (parents[i].evaluate())
					i++;
		}
	}

	for (int it = 0; it < iterations; it++) {
		iterate_alg(parents, children, population);
	}

	cout << "WTF JUST HAPPEND\n";
	system("pause");

}
