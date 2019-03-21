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
	
		// read in command line options
	string config_name, out_name;
	if (argc == 1) {
		config_name = "config.csv";
		out_name = "output.csv";
	}
	else if (argc == 2) {
		config_name = argv[1];
		out_name = "output.csv";
	}
	else if (argc == 3) {
		config_name = argv[1];
		out_name = argv[2];
	}



		// open config file
	ifstream config;
	config.open(config_name);
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

		// create the parents and children list
	circuit* parents = new circuit[population];
	circuit* children = new circuit[population];

		// initalise the parents, check they are valid and find the fittness of them
	int cnt = 0;
	while (cnt < population) {
		parents[cnt] = circuit(num_unit, population);
		if (parents[cnt].validate_simple()) {   // if passes simple tests
			parents[cnt].set_units();			// set the cuits within it
			if (parents[cnt].validate_connected())  // if passes more complex tests
				if (parents[cnt].evaluate())		// if it converges to a steady state
					cnt++;
		}
	}

		// initalise the children and set the desired parameters
	for (int i = 0; i < population; i++) {
		children[i] = circuit(num_unit, population);

		children[i].cross_prob	= parents[i].cross_prob		= cross_prob;
		children[i].mutate_prob	= parents[i].mutate_prob	= mute_prob;
		children[i].ppkg_gor	= parents[i].ppkg_gor		= ppk_gorm;
		children[i].ppkg_waste	= parents[i].ppkg_waste		= ppk_waste;
		children[i].ga_tol		= parents[i].ga_tol			= ga_tol;
		children[i].sim_tol		= parents[i].sim_tol		= sim_tol;

	}

		// iterate with convergence criteria
	double old_best;
	int count(1), it(0);
	while (it < iterations) {

			// keep previous best
		old_best = parents[0].fitness;

			// iterate
		iterate_alg(parents, children, population);
		it++;

			// check with previous beast
		if (children[0].fitness != old_best) 
			count = 1;
		else {
			count++;
			if (count == ga_tol)
				break;
		}

			// swap parent and child list
		circuit* tmp = parents;
		parents = children;
		children = tmp;
	}

	cout << "finished iterating\n";

		// write the output IMPLEMENT ME!!x
	ofstream file;
	file.open(out_name, ofstream::app);
	const int it_act = (it != iterations) ? it - ga_tol : it;
	file << "Iterations Val,Iterations Act,Fitness\n"
		<< it << "," << it_act << "," << old_best << "\n";
	file.close();
	parents[0].analysis(out_name);
	cout << "wrote to file " << out_name << "\n";

	/*cout << endl<<"algorithm finished at the " << final_iteration << "th iteration\n";
	cout << "the fitness value of optimum circuit: " << children[0].fitness << endl;
	cout << endl<<"Parameters: "<<endl<<"maximum iterations: " << iterations << endl;
	cout << "population size: " << population << endl;
	cout << "num_units: " << num_unit << endl;*/
	system("pause");

}
