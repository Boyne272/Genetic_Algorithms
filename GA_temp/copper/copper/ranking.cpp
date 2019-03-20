#include <iostream>
#include <ctime>
#include <cstdlib> // generate randem number

#define num_units 10
#define N 10

using namespace std;

typedef struct
{
int circuit[2 * num_units + 1];
double fitness_value;
} item;

void swap(item list[], int first, int second)
{
	item temp;

	temp = list[first];
	list[first] = list[second];
	list[second] = temp;
}

int partition(item list[], int left, int right) 
{
	double pivot;
	int storeIndex = left;
	int pivotIndex;
	pivotIndex = (left + right) / 2;

	pivot = list[pivotIndex].fitness_value;
	swap(list, pivotIndex, right);

	storeIndex = left;
	for (int index = left; index <= right - 1; index++)
		if (list[index].fitness_value > pivot) {
			swap(list, storeIndex, index);
			storeIndex++;
		}
	swap(list, right, storeIndex);
	return storeIndex;
}


void recursionQuick(item list[], int first, int last) {
	int pivotLocation;

	if (first < last) {
		pivotLocation = partition(list, first, last);
		recursionQuick(list, first, pivotLocation - 1);
		recursionQuick(list, pivotLocation + 1, last);
	}
}

void quickSort(item list[], int length) {
	recursionQuick(list, 0, length - 1);
}

int main()
{
	item item_array[N];
	int temp_array[2 * num_units + 1];
	int temp_fitness;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2 * num_units + 1; j++)
		{
			item_array[i].circuit[j] = (rand() + time(0)) % 10;
		}
		item_array[i].fitness_value = 0.5*item_array[i].circuit[0]+ 0.2*item_array[i].circuit[1];
	}

	cout << "The struct list before quick sorting: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2 * num_units + 1; j++)
		{
			cout << item_array[i].circuit[j] << " ";
		}
		cout << endl << item_array[i].fitness_value << endl << endl;
	}

	quickSort(item_array, N);

	cout << "The struct list after quick sorting: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2 * num_units + 1; j++)
		{
			cout << item_array[i].circuit[j]<<" ";
		}
		cout << endl<<item_array[i].fitness_value << endl<<endl;
	}
	system("pause");
	return 1;
}