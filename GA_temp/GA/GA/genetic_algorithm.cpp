#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define N 8                  //21 CELLS
#define SIZE 100              //100 CHROMS

using namespace std;

typedef struct Chrom
{
	double bit[N];             // gene of a chrom
	double fit = 0;            // fitness default 0
	double rfit = 0;        // relative fitness, the percentage of all fitness default 0
	double cfit = 0;        // cumulative fitness default 0
}chrom;

// function define
void initialize(chrom *parent_chroms, chrom achrom);
void update_parents_cfit(chrom *chroms_parent);
void reproduction(chrom *parent_chroms, chrom *children_chroms);
void fitness(chrom* a_chrom, chrom *cankao);
void pick_parents(chrom *parent_chroms, chrom *father, chrom *mother);
void crossover(chrom *father, chrom *mother, chrom *son, chrom *daughter);
void mutation(chrom *a_parent, chrom *a_child);
bool valid(chrom *a_chrom);
void make_child(chrom *parent_chroms, chrom *children_chroms);

void main()
{
	int num = 100000;                                  // iteration round£»
	int i, Max;
	Max = 0;
	chrom *parent_chroms = new chrom[SIZE];
	chrom *children_chroms = new chrom[SIZE];
	srand(time(0));
	chrom a_chrom;
	for (int i = 0; i < N; i++) a_chrom.bit[i] = (1.0 + (double)rand()) / (double)(RAND_MAX + 1)*1000.0;

	initialize(parent_chroms, a_chrom);    // generate initial population

	

	for (i = 0; i < num; i++)                        //start iteration num ROUNDS
	{
		
		reproduction(parent_chroms, children_chroms);

		for (int j = 0; j < SIZE; j++)
			parent_chroms[j] = children_chroms[j];
		for (int j = 0; j < SIZE; j++)
			fitness(&parent_chroms[j], &a_chrom);

		/*for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < N; k++)
				cout << parent_chroms[j].bit[k] << "   ";
			cout << endl;
			cout << "Fitness: " << parent_chroms[j].fit << endl;

		}
		cout << endl;*/
	}
	cout << "final = " << endl;
	for (int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < N; j++)
			cout <<parent_chroms[i].bit[j] << "   "  ;
		cout << "rfit =" << parent_chroms[i].rfit;
		cout << endl;
	}
	cout << "a_chrom = " << endl;
	for (int i = 0; i < N; i++)
	{
		cout << a_chrom.bit[i] << "   ";
	}
	cout << "a_chrom 's fitness: " << a_chrom.fit << endl;
	cout << endl;
	system("pause");

}

void initialize(chrom *parent_chroms, chrom a_chrom)    // generate random initial population
{
	int i, j;;
	int random;
	double sum = 0;

	for (j = 0; j < SIZE; j++)                            // loop over all chrom
	{
		for (i = 0; i < N; i++)                       // from first gene to N th gene
		{
			random = (1.0 + (double)rand()) / (double)(RAND_MAX + 1)*1000.0;                 // random number between 0 to N
			parent_chroms[j].bit[i] = random;
		}

		fitness(&parent_chroms[j], &a_chrom);            // calculate the fitness value of a chrom
	}
}

void fitness(chrom *a_chrom, chrom *ref)    // get the fitness
{
	double sum=0;
	for (int i = 0; i < N; i++)
		sum += abs((double)a_chrom->bit[i] - (double)ref->bit[i]);
	//a_chrom->fit = -abs(sum - N);
	a_chrom->fit = -(sum);
}

void reproduction(chrom *parent_chroms, chrom *children_chroms)    // after reproduction, children_chroms becomes next generation
{
	// find max fitness parents
	double Max = parent_chroms[0].fit;
	int max_index = 0;
	for (int i = 1; i < SIZE; i++)
		if (parent_chroms[i].fit > Max)
		{
			Max = parent_chroms[i].fit;
			max_index = i;
		}
	children_chroms[0] = parent_chroms[max_index];               // remain the best parent		
	// get two parents each time and do crossover

	update_parents_cfit(parent_chroms);

	make_child(parent_chroms, children_chroms);
}

bool valid(chrom *a_chrom)
{
	return true;
}

