#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void readfile(int* arr);
void swap(int* arr, int from, int to);
int compareThree(int l, int r, int mid);
int fildpivot(int* arr, int l, int r);
void showarray(int *arr, int l, int r);
int partitionFuc(int* arr, int l, int r, int pivot);
void quicksort(int* arr, int l, int r, int *counter);


void readfile(int *arr){
    ifstream file("QuickSort.txt");
    if(file.is_open())
    {
        for(int i = 0; i < 10000; ++i)
        {
            file >> arr[i];
        }
    }
}

void swap(int *arr, int from, int to){
    int temp = arr[from];
    arr[from] = arr[to];
    arr[to] = temp;
}

int compareThree(int *arr, int l, int r, int mid_index){
	// cout << "l = " << arr[l] << ", r = " << arr[r] << ", mid = " << arr[mid_index] << endl;
	int middle = max(min(arr[l], arr[r]), min(max(arr[l], arr[r]), arr[mid_index]));
	// cout << "Median value = " << middle << endl;
	if(middle == arr[l]) return l;
	if(middle == arr[r]) return r;
	if(middle == arr[mid_index]) return mid_index;
}

int findpivot(int *arr, int l, int r){
    //Pattern1: Use the left edge
    // int pivot = l;

    // Pattern2: Use the right edge
    // int pivot = r;

    //Pattern3: Use the Median of three
    int mid_index = (r + l)/2;
    // cout << "l_index=" << l << " r_index=" << r << " mid_index=" << mid_index << endl;
    int pivot = compareThree(arr, l, r, mid_index);
    
    return pivot;
}

int partitionFuc(int *arr, int l, int r, int pivot){
    swap(arr, l, pivot);
    int p = arr[l];
    int i = l+1;
    for (int j=l+1; j < r+1; j++){
        if (arr[j] > p) {
            //Do nothing
            // cout << "DO nothing" << endl;
        }
        else if (arr[j] < p){
            // cout<< "Swap it" << endl;
            swap(arr, i, j);
            i++;
            // cout << "i=" << i << endl;
        }
    }
    swap(arr, l, i-1);
    return i-1;
}

void showarray(int *arr, int l, int r){
	for(int i=l; i<r+1; i++){
		cout << "Show input array: " << arr[i] << endl;
	}
}

void quicksort(int *arr, int l, int r, int *counter){
    //Base case
    //When the input is len = 1, return the value itself
    if (r - l <= 0){
        // cout << "Base case: " << arr[l] << endl;
    }
    else{
        int pivot = findpivot(arr, l, r);
        int partition = partitionFuc(arr, l, r, pivot);
        *counter += r-l;
        // cout << "count=" << r-l << endl;
        // showarray(arr, l, partition - 1);
        quicksort(arr, l, partition - 1, counter);
        // showarray(arr, partition + 1, r);
        quicksort(arr, partition + 1, r, counter);
    }
}

int main(){
    int arr[10000];
    readfile(arr);

    // int arr[20] = {2, 20, 1, 15, 3, 11, 13, 6, 16, 10, 19, 5, 4, 9, 8, 14, 18, 17, 7, 12};
    // int arr[2] = {2,1};

    //Quicksort initialization
    int left(0);
    int right = sizeof(arr) / sizeof(arr[0]) - 1;

    //Define counter pointer
    int count_value(0);
    int *counter = &count_value;

    //Call quicksort
    // showarray(arr, left, right);
    quicksort(arr, left, right, counter);

    // cout << "No. of comparason= " << *counter << endl;
    showarray(arr, left, right);


    return 0;
}