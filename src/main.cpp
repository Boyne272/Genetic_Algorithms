#include "header.h"
#include "genetic_algorithm.h"

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
	int num_unit(0), population(0);
	double cross_prob(0), mute_prob(0), ppk_gorm(0), ppk_waste(0);
	read_file(config, num_unit);
	read_file(config, population);
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
	
		// do da thing
	
}