void make_child(chrom *parent_chroms, chrom *children_chroms)
{
	chrom father, mother, son, daughter;
	int updata_index = 1, father_index, mother_index;
	while (updata_index < SIZE)
	{
		pick_parents(parent_chroms, &father, &mother);           // get a father chrom

		crossover(&father, &mother, &son, &daughter);
		mutation(&father, &son);
		mutation(&mother, &daughter);
		if (valid(&son))
		{
			children_chroms[updata_index] = son;
			updata_index++;
		}
		if (updata_index >= SIZE)
			break;
		if (valid(&daughter))
		{
			children_chroms[updata_index] = daughter;
			updata_index++;
		}
	}
}

void update_parents_cfit(chrom *chroms_parent)
{
	// find the minimum fitness(in case thats negative
	double min = chroms_parent[0].fit;
	for (int i = 1; i < SIZE; i++)
		if (chroms_parent[i].fit < min)
			min = chroms_parent[i].fit;
	if (min < 0) {
		for (int i = 0; i < SIZE; i++)
			chroms_parent[i].fit += (-min) + 1;
	}

	double sum = 0.0;
	//find the total fitness of the population, not include the one with max fitness
	for (int i = 0; i < SIZE; i++)
			sum = sum + chroms_parent[i].fit;
	//cout << sum << endl;
	//calculate the relative fitness of each member, not include the one with max fitness
	for (int i = 0; i < SIZE; i++)
			chroms_parent[i].rfit = chroms_parent[i].fit / sum;
	//calculate the cumulative fitness
	chroms_parent[0].cfit = chroms_parent[0].rfit;
	for (int i = 1; i < SIZE; i++)
			chroms_parent[i].cfit = chroms_parent[i].rfit + chroms_parent[i - 1].cfit;                  // start point for the next updating round of cfit
}

//pick a chrom base on fitness value choose next populartion
void pick_parents(chrom *parent_chroms, chrom *father, chrom *mother)
{
	double p1;
	double p2;
	int father_index = 0, mother_index = 0;
	while (father_index == mother_index) {
		p1 = (1.0 + (double)rand()) / (double)(RAND_MAX + 1);                 // a random number between 0 to 1
		p2 = (1.0 + (double)rand()) / (double)(RAND_MAX + 1);                 // a random number between 0 to 1
		for (int i = 0; i < SIZE; i++)
		{
			if (i == 0)
			{
				if (parent_chroms[i].cfit > p1)
				{
					father_index = i;
					*father = parent_chroms[i];
					break;
				}
				if (parent_chroms[i].cfit > p2)
				{
					mother_index = i;
					*mother = parent_chroms[i];
					break;
				}
			}
			else
			{
				if (parent_chroms[i].cfit > p1 && parent_chroms[i - 1].cfit < p1)
				{
					father_index = i;
					*father = parent_chroms[i];
					break;
				}
				if (parent_chroms[i].cfit > p2 && parent_chroms[i - 1].cfit < p2)
				{
					father_index = i;
					*mother = parent_chroms[i];
					break;
				}
			}
		}
	}
}

void crossover(chrom *father, chrom *mother, chrom *son, chrom *daughter)
{
	int random = rand() % (N - 2) + 1;               // get a random number between 1 to ( N - 1 )
	for (int i = 0; i < random; i++)                     // copy the data before random for father
	{
		son->bit[i] = father->bit[i];
		daughter->bit[i] = mother->bit[i];
	}
	for (int i = random; i < N; i++)                     // copy the data before random for father
	{
		son->bit[i] = mother->bit[i];
		daughter->bit[i] = father->bit[i];
	}
}

void mutation(chrom *a_parent, chrom* a_child)
{
	int random = rand() % 100;
	int random_index;
	double random_change;
	for (int i = 0; i < N; i++)
		a_child->bit[i] = a_parent->bit[i];
	if (random == 5)                       // only 1% random == 5, can be any number between 0 to 100
	{
		random_change = (1.0 + (double)rand()) / (double)(RAND_MAX + 1)*1000.0;
		random_index = rand() % N;               // generate random index
		a_child->bit[random_index] = random_change;
	}
}