#pragma once

// include any additional package dependencies here

#include <iostream>		// input/output streams

#include <cstdlib>		// random number functions
#include <time.h>		// seeding the RNG with current time

#include <string>		// for taking user input
#include <sstream>		// for reading in string from files
#include <fstream>		// writing/reading files

const int numb_nodes = 5;
const int numb_pipes = 2 * numb_nodes + 1;

using namespace std;
