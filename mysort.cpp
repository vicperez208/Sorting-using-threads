// optimizing bubble sort using pThreads and then merging sub arrays to one big array to an ouput file.  
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <pthread.h>

using namespace std;
struct threadNumArgs {
	int* numsArray;
	int startingIndex;
	int endingIndex;
};

void mergeSuperSections(int* left, int leftSize, int* right, int rightSize, int* result) {
	int i = 0, j = 0, k = 0;
	while (i < leftSize && j < rightSize) {
		if (left[i] < right[j]) {
			result[k++] = left[i++];
		}
		else {
			result[k++] = right[j++];
		}
	}
	while (i < leftSize) {
		result[k++] = left[i++];
	}
	while (j < rightSize) {
		result[k++] = right[j++];
	}
}

void* bubbleSortThread(void* arg) {
	threadNumArgs* args = (threadNumArgs*)arg;
	int* numsArray = args->numsArray;
	int startingIndex = args->startingIndex;
	int endingIndex = args->endingIndex;

	for (int i = startingIndex; i < endingIndex - 1; i++) {
		for (int j = startingIndex; j < endingIndex - 1; j++) {
			if (numsArray[j] > numsArray[j + 1]) {
				int temp = numsArray[j];
				numsArray[j] = numsArray[j + 1];
				numsArray[j + 1] = temp;
			}
		}
	}

	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " input_file output_file" << endl;
		return 1;
	}

	ifstream in(argv[1]);
	if (!in.is_open()) {
		cout << "Couldn't open input file" << endl;
		return 1;
	}
	const int maxNumbers = 1000000;
	int numbers[maxNumbers];
	int count = 0;
	int num;
	while (in >> num) {
		if (count >= maxNumbers) {
			cout << "Error: input file contains too many numbers" << endl;
			return 1;
		}
		numbers[count++] = num;
	}

	in.close();

	const int superSectionSize = 125000;
	const int superSectionNums = 8;
	pthread_t threads[superSectionNums];
	threadNumArgs args[superSectionNums];
	for (int i = 0; i < superSectionNums; i++) {
		args[i].numsArray = numbers;
		args[i].startingIndex = i * superSectionSize;
		args[i].endingIndex = (i + 1) * superSectionSize;
		pthread_create(&threads[i], NULL, bubbleSortThread, (void*)&args[i]);
	}
	for (int i = 0; i < superSectionNums; i++) {
		pthread_join(threads[i], NULL);
	}

	int tempArray[maxNumbers];
	mergeSuperSections(numbers, superSectionSize, numbers + superSectionSize, superSectionSize, tempArray);
	mergeSuperSections(tempArray, superSectionSize * 2, numbers + (superSectionSize * 2), superSectionSize, numbers);
	mergeSuperSections(numbers, superSectionSize * 3, numbers + (superSectionSize * 3), superSectionSize, tempArray);
	mergeSuperSections(tempArray, superSectionSize * 4, numbers + (superSectionSize * 4), superSectionSize, numbers);
	mergeSuperSections(numbers, superSectionSize * 5, numbers + (superSectionSize * 5), superSectionSize, tempArray);
	mergeSuperSections(tempArray, superSectionSize * 6, numbers + (superSectionSize * 6), superSectionSize, numbers);
	mergeSuperSections(numbers, superSectionSize * 7, numbers + (superSectionSize * 7), maxNumbers - (superSectionSize * 7), tempArray);
	mergeSuperSections(tempArray, superSectionSize * 7, numbers + (superSectionSize * 7), maxNumbers - (superSectionSize * 7), numbers);
	ofstream out(argv[2]);
	if (!out.is_open()) {
		cout << "Couldn't open output file" << endl;
		return 1;
	}

	for (int i = 0; i < count; i++) {
		out << numbers[i] << endl;
	}

	out.close();

	return 0;
}






