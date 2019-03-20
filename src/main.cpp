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

		// load the parameters
	int num_unit(0), population(0), iterations(0), ga_tol(0);
	double cross_prob(0), mute_prob(0), ppk_gorm(0), ppk_waste(0), sim_tol(0);
	read_file(config, num_unit);
	read_file(config, population);
	read_file(config, iterations);
	read_file(config, cross_prob);
	read_file(config, mute_prob);
	read_file(config, ppk_gorm);
	read_file(config, ppk_waste);
	read_file(config, ppk_waste);
	read_file(config, ga_tol);
	read_file(config, sim_tol);
	cout << "Config sucessfully read in\n";

		// create the parents and children list
	circuit* parents = new circuit[population];
	circuit* children = new circuit[population];

		// initalise the parents, check they are valid and find the fittness of them
	int cnt = 0;
	while (cnt < population) {
		parents[cnt] = circuit(num_unit);
		if (parents[cnt].validate_simple()) {   // if passes simple tests
			parents[cnt].set_units();			// set the cuits within it
			if (parents[cnt].validate_connected())  // if passes more complex tests
				if (parents[cnt].evaluate())		// if it converges to a steady state
					cnt++;
		}
	}

		// initalise the children and set the desired parameters
	for (int i = 0; i < population; i++) {
		children[i] = circuit(num_unit);

		children->cross_prob = parents->cross_prob = cross_prob;
		children->mutate_prob = parents->mutate_prob = mute_prob;
		children->ppkg_gor = parents->ppkg_gor = ppk_gorm;
		children->ppkg_waste = parents->ppkg_waste = ppk_waste;
		children->ga_tol = parents->ga_tol = ga_tol;
		children->sim_tol = parents->sim_tol = ga_tol;

	}

		// iterate to solve
	for (int it = 0; it < iterations; it++) 
		iterate_alg(parents, children, population);
	

		// write the output IMPLEMENT ME!!


	system("pause");

}
