/*****************************************************************************
* Antonio Santos
* Spring 2017 - CSCI 271
* Program 4 - Due 3/27/2017
*****************************************************************************/
#include <time.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

void insertionSort(string*, int); //insertion sort O(n^2)
void mergeSort(string*,string*,int,int); //merge sort helper O(nlog(n))
void swap(string*, int, int); //swap
void display(string*, int); //displays array O(n)

/*arg contains the amount of elements in argc.
/argc contains useful info:
  /argc[0] == execution file namespace
  /argc[1] == in our case, it is the input number */
int main(int arg, char* argc[]){ //start of main
  const int size = atoi(argc[1]); //gets size of input (its in argc[1] in char
                                  //form originally)
  string* data = new string[size]; /*array that uses space from the heap
                                   /rather than from static memory. Helpful
                                   /for extremely large data */
  string* hold = new string[size];
  clock_t t; //used to calculate time of just the algorithm rather than whole
             //program
  ifstream file;
  file.open("sort.dat");
  int acounter = 0; //array counter
  int ccounter = 0; //c-string counter
  string temp;
  int ans;

  //go until we hit end of file, or until we reach end of desired input size
  while((acounter != size) && (!file.eof())){
    ccounter = 0;

    //do not include spaces, new lines, and a string more than 30 chars
    while((file.get() != ' ') && (file.get() != '\n') && (ccounter != 30)){
      temp.push_back(file.get());
      ccounter++;
    }
    data[acounter] = temp; //put complete c-string in array
    acounter++;
    temp.erase(temp.begin(), temp.end()); //delete temporary c-string
  }

  cout << "-----MERGE SORT-----" << endl;
  //display(data, size); //uncomment to see values before sort
  t = clock();
  mergeSort(data, hold, 0, size - 1);
  t = clock() - t;
  cout << endl;
  //display(data, size); //uncomment to see values after sort
  cout << "Execution time = " << ((float) t)/CLOCKS_PER_SEC;

  return 0;
} //end of main

/*****************************************************************************
* Function: display
* O(n)
* displays the contents of array
*****************************************************************************/
void display(string *arg, int max){
  for(int i = 0; i < max; i++){
    cout << arg[i] << endl;
  }
}

/*****************************************************************************
* Function: swap
* O(3)
* swaps contents of 2 positions in array
*****************************************************************************/
void swap(string *arg, int pos1, int pos2){
  string temp = arg[pos1];
  arg[pos1] = arg[pos2];
  arg[pos2] = temp;
}

/*****************************************************************************
* Function: insertionSort
* O(n^2)
* goes through array (O(n)) and performs a swap where needed (O(n)).
*****************************************************************************/
void insertionSort(string *arg, int max){
  for(int i = 1; i < max; i++) //goes through array
    //if value is hit where the array @ i is < the previous position, then we
    //want to swap those 2 positions.
    for(int j = i; ((j > 0) && (arg[j] < arg[j - 1])); j--)
      //once the first swap is done, we know that we are in order at the
      //current position. now we keep going up/left (however you visualize
      //an array) to make sure the rest of the previous values are in order
      swap(arg, j, j-1);
}

/*****************************************************************************
* Function: mergeSort
* O(nlog(n))
* partitions array into multiple subtrees and keep doing it until the subtrees
* are at 1 elemnt (this takes O(logn)). keeps doing it for every element (O(n))
*****************************************************************************/
void mergeSort(string *arg, string *temp, int l, int r){
  if((r - l) <= 2000){ //small partition is better sorted with insertion sort
   insertionSort(arg, r-l+1);
   return;
  }
  int i, j, k, mid = (l + r)/2;
  mergeSort(arg, temp, l, mid);//partitions left side of array
  mergeSort(arg, temp, mid + 1, r);//partitions right side of array

  //copies subarray into temp
  for(i = mid; i >= l; i--)
    temp[i] = arg[i];
  for(j = 1; j <= r-mid; j++)
    temp[r = j + 1] = arg[j + mid];

  for(i = l, j = r, k = l; k <= r; k++)
    if(temp[i] < temp[j])
      arg[k] = temp[i++];
    else
      arg[k] = temp[j--];
}
