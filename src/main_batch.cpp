#include "header.h"
#include "genetic_algorithm.h"
#include "circuit.h"


using namespace std;

void read_file(ifstream& file, int& val) {
	string buff;
	stringstream ss;
	getline(file, buff, '\n');
	ss << buff;
	getline(ss, buff, ',');
	getline(ss, buff, ',');

	if (buff == "")
		throw ("Error in loading config data");

	val = stoi(buff);
}

void read_file(ifstream& file, double& val) {
	string buff;
	stringstream ss;
	getline(file, buff, '\n');
	ss << buff;
	getline(ss, buff, ',');
	getline(ss, buff, ',');

	if (buff == "")
		throw ("Error in loading config data");

	val = stod(buff);
}

int main(int argc, char *argv[]) {
	
		// seed the RNG
	srand(time(NULL));
	//srand(100);
	// parameters to solve for
	//const int population = 100;
	//const int num_unit = 5;
	//const int iterations = 2000;	// to be safe
	
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
	read_file(config, ga_tol);
	read_file(config, sim_tol);
	cout << "Config sucessfully read in\n";

	int round = 10;
	int *rounds = new int[round];
	circuit* parents = new circuit[population];
	circuit* children = new circuit[population];
	circuit* tmp;
	int cnt, it, ended=0;
	double old_best;
	int data_num = 0;
	double ref_fitness = 24.8196;
	ofstream out("5_cell_pop_100_mu0.01.txt");
	while (data_num < round)
	{
		cout << data_num<<endl;

		// initalise the children and set the desired parameters
		for (int i = 0; i < population; i++) {
			children[i] = circuit(num_unit, population);
			parents[i] = circuit(num_unit, population);

			children[i].cross_prob = parents[i].cross_prob = cross_prob;
			children[i].mutate_prob = parents[i].mutate_prob = mute_prob;
			children[i].ppkg_gor = parents[i].ppkg_gor = ppk_gorm;
			children[i].ppkg_waste = parents[i].ppkg_waste = ppk_waste;
			children[i].ga_tol = parents[i].ga_tol = ga_tol;
			children[i].sim_tol = parents[i].sim_tol = sim_tol;
		}

		// initalise the parents, check they are valid and find the fittness of them
		cnt = 0;
		while (cnt < population) {
			parents[cnt].radomise();
			if (parents[cnt].validate_simple()) {   // if passes simple tests
				parents[cnt].set_units();			// set the cuits within it
				if (parents[cnt].validate_connected())  // if passes more complex tests
					if (parents[cnt].evaluate())		// if it converges to a steady state
						cnt++;
			}
		}


		// iterate with convergence criteria
		it = 0;
		while (it < iterations) {

			// keep previous best
			old_best = parents[0].fitness;

			// iterate
			iterate_alg(parents, children, population);
			
			// check with previous beast
			if (abs(ref_fitness - children[0].fitness) < 0.01)
			{
				ended++;
				rounds[data_num] = it;
				
				break;
			}
			it++;
			// swap parent and child list
			circuit* tmp = parents;
			parents = children;
			children = tmp;
			
		}
		
		data_num++;
	}
	if (out.is_open())
	{
		for(int i = 0;i< round;i++)
			out << rounds[i] << endl;
	}
	out.close();


		// write the output IMPLEMENT ME!!x

	cout << "algorithm finished\n";

}

