#include <iostream>
using namespace std;

class Heapsort{
	public:
	void maxheapify(int a[],int i,int n){
    	int largest = i;
    	int left = 2*i +1;
    	int right = 2*i +2;

    	if(left<n&&a[left]>a[largest]){
        	largest = left;
    	}

    	if(right<n&&a[right]>a[largest]){
        	largest = right;
    	}

    	if(largest!=i){
        	int temp = a[i];
        	a[i] = a[largest];
        	a[largest] = temp;
        	maxheapify(a,largest,n);
    	}
	}

	//FUNCTION TO BUILD MAX HEAP
	void buildmaxheap(int a[],int n){
    	for(int i=n/2 -1;i>=0; i--){
        	maxheapify(a,i,n);
    	}
	}

	//FUNCTION TO PERFORM HEAP SORT
	void heapsort(int a[],int n){
    	buildmaxheap(a,n);
    	for(int i=n-1;i>0;i--){
        	int temp = a[0];
        	a[0] = a[i];
        	a[i] = temp;
        	maxheapify(a,0,i);
    	}
	}

	//FUNCTION TO ACCEPT INPUT
	void accept(){
    	int n;
    	cout<<"Enter number of students : ";
    	cin>>n;
    	int* a = new int[n];
    	for(int i=0; i<n; i++){
        	cout<<"Enter marks for student "<<i+1<<" : ";
        	cin>>a[i];
    	}
    	heapsort(a,n);
    	display(a,n);
	}

	//FUNCTION TO DISPLAY SORTED MARKS
	void display(int a[],int n){
    	cout<<"::::::SORTED MARKS:::::::"<<endl;
    	for(int i=0; i<n; i++){
        	cout<<a[i]<<endl;
    	}
    	cout<<"Minimum marks obtained are : "<<a[0];
    	cout<<"\nMaximum marks obtained are : "<<a[n-1];
	}

};
int main(){
	Heapsort h;
	h.accept();

}



// OUTPUT
// Enter number of students : 5
// Enter marks for student 1 : 46
// Enter marks for student 2 : 33
// Enter marks for student 3 : 89
// Enter marks for student 4 : 4
// Enter marks for student 5 : 65
// ::::::SORTED MARKS:::::::
// 4
// 33
// 46
// 65
// 89
// Minimum marks obtained are : 4
// Maximum marks obtained are : 89

// === Code Execution Successful ===
