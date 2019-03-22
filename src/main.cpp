#include "header.h"
#include "genetic_algorithm.h"
#include "circuit.h"

#define PRINT

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

	// find the workshare for each processor
void find_distribution(int population, int num_processors, int my_id,
	int& my_population, int& my_start) {

	// divide work equally amoungst processors
	const int workshare = population / num_processors;
	const int remainder = population % num_processors;

	// find the start point of this processor
	const int offset = (my_id < remainder) ? remainder : my_id;
	my_start = my_id * workshare + offset;

	// find the size of this processors children list
	if (my_id < remainder)
		my_population = workshare + 1;
	else
		my_population = workshare;

	// if you are not the first node account for additional first child
	//if (my_id > 0)
	//	my_population++;
}

void find_message_sizes(int* &size_list, int num_proc, int pop) {
	int pop_dummy, start_dummy;
	for (int i = 0; i < num_proc; i++) {
		find_distribution(pop, num_proc, 0, pop_dummy, start_dummy);
		size_list[i] = pop_dummy;
	}
}


void gather_fitness(double* &fitness_list, circuit* children_list, int circ_num) {
	for (int i = 0; i < circ_num; i++) {
		fitness_list[i] = children_list[i].fitness;
	}
}

void gather_genes(int* &gene_list, int gene_length, circuit* children_list, int circ_num) {
	int index = 0;
	for (int i = 0; i < circ_num; i++) {

		for (int j = 0; j < gene_length; j++) {
			index = (i * gene_length) + j;
			gene_list[index] = children_list[i].adjacency_list[j];
		}
	}
}

void place_data(circuit* &parent_list, double* global_fitness, int* global_genes, 
	int num_parents, int gene_length) {
	for (int i = 0; i < num_parents; i++) {
		parent_list[i].fitness = global_fitness[i];
		for (int j = 0; j < gene_length; j++) {
			const int index = i * gene_length + j;
			parent_list[i].adjacency_list[j] = global_genes[index];
		}
	}

}



