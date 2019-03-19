#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define N 21                  //21 CELLS
#define SIZE 10              //100 CHROMS

using namespace std;

typedef struct Chrom
{
	int bit[N];             // gene of a chrom
	double fit = 0;            // fitness default 0
	double rfit = 0;        // relative fitness, the percentage of all fitness default 0
	double cfit = 0;        // cumulative fitness default 0
}chrom;

// function define
void initialize(chrom *parent_chroms, chrom achrom);
void update_parents_cfit(chrom *chroms_parent, int max_index);
void reproduction(chrom *parent_chroms, chrom *children_chroms);
void fitness(chrom* a_chrom, chrom *cankao);
chrom pick_parent_chrom(chrom *parent_chroms, int max_index, int *check_index);
void crossover(chrom *father, chrom *mother);
void mutation(chrom *a_chrom);
bool valid(chrom *a_chrom);


void main()
{
	int num = 10;                                  // iteration round£»
	int i, Max;
	Max = 0;
	chrom *parent_chroms = new chrom[SIZE];
	chrom *children_chroms = new chrom[SIZE];

	srand(time(NULL));
	chrom a_chrom;
	for (int i = 0; i < N; i++) a_chrom.bit[i] = rand() % N + 1;

	initialize(parent_chroms, a_chrom);    // generate initial population

	cout << "a_chrom = " << endl;
	for (int i = 0; i < N; i++)
	{
		cout << a_chrom.bit[i] << "   ";
	}
	cout << "cankao 's fitness: "<<a_chrom.fit << endl;
	cout << endl;

	for (i = 0; i < num; i++)                        //start iteration num ROUNDS
	{
		cout <<endl<<endl<<"round " << i << endl;

		reproduction(parent_chroms, children_chroms);
		for (int j = 0; j < SIZE; j++)
			children_chroms[j] = parent_chroms[j];
		for (int j = 0; j < SIZE; j++)
			fitness(&parent_chroms[j], &a_chrom);

		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < N; k++)
				cout << parent_chroms[j].bit[k] << "   ";
			cout << endl;
			cout << "Fitness: " << parent_chroms[j].fit << endl;

		}
		cout << endl;
	}
	cout << "final = " << endl;
	for (int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < N; j++)
			cout << parent_chroms[i].bit[j] << "   ";
		cout << endl;
	}
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
			random = rand() % N;                 // random number between 0 to N
			parent_chroms[j].bit[i] = random;
		}

		fitness(&parent_chroms[j], &a_chrom);            // calculate the fitness value of a chrom
	}
}

void fitness(chrom *a_chrom, chrom *cankao)    // get the fitness
{
	double sum=0;
	for (int i = 0; i < N; i++)
		sum += (double)a_chrom->bit[i] / (double)cankao->bit[i];
	a_chrom->fit = -abs(sum - N);

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
	
	while (updata_index < SIZE)
	{
		cout << "updata_index"<<updata_index << endl;
		father = pick_parent_chrom(parent_chroms, max_index, &father_index);           // get a father chrom
		mother = pick_parent_chrom(parent_chroms, max_index, &mother_index);           // get a mother chrom
		cout << "father_index " << father_index << endl;
		cout << "mother_index " << mother_index << endl;
		/*for (int i = 0; i < SIZE; i++)
		{
			cout <<"i" << i << "r "<<parent_chroms[i].rfit << " " << endl;
			cout << "i" << i << "c "<<parent_chroms[i].cfit << " " << endl;
		}*/
		
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
	cout << "reproduction finish" << endl;
}

bool valid(chrom *a_chrom)
{
	return true;
}

void update_parents_cfit(chrom *chroms_parent, int max_index)
{
	// find the minimum fitness(in case thats negative
	double min = chroms_parent[0].fit;
	for (int i = 1; i < SIZE; i++)
		if (chroms_parent[i].fit < min)
			min = chroms_parent[i].fit;
	if (min < 0) {
		for (int i = 0; i < SIZE; i++)
			chroms_parent[i].fit += (-min);
	}

	double sum = 0.0;
	//find the total fitness of the population, not include the one with max fitness
	for (int i = 0; i < SIZE; i++)
			sum = sum + chroms_parent[i].fit;
	//calculate the relative fitness of each member, not include the one with max fitness
	for (int i = 0; i < SIZE; i++)
			chroms_parent[i].rfit = chroms_parent[i].fit / sum;
	//calculate the cumulative fitness
	chroms_parent[0].cfit = chroms_parent[0].rfit;
	for (int i = 1; i < SIZE; i++)
			chroms_parent[i].cfit = chroms_parent[i].rfit + chroms_parent[i - 1].cfit;                  // start point for the next updating round of cfit
}

//pick a chrom base on fitness value choose next populartion
chrom pick_parent_chrom(chrom *parent_chroms, int max_index, int *check_index)
{
	double p = (1.0 + (double)rand()) / (double)(RAND_MAX + 1);                 // a random number between 0 to 1
	cout << p << endl;
	chrom parent;
	for (int i = 0; i < SIZE; i++)
	{
		if (i == 0)
			if (parent_chroms[i].cfit > p)
			{
				*check_index = i;
				parent = parent_chroms[i];
				break;
			}
			else{}
		else
			if (parent_chroms[i].cfit > p && parent_chroms[i - 1].cfit < p)
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
	int random = rand() % 10;
	int random_index, random_change;

	if (random == 5)                       // only 1% random == 5, can be any number between 0 to 100
	{
		random_change = rand() % ((N - 1) / 2 + 2);       // generate random index
		random_index = rand() % N;
		a_chrom->bit[random_index] = random_change;
	}
}