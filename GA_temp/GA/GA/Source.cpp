#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define N 21                  //21 CELLS
#define SIZE 100              //100 CHROMS

using namespace std;

typedef struct Chrom
{
	int bit[N];             // gene of a chrom
	int fit = 0;            // fitness default 0
	double rfit = 0;        // relative fitness, the percentage of all fitness default 0
	double cfit = 0;        // cumulative fitness default 0
}chrom;

// function define
void initialize(chrom *parent_chroms);
void update_parents_cfit(chrom *chroms_parent, int max_index);
void reproduction(chrom *parent_chroms, chrom *children_chroms);
void fitness(chrom* a_chrom);
chrom pick_parent_chrom(chrom *parent_chroms, int max_index, int *check_index);
void crossover(chrom *father, chrom *mother);
void mutation(chrom *a_chrom);
bool valid(chrom *a_chrom);


void main()
{
	int num = 100;                                    // iteration round£»
	int i, Max;
	Max = 0;
	chrom *parent_chroms = new chrom[SIZE];
	chrom *children_chroms = new chrom[SIZE];

	srand(time(0));
	chrom a_chrom;
	
		
	fitness(&a_chrom);

	initialize(parent_chroms);    // generate initial population
	cout << "num" << endl;
	for (i = 0; i < num; i++)                        //start iteration num ROUNDS
	{	
		cout << i <<endl;
		reproduction(parent_chroms, children_chroms);
		parent_chroms = children_chroms;
		for (int j = 0; j < SIZE; j++)
			fitness(&parent_chroms[j]);
	}
	cout << "a_chrom = " << endl;
	for (int i = 0; i < N; i++)
	{
		a_chrom.bit[i] = rand() % N;
		cout << a_chrom.bit[i] << "   ";
	}
	cout << endl;
	cout << "final = " << endl;
	for (int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < N; j++)
			cout << parent_chroms[i].bit[j] << "   ";
		cout << endl;
	}
	system("pause");

}

void initialize(chrom *parent_chroms)    // generate random initial population
{
	int i, j;;
	int random;
	double sum = 0;

	for (j = 0; j < SIZE; j++)                            // loop over all chrom
	{
		for (i = 0; i < N; i++)                       // from first gene to N th gene
		{
			random = rand() % N;                 // random number between 0 to N
			parent_chroms[j].bit[i] = random;
		}

		fitness(&parent_chroms[j]);            // calculate the fitness value of a chrom
	}
}

void fitness(chrom *a_chrom)    // get the fitness
{
	for (int i = 0; i < N; i++)
		a_chrom->fit += a_chrom->bit[i];
}

void reproduction(chrom *parent_chroms, chrom *children_chroms)
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
	update_parents_cfit(parent_chroms, max_index);
	int updata_index = 1, father_index, mother_index;
	chrom father, mother;
	cout << "updata_index" << endl;
	while (updata_index < SIZE)
	{
		cout << updata_index << endl;
		father = pick_parent_chrom(parent_chroms, max_index, &father_index);           // get a father chrom
		mother = pick_parent_chrom(parent_chroms, max_index, &mother_index);           // get a mother chrom
		if (father_index != mother_index)
		{
			crossover(&father, &mother);
			mutation(&father);
			mutation(&mother);
			if (valid(&father))
			{
				children_chroms[updata_index] = father;
				updata_index++;
			}
			if (updata_index >= SIZE)
				break;
			if (valid(&mother))
			{
				children_chroms[updata_index] = mother;
				updata_index++;
			}
		}
			
		
	}
}

bool valid(chrom *a_chrom)
{
	return true;
}

void update_parents_cfit(chrom *chroms_parent, int max_index)
{
	double sum = 0.0;
	//find the total fitness of the population, not include the one with max fitness
	for (int i = 0; i < SIZE; i++)
		if (i != max_index)
			sum = sum + chroms_parent[i].fit;
	//calculate the relative fitness of each member, not include the one with max fitness
	for (int i = 0; i < SIZE; i++)
		if (i != max_index)
			chroms_parent[i].rfit = chroms_parent[i].fit / sum;
	//calculate the cumulative fitness
	//popcurrent[0].cfit = popcurrent[0].rfit;
	int start;
	for (int i = 0; i < SIZE; i++)
		if (i != max_index)
		{
			chroms_parent[i].cfit = chroms_parent[i].rfit;
			start = i;                                                     // start point for the next updating round of cfit
			break;
		}
	chroms_parent[max_index].cfit = 0;                                    // make that one not selectable
	chroms_parent[max_index].rfit = 0;
	for (int i = start; i < SIZE; i++)
		if (i != max_index && (i - 1) != max_index)                                                // in case, start is not zero(can always happen)
			chroms_parent[i].cfit = chroms_parent[i - 1].cfit + chroms_parent[i].rfit;
		else if ((i - 1) == max_index)
			if ((i - 1) == 0)
				chroms_parent[i].cfit = chroms_parent[i].rfit;
			else if ((i - 1) > 0)
				chroms_parent[i].cfit = chroms_parent[i - 2].cfit + chroms_parent[i].rfit;    // finish getting the cfit for all parent except one with max fitness
}

//pick a chrom base on fitness value choose next populartion
chrom pick_parent_chrom(chrom *parent_chroms, int max_index, int *check_index)
{
	double p = (1 + rand()) / (RAND_MAX + 1);                 // a random number between 0 to 1
	chrom parent;
	for (int i = 0; i < SIZE; i++)
	{
		if (i = 0)
			if (parent_chroms[i].cfit > p)
			{
				*check_index = i;
				parent = parent_chroms[i];
				break;
			}
			else{}
		else
			if (parent_chroms[i].cfit > p && parent_chroms[i - 1].cfit<p)
			{
				*check_index = i;
				parent = parent_chroms[i];
				break;
			}
	}
	return parent;
}

void crossover(chrom *father, chrom *mother)
{
	srand(time(0));
	int random = rand() % (N - 2) + 1;               // get a random number between 1 to ( N - 1 )
	int *temp_chrom_bit = new int[random];
	for (int i = 0; i < random; i++)                     // copy the data before random for father
	{
		temp_chrom_bit[i] = father->bit[i];
		father->bit[i] = mother->bit[i];
		mother->bit[i] = temp_chrom_bit[i];
	}
}

void mutation(chrom *a_chrom)
{
	int random = rand() % 100;
	srand(time(0)); 
	int random_index, random_change;

	if (random == 5)                       // only 1% random == 5, can be any number between 0 to 100
	{
		random_change = rand() % ((N - 1) / 2 + 2);       // generate random index
		random_index = rand() % N;
		a_chrom->bit[random_index] = random_change;
	}
}