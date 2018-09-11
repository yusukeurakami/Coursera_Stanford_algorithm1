#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void readTXT(int* arr){
    ifstream file("IntegerArray.txt");
    if(file.is_open())
    {
        for(int i = 0; i < 100000; ++i)
        {
            file >> arr[i];
        }
    }
}

long long merge(int* arr, int* temp, int begin, int mid, int end){
  long long inv_count = 0;

  int i = begin; /* i is index for left subarray*/
  int j = mid;  /* j is index for right subarray*/
  int k = begin; /* k is index for resultant merged subarray*/
  while ((i <= mid - 1) && (j <= end))
  {
    if (arr[i] <= arr[j])
    {
      temp[k++] = arr[i++];
    }
    else
    {
      temp[k++] = arr[j++];

     /*this is tricky -- see above explanation/diagram for merge()*/
      inv_count = inv_count + (mid - i);
    }
  }
  return inv_count;
 }

long long inverseCount(int* arr, int* temp, int begin, int end){
  
  long long count = 0;

  if (begin < end){
  	int mid = (begin+end)/2;
  	count = inverseCount(arr, temp, begin, mid);
  	count += inverseCount(arr, temp, mid+1, end);
  	count += merge(arr, temp, begin, mid, end);
  	return count;
  }
  return count; //Base case. When the begin == end (when the input is single element.) return zero.
}

int main(){
  //Make the vector for storaging the value
  int arr[100000];
  int temp[100000];
  //Read the text file and make the vector contain all the values
  readTXT(arr);
  //Run the function for counting inverse in the vector
  const int size = sizeof(arr) / sizeof(arr[0]);
  long long n_inv = inverseCount(arr, temp, 0, size);
  // Print the result
  cout << "Number of inverse: " << n_inv << endl;
  //Check the size

  cout << "size:" << size << " arr check: " << arr[99999] << endl;
  return 0;
}