int main(int argc, char *argv[]) {
	
	//////////////////////////////////////////////////

	int id(0), p(2);
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	srand(time(NULL) + id * 10);
	double time = MPI_Wtime();

	//////////////////////////////////////////////////
	
	
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


	/////////////////////////////////////////////

	#ifdef PRINT
		cout << id << "-finding_info\n";
		cout.flush();
	#endif // PRINT

		// get this nodes info
	int my_pop, my_start, gene_length;
	gene_length = 2 * num_unit + 1;
	find_distribution(population, p, id, my_pop, my_start);

	int offset = (id == 0) ? 0 : 1;

	#ifdef PRINT
		cout << id << "-info(pop=" << my_pop << " gene_length=" << gene_length << ")\n";
		cout.flush();
	#endif // PRINT

		// setup mpi_gather size lists
	int* fitness_sizes = new int[p];
	int* gene_sizes = new int[p];
	find_message_sizes(fitness_sizes, p, population);
	for (int i = 0; i < p; i++)
		gene_sizes[i] = fitness_sizes[i] * gene_length;

		// setup mpi_gather displacements list
	int* fitness_displacements = new int[p];
	int* gene_displacements = new int[p];
	fitness_displacements[0] = 0;
	gene_displacements[0] = 0;
	for (int i = 1; i < p; i++) {
		fitness_displacements[i] = fitness_displacements[i-1] + fitness_sizes[i];
		gene_displacements[i] = gene_displacements[i-1] + gene_sizes[i];
	}

		// arrays to gather genes and fitness values into for messages
	double* fitness_list = new double[my_pop];
	int* gene_list = new int[my_pop * gene_length];
	double* glob_fitness_list = new double[population];
	int* glob_gene_list = new int[population * gene_length];


	#ifdef PRINT
		cout << id << "-info(found mpi vars)\n";
		cout.flush();
	#endif // PRINT

	/////////////////////////////////////////////


		// create the parents and children list
	circuit* parents = new circuit[population];
	circuit* children = new circuit[my_pop + offset];

		// initalise the parents then set the desired parameters
	for (int i = 0; i < population; i++) {
		parents[i] = circuit(num_unit, population);

		parents[i].cross_prob	= cross_prob;
		parents[i].mutate_prob	= mute_prob;
		parents[i].ppkg_gor		= ppk_gorm;
		parents[i].ppkg_waste	= ppk_waste;
		parents[i].ga_tol		= ga_tol;
		parents[i].sim_tol		= sim_tol;
	}	


		// initalise the children then set the desired parameters
	for (int i = 0; i < my_pop + offset; i++) {
		children[i] = circuit(num_unit, population);

		children[i].cross_prob	= cross_prob;
		children[i].mutate_prob = mute_prob;
		children[i].ppkg_gor	= ppk_gorm;
		children[i].ppkg_waste	= ppk_waste;
		children[i].ga_tol		= ga_tol;
		children[i].sim_tol		= sim_tol;
	}

		// randomise the children genes, check they are valid and find their fittness 
	int cnt = 0;
	while (cnt < my_pop) {
		children[cnt].radomise();
		if (children[cnt].validate_simple()) {   // if passes simple tests
			children[cnt].set_units();			// set the cuits within it
			if (children[cnt].validate_connected())  // if passes more complex tests
				if (children[cnt].evaluate())		// if it converges to a steady state
					cnt++;
		}
	}

	/////////////////////////////////////////////////////
		// send children to become parents


		// gather the information to be sent
	gather_fitness(fitness_list, children + offset, my_pop);
	gather_genes(gene_list, gene_length, children + offset, my_pop);

	#ifdef PRINT
		cout << id << "-preping_to_send_children\n";
		cout.flush();
	#endif // PRINT

		// send children to be first parents
	MPI_Allgatherv(fitness_list, my_pop, MPI_DOUBLE, glob_fitness_list, fitness_sizes,
		fitness_displacements, MPI_DOUBLE, MPI_COMM_WORLD);

	#ifdef PRINT
		cout << id << "-sent(half)\n";
		cout.flush();
	#endif // PRINT

	MPI_Allgatherv(gene_list, my_pop * gene_length, MPI_INT, glob_gene_list, gene_sizes,
		gene_displacements, MPI_INT, MPI_COMM_WORLD);

	#ifdef PRINT
		cout << id << "-sent children\n";
		cout.flush();
	#endif // PRINT

		// put new information into children
	place_data(parents, glob_fitness_list, glob_gene_list, population, gene_length);

	/////////////////////////////////////////////////////


		// vairables for convergence criteria
	double old_best;
	int count(1), it(0);

		// iteration loop
	while (it < iterations) {

			// keep previous best
		old_best = parents[0].fitness;

			// iterate
		#ifdef PRINT
			cout << id << "-iterate(starting)\n";
			cout.flush();
		#endif // PRINT
		iterate_alg(parents, children, my_pop + offset);
		it++;
		#ifdef PRINT
			cout << id << "-iterate(ending)\n";
			cout.flush();
		#endif // PRINT



		/////////////////////////////////////////////////////
			// send children to become parents

			// gather the information to be sent
		gather_fitness(fitness_list, children + offset, my_pop);
		gather_genes(gene_list, gene_length, children + offset, my_pop);

		#ifdef PRINT
			cout << id << "-preping_to_send_children(" << it << ")\n";
			cout.flush();
		#endif // PRINT

		// send children to be first parents
		MPI_Allgatherv(fitness_list, my_pop, MPI_DOUBLE, glob_fitness_list, fitness_sizes,
			fitness_displacements, MPI_DOUBLE, MPI_COMM_WORLD);
		MPI_Allgatherv(gene_list, my_pop * gene_length, MPI_INT, glob_gene_list, gene_sizes,
			gene_displacements, MPI_INT, MPI_COMM_WORLD);

		#ifdef PRINT
			cout << id << "-sent children(" << it << ")\n";
			cout.flush();
		#endif // PRINT

		// put new information into children
		place_data(parents, glob_fitness_list, glob_gene_list, population, gene_length);

		#ifdef PRINT
			cout << id << "-parent[0](" << parents[0].fitness << ")\n";
			cout.flush();
		#endif // PRINT

		/////////////////////////////////////////////////////

			// check with previous beast
		if (parents[0].fitness != old_best) 
			count = 1;
		else {
			count++;
			if (count == ga_tol) {
				#ifdef PRINT
					cout << id << "-we are breaking out(" << it << ")\n";
					cout.flush();
				#endif // PRINT
				break;
			}
		}

	}

	#ifdef PRINT
		cout << id << "-finished iterating\n";
		cout.flush();
	#endif // PRINT

		// write the output
	if (id == 0) {
		ofstream file;
		stringstream ss;
		ss << p << "," << MPI_Wtime() - time << ",";
		file.open(out_name, ofstream::app);
		parents[0].save(it, file, ss.str());
		file.close();
		cout << id << "-wrote to file(" << out_name << ")\n";
	}

		// clean memory with workaround kill function
	for (int i = 0; i < my_pop; i++) {
		children[i].killme();
		parents[i].killme();
	}	
	delete[] children;
	delete[] parents;

	////////////////////////////////////////////////
	MPI_Finalize();
	////////////////////////////////////////////////

}
