#pragma once
#include "header.h"
#include "circuit.h"

void prep_parents(circuit* parents, circuit* best_child);
void pick_parents(circuit* parents, circuit* &father, circuit* &mother);
void breed(circuit *father, circuit *mother, circuit *son, circuit *daughter);
void breed(circuit *father, circuit *mother, circuit *child);
void iterate_alg(circuit* &parents, circuit* &children, int child_len);
