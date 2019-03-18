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
	int bit[N];         // gene of a chrom
	int fit;            // fitness
	double rfit;        //relative fitness, the percentage of all fitness
	double cfit;        //cumulative fitness
}chrom;

// function define
void *initialize(chrom popcurrent[SIZE]);
int fitness(chrom popcurrent[SIZE]);
void *pickchroms_new(chrom popcurrent[SIZE]); // 基于概率分布
void *crossover(chrom popnext[SIZE]);//交叉操作
void *mutation(chrom popnext[SIZE]);//突变
double r8_uniform_ab(double a, double b, int &seed);//生成a~b之间均匀分布的数字
chrom popcurrent[SIZE];
chrom popnext[SIZE];

void main()
{
	int num;                                    // iteration round；
	int i, j, l, Max, k;
	Max = 0;

	cout << "\nWelcome to the Genetic Algorithm！\n";
	cout << "The Algorithm is based on the function y = -x^2 + 5 to find the maximum value of the function.\n";

	cout << ("\nPlease enter the no. of iterations\n:");
	cin >> num;

	srand(time(0));
	initialize(popcurrent);    // generate initial population
	Max = popcurrent[0].fit;  

	for (i = 0; i < num; i++)                        //start iteration
	{

		for (j = 0; j < SIZE; j++)
			popnext[j] = popcurrent[j];           // update the popnext to date

		pickchroms_new(popnext);                    // pick a good parent
		crossover(popnext);                     // do crossover
		mutation(popnext);                      // do mutation

		for (j = 0; j < SIZE; j++)
			popcurrent[j] = popnext[j];                // update all chrom

	}  // 等待迭代终止；
//对于真正随机数是需要注意取较大的迭代次数
	for (l = 0; l < 3; l++)
	{
		if (popcurrent[l].fit > Max)
		{
			Max = popcurrent[l].fit;
		}

	}
	printf("\n 当x等于 %d时，函数得到最大值为： %d ", k, Max);

	system("pause");

}



void *initialize(chrom popcurrent[SIZE])    // generate random initial population
{
	int i, j;;
	int random;
	double sum = 0;

	for (j = 0; j < SIZE; j++)                            // loop over all chrom
	{
		for (i = 0; i < N; i++)                       // from first gene to N th gene
		{
			random = (random % N);                 // random number between 0 to N
			popcurrent[j].bit[i] = random;
		}

		popcurrent[j].fit = fitness(popcurrent);  // calculate the fitness value of a chrom
		sum = sum + popcurrent[j].fit;
	}

	for (j = 0; j < N; j++)
	{
		popcurrent[j].rfit = popcurrent[j].fit / sum;  // calculate relative fitness value, which will be used to choose parents
		popcurrent[j].cfit = 0;                        // init to zero
	}
	return(0);
}

int fitness(chrom popcurrent[SIZE])    // get the fitness
{
	int y;
	y = -(popcurrent[0].bit[0] * popcurrent[0].bit[0]) + 5;
	return(y);
}

//pick a chrom base on fitness value choose next populartion
void *pickchroms_new(chrom popnext[SIZE])
{
	int i; int j;
	double p;
	double sum = 0.0;
	//find the total fitness of the population
	for (i = 0; i < SIZE; i++)
		sum = sum + popnext[i].fit;
	//calculate the relative fitness of each member
	for (i = 0; i < SIZE; i++)
		popnext[i].rfit = popnext[i].fit / sum;
	//calculate the cumulative fitness
	popcurrent[0].cfit = popcurrent[0].rfit;
	for (i = 1; i < SIZE; i++)
		popnext[i].cfit = popnext[i - 1].cfit + popnext[i].rfit;
	for (i = 0; i < SIZE; i++)
	{
		//p = r8_uniform_ab ( 0, 1, seed ); // GENERATE RANDOM NUMBER BETWEEN 0 TO 1
		p = rand() % 10;
		p = p / 10;
		if (p < popnext[0].cfit)
			popcurrent[i] = popnext[0];
		else
			for (j = 0; j < SIZE; j++)
				if (popnext[j].cfit <= p && p < popnext[j + 1].cfit)
				{
					popcurrent[i] = popcurrent[j + 1];                     // todo, here should just direct choose a parent

				}
					
	}
	//  Overwrite the old population with the new one.
	for (i = 0; i < SIZE; i++)
		popnext[i] = popcurrent[i];
	return(0);
}

double r8_uniform_ab(double a, double b, int &seed)
{
	{
		int i4_huge = 2147483647;
		int k;
		double value;

		if (seed == 0)
		{
			std::cerr << "\n";
			std::cerr << "R8_UNIFORM_AB - Fatal error!\n";
			std::cerr << "  Input value of SEED = 0.\n";
			exit(1);
		}

		k = seed / 127773;

		seed = 16807 * (seed - k * 127773) - k * 2836;

		if (seed < 0)
		{
			seed = seed + i4_huge;
		}

		value = (double)(seed) * 4.656612875E-10;

		value = a + (b - a) * value;

		return value;
	}
}

void *crossover(chrom popnext[SIZE])
{
	int random;
	int i;
	srand(time(0)); 
	random = ((random % (N - 2)) + 1);                 //pick a crossover point between 1 to SIZE - 1
	for (i = 0; i < random; i++)
	{
		popnext[2].bit[i] = popnext[0].bit[i];   // child 1 cross over                    // rewrite crossover
		popnext[3].bit[i] = popnext[1].bit[i];   // child 2 cross over                    // using the choosen parents to do crossover
	}

	for (i = random; i < 6; i++)                      // crossing the bits beyond the cross point index
	{
		popnext[2].bit[i] = popnext[1].bit[i];    // child 1 cross over
		popnext[3].bit[i] = popnext[0].bit[i];    // chlid 2 cross over
	}

	for (i = 0; i < 4; i++)
	{
		popnext[i].fit = fitness(popnext[i]);        // 为新个体计算适应度值；
	}

	for (i = 0; i < 4; i++)
	{
		printf("\nCrossOver popnext[%d]=%d%d%d%d%d%d    value=%d    fitness = %d", i, popnext[i].bit[5], popnext[i].bit[4], popnext[i].bit[3], popnext[i].bit[2], popnext[i].bit[1], popnext[i].bit[0], x(popnext[i]), popnext[i].fit);
		// 输出新个体；
	}
	return(0);
}

void *mutation(chrom popnext[SIZE])                //
{

	int random;
	int row, col, value;
	//srand(time(0)); 
	random = rand() % 100;  // 随机产生到之间的数；
	//变异操作也要遵从一定的概率来进行，一般设置为0到0.5之间
	//
	if (random == 5)                              // random==5的概率只有1%，即变异率为，所以是以小概率进行变异！！
	{
		col = rand() % 6;                            // 随机产生要变异的基因位号；
		row = rand() % 4;                            // 随机产生要变异的染色体号；

		if (popnext[row].bit[col] == 0)             // 1变为；
		{
			popnext[row].bit[col] = 1;
		}
		else if (popnext[row].bit[col] == 1)        // 0变为；
		{
			popnext[row].bit[col] = 0;
		}
		popnext[row].fit = y(x(popnext[row]));     // 计算变异后的适应度值；
		value = x(popnext[row]);
		printf("\nMutation occured in popnext[%d] bit[%d]:=%d%d%d%d%d%d    value=%d   fitness=%d", row, col, popnext[row].bit[5], popnext[row].bit[4], popnext[row].bit[3], popnext[row].bit[2], popnext[row].bit[1], popnext[row].bit[0], value, popnext[row].fit);

		// 输出变异后的新个体；
	}

	return(0);
}