//  Author : Britain Mackenzie
//  Due Date : 11/07/18
//
//  This program uses random number generation on a user defined sized array
//  that is then sorted with mulitple different sort algorithms, displaying
//  speed of execution and number of comparisons, or calls.

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <ctime>
using namespace std;

void displayIntro();                            //Displays intro dialogue
bool getInt(int &);                             //Gets user input array size
int fillArray(int, int []);                     //fills array with random numbers
void dispArray(int, const int []);              //displays up to first 20 elements
void copyArray(int, const int [], int[]);       //makes copy of original array
int sequSearch(int, int, int &, const int []);  //sequentially searches for random number
void bubble(int, int &, int []);                //bubble sorts copy of array
void insertSort(int, int &, int[]);             //insert sorts copy of array
void quickFirst(int, int, int &, int[]);        //quick sort with first element pivot
void quickMid(int, int, int &, int[]);          //quick sort with next to middle element pivot
void quickLast(int, int, int &, int[]);         //quick sort with last element pivot

int main() {
    int *nums, *copy;                           //pointers for dynamic array allocation
    int size, rando;                            //array size, and number for search
    int temp, total;                            //holds 1 if number found, and total counts
    double start, end = 0.0;                    //to store CPU clock
    
    displayIntro();
    if(getInt(size))
    {
        nums = new int [size];
        copy = new int [size];
        rando = fillArray(size, nums);
        copyArray(size, nums, copy);
        dispArray(size, nums);
        
        cout<<"Sequential Search\n\nSearching for "<<rando<<endl<<endl;
        start = clock();
        temp = sequSearch(size, rando, total, nums);
        end = clock();
        if(temp == 0)
            cout<<rando<<" Was Not found.\n";
        else
            cout<<rando<<" Was found.\n";
        cout<<"Start Time\t: "<<start<<endl<<"End Time\t: "<<end<<endl;
        cout<<"Actual CPU Clock time : "<<end-start<<endl;
        cout<<"Total Number of Comparisons : "<<total<<"\n\n\n\n";
        
        total = 0;
        start = clock();
        bubble(size, total, copy);
        end = clock();
        cout<<"Bubble Sort : \n\n";
        cout<<"Start Time\t: "<<start<<endl<<"End Time\t: "<<end<<endl;
        cout<<"Actual CPU Clock time : "<<end-start<<endl;
        cout<<"Total Number of Swaps : "<<total<<"\n\n\n\n";
        
        total = 0;
        copyArray(size, nums, copy);
        start = clock();
        insertSort(size, total, copy);
        end = clock();
        cout<<"Insertion Sort : \n\n";
        cout<<"Start Time\t: "<<start<<endl<<"End Time\t: "<<end<<endl;
        cout<<"Actual CPU Clock time : "<<end-start<<endl;
        cout<<"Total Number of Comparisons : "<<total<<"\n\n\n\n";
       
        total = 0;
        copyArray(size, nums, copy);
        start = clock();
        quickMid(0, size-1, total, copy);
        end =clock();
        cout<<"Quick Sort - Next to the middle element as a pivot : \n\n";
        cout<<"Start Time\t: "<<start<<endl<<"End Time\t: "<<end<<endl;
        cout<<"Actual CPU Clock time : "<<end-start<<endl;
        cout<<"Total Number of Recursive Calls : "<<total<<"\n\n\n\n";
        
        total = 0;
        copyArray(size, nums, copy);
        start = clock();
        quickFirst(0, size-1, total, copy);
        end = clock();
        cout<<"Quick Sort - First element as a pivot :\n\n";
        cout<<"Start Time\t: "<<start<<endl<<"End Time\t: "<<end<<endl;
        cout<<"Actual CPU Clock time : "<<end-start<<endl;
        cout<<"Total Number of Recursive Calls : "<<total<<"\n\n\n\n";
        
        total = 0;
        copyArray(size, nums, copy);
        start = clock();
        quickLast(0, size-1, total, copy);
        end = clock();
        cout<<"Quick Sort - last element as a pivot :\n\n";
        cout<<"Start Time\t: "<<start<<endl<<"End Time\t: "<<end<<endl;
        cout<<"Actual CPU Clock time : "<<end-start<<endl;
        cout<<"Total Number of Recursive Calls : "<<total<<"\n\n\n\n";
    }
    else
        cout<<"***  Error - Invalid input - Size must be >0 ***\n\n\n";
    cout<<"Benchmark Algorithm Implemented by Britain Mackenzie\n11 / 7 / 2018\n\n";
    return 0;
}
//Displays intro dialogue
void displayIntro(){
    cout<<"Searching / Sorting Benchmark\n\n\n";
    cout<<"Using a random number generator, we are creating an array of n\n";
    cout<<"elements of type integer then preforming the following   :\n\n";
    cout<<"\t1. Displaying the first 20 numbers.\n\n";
    cout<<"\t2. Using recursion, Searching for an element in the array using\n";
    cout<<"\t   sequential search and at the end displaying number of comparisons\n";
    cout<<"\t   it makes.\n\n";
    cout<<"\t3. Sort the original array using bubble Sort  and at the end display\n";
    cout<<"\t   the number of swaps it makes.\n\n";
    cout<<"\t4. Sorting the array using insertion   Sort    and at the end\n";
    cout<<"\t   displaying  the number of comparisons it makes.\n\n";
    cout<<"\t5. Sorting the array using Quick Sort   and at the end displaying\n";
    cout<<"\t   the number of recusion calls it makes. Using the next to the\n";
    cout<<"\t   middle value as a pivot value.\n\n";
    cout<<"\t6. Sorting the same array using Quick Sort   and at the end\n";
    cout<<"\t   displaying the number of recusion calls it makes. Using the\n";
    cout<<"\t   first valu as a pivot value.\n\n";
    cout<<"\t7. Sorting the same arrray using Quick Sort and at the end\n";
    cout<<"\t   displaying the number of recursion calls it makes. Using the\n";
    cout<<"\t   last value as a pivot value.\n\n";
    cout<<"\t8. For each of the preceding steps ( 2 thru 5 ), calculating and\n";
    cout<<"\t   printing the CPU time before each step starts and after each\n";
    cout<<"\t   completed step the calculating actual CPU time for the\n";
    cout<<"\t   completion of each step.\n\n\n";
    cout<<"Enter the size of the array :  ";
}
//Returns true if user input is positive int, false if not int or positive
bool getInt(int &size){
    bool valid = true;          //holds true if positive int
    if(isalpha(cin.peek()))
        valid = false;
    else if(cin.fail())
        valid = false;
    else{
        cin>>size;
        if(cin.peek()=='.'){
            valid = false;
        }
        if(size<0)
            valid = false;
    }
        return valid;
}
//Fills array with randomly generated numbers between 1-1000, returns int for sequential search
int fillArray(int size, int nums[]){
    srand(time(NULL));
    for(int x = 0; x<size; x++){
        nums[x]=rand() % 1000;
    }
    return (rand() % 1000);
}
//Displays array up to 20th element
void dispArray(int size, const int nums[]){
    cout<<"\n\nArray elements are: ";
    if(size>20){
        for(int x =0; x<20; x++){
            cout<<nums[x]<<" ";
        }
    }
    else{
        for(int x =0; x<size; x++){
            cout<<nums[x]<<" ";
        }
    }
    cout<<endl<<endl;
}
//creates copy of original array for use in sorting algorithms
void copyArray(int size, const int nums[], int copy []){
    for(int i = 0; i<size; i++){
        copy[i]=nums[i];
    }
}
//searches for a randomly generated number recursively
int sequSearch(int size, int rando, int &total, const int nums[]){
    if(size==0)
    {
        return 0;
    }
    total++;
    if(rando == nums[size-1])
    {
        return 1;
    }
    total++;
    return sequSearch(size-1, rando, total, nums);
}
//sorts array using bubble sort algorithm
void bubble(int size, int &total, int nums[]){
    int temp;       //holds temp for element swap
    bool swapped;   //true if elements swapped
    for(int i =0; i<size; i++){
        swapped =false;
        for( int j =0; j<size-i-1;j++){
            if(nums[j]>nums[j+1]){
                temp=nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
                total++;
                swapped=true;
            }
        }
        if(swapped == false)
            return;
    }
}
//sorts array using insert sort algorithm
void insertSort(int size, int &total, int nums[]){
    int temp, j;        //holds temp for swapping, and iterator
    for(int i = 1; i<size; i++){
        temp = nums[i];
        j = i-1;
        while(j>=0 && nums[j]>temp){
            nums[j+1] = nums[j];
            j = j-1;
            total++;
        }
        nums[j+1] = temp;
    }
}
//sorts array using quick sort with first element as pivot
void quickFirst(int left, int right, int &total, int nums[]){
    int pivot = nums[left];             //sets pivot to left element
    int i= left, j = right, temp = 0;   //iterators and temp for swapping
    while(i<=j){
        while(nums[i]<pivot)
            i++;
        while(nums[j]>pivot)
            j--;
        if(i<=j){
            temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
            i++;
            j--;
        }
    }
    if(left < j)
    {
        total++;
        quickFirst(left, j, total, nums);
    }
    if(right > i){
        total++;
        quickFirst(i, right, total, nums);
    }
}
//sorts array using quick sort with next to middle element as pivot
void quickMid(int left, int right, int &total, int nums[]){
    int pivot = nums[(left+right)/2];   //sets pivot to next to middle element
    int i= left, j = right, temp =0;    //iterators and temp for swapping
    while(i<=j){
        while(nums[i]<pivot)
            i++;
        while(nums[j]>pivot)
            j--;
        if(i<=j){
            temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
            i++;
            j--;
        }
    }
    if(left < j){
        total++;
        quickMid(left, j, total, nums);
    }
    if(right > i){
        total++;
        quickMid(i, right, total, nums);
    }
}
//sorts array using quick sort with last element as pivot
void quickLast(int left, int right, int &total, int nums[]){
    int pivot = nums[right];            //sets pivot to last element
    int i= left, j = right, temp =0;    //iterators and temp for swapping
    while(i<=j){
        while(nums[i]<pivot)
            i++;
        while(nums[j]>pivot)
            j--;
        if(i<=j){
            temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
            i++;
            j--;
        }
    }
    if(left < j){
        total++;
        quickLast(left, j, total, nums);
    }
    if(right > i){
        total++;
        quickLast(i, right, total, nums);
    }
}
