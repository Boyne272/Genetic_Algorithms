#include<iostream>
#include<time.h>
#include "GA_Header.h"

#define N 10
#define NUM 100

using namespace std;

struct data
{
	double fitness = 0;
	int data[2 * N + 1];
};

struct data *list = new struct data[NUM];

void fitness(struct data *item)
{
	item->fitness = rand() % (15);
}

void swap(struct data *list, int first, int second)
{
	struct data temp;

	temp = list[first];
	list[first] = list[second];
	list[second] = temp;
}

int partition(struct data *list, int left, int right)
{
	double pivot;
	int storeIndex = left;
	int pivotIndex;
	pivotIndex = (left + right) / 2;

	pivot = list[pivotIndex].fitness;
	swap(list, pivotIndex, right);

	storeIndex = left;
	for (int index = left; index <= right - 1; index++)
		if (list[index].fitness > pivot) {
			swap(list, storeIndex, index);
			storeIndex++;
		}
	swap(list, right, storeIndex);
	return storeIndex;
}

void recursionQuick(struct data *list, int first, int last) {
	int pivotLocation;

	if (first < last) {
		pivotLocation = partition(list, first, last);
		recursionQuick(list, first, pivotLocation - 1);
		recursionQuick(list, pivotLocation + 1, last);
	}
}

void quickSort(struct data *list) {
	recursionQuick(list, 0, N - 1);
}

void creat_n_vaild_vector()
{
	srand(time(NULL));
	
	for (int i = 0; i < NUM; i++)
	{
		for (int j = 0; j < 2 * N + 1; j++)
		{
			list[i].data[j] = rand() % (2 * N + 1);
		}
		fitness(&list[i]);
	}
}

void ranking()
{

}

void reproduction()
{
	double max=10, min=1;
	
	double sum;
	for (int i = 0; i < NUM; i++)
	{
		list[i].fitness += min;
		sum += list[i].fitness;
	}
	rand()%sum
}

void crossover()
{

}

bool Termination()
{

	return true;
}

int t_main()
{
	double max, min;
	creat_n_vaild_vector();

	quickSort(list);

	for (int i = 0; i < NUM; i++)
	{
		cout << list[i].fitness << endl;
	}

	ranking();

	system("pause");
}