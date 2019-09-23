/*
 * ordenacao.cpp
 *
 *  Created on: 20 de out de 2017
 *      Author: ramide
 */

#include <iostream>
#include <stdlib.h>
#include <chrono>

using namespace std;

int validate(int * data, int size) {
	for (int i = 0; i < size - 1; i++) {
		if (data[i] > data[i + 1]) return 0;
	}
	return 1;
}

void print(int * data, int size) {
	for (int i = 0; i < size; i++) {
		cout << data[i] << " ";
	}
	cout << endl;
}

int * clone(int * array, int size) {
	int * copy = new int[size];
	for (int i = 0; i < size; i++) { copy[i] = array[i]; }
	return copy;
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void noopsort(int * array, int size) {
	// no-op
}


void bubblesort(int * array, int size) {
	//TO DO
	while(!validate(array, size)){
		for(int i = 0; i < size -1;i++){
			if(array[i] > array[i +1]){
				swap(array[i], array[i + 1]);
			}
		}
	}
}


void selectionsort(int * array, int size) {
	//TO DO
	int minimo;
	for(int i = 0; i < size; i++){
		minimo = i;
		for(int j = i + 1; j < size; j++){
			if(array[minimo] > array[j]){
				minimo = j;
			}
		}
		swap(array[minimo], array[i]);
	}
}


void insertionsort(int * array, int size) {
	//TO DO
}

void merge(int * target, int * buffer, int start, int mid, int finish) {
	//TO DO
	int init = start;
	int meio = mid;
	int fim = finish;
	for(int i = start; i <= fim; i++){
		if(init <= mid - 1&& meio <= fim){
			if(buffer[init] <= buffer[meio]){
				target[i] = buffer[init++];
			}
			else{
				target[i] = buffer[meio++];
			}
		}
		else if(init <= mid - 1){
			target[i] = buffer[init++];
		}
		else if(meio <= fim){
			target[i] = buffer[meio++];
		}
	}
}

void mergesort(int * target, int * buffer, int start, int finish) {
	if (start >= finish) return;

	int mid = (start + finish)/2;

	mergesort(buffer, target, start, mid);
	mergesort(buffer, target, mid + 1, finish);

	merge(target, buffer, start, mid + 1, finish);
}

void mergesort(int * array, int size) {
	int * copy = clone(array, size);
	mergesort(array, copy, 0, size - 1);
	delete [] copy;
}

int partition(int * array, int start, int finish) {
	//TO DO
	int pivo = array[finish];
	int p = start -1;
	for(int i = start; i <= finish; i++){
		if(array[i] <= pivo){
			p++;
			swap(array[i], array[p]);
		}
	}
	return p;
}

void quicksort(int * array, int start, int finish) {
	if (finish <= start) return;
	int pivot = partition(array, start, finish);
	quicksort(array, start, pivot - 1);
	quicksort(array, pivot + 1, finish);
}

void quicksort(int * array, int size) {
	quicksort(array, 0, size - 1);
}



void show(int * array, int size, const char * name, void function(int *, int), int printFlag) {
	int * copy = clone(array, size);
	auto start = std::chrono::high_resolution_clock::now();

	function(copy, size);

	auto finish = std::chrono::high_resolution_clock::now();
	long elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / 1000;

	int valid = validate(copy, size);
	cout << name << ": " << (valid?"ok":"erro") << " (tempo[us] = " << elapsed << ") ";

	if (printFlag) print(copy, size);
	delete [] copy;
}

int main() {
	int size = 10;
	int print = 1;

	int * array = new int[size];

	for (int i = 0; i < size; i++) {
		array[i] = rand() % size;
	}

	show(array, size, "NoOpSort     ", noopsort, print);
	show(array, size, "BubbleSort   ", bubblesort, print);
	show(array, size, "SelectionSort", selectionsort, print);
	show(array, size, "InsertionSort", insertionsort, print);
	show(array, size, "MergeSort    ", mergesort, print);
	show(array, size, "QuickSort    ", quicksort, print);

	delete [] array;
}





