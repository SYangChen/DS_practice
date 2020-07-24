/*  資工110 
 *  B063040061 
 *  陳少洋
 *  Dec. 16, 2018
 *  Assignmenet #7 
 *	撰寫五種排序演算法，並根據輸入數字由少到多， 
 *	比較各種排序演算法的效率及時間長短。
 *	檢驗排序法皆運算正確後，時間以表格型式呈現於書面報告中。
 *	A) Insertion Sort
 *	B) Merge Sort
 *	C) Quick Sort
 *	D) C qsort
 *	E) C++ STL sort 
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std ;
fstream fin ;				// file input
fstream fout ;				// file output

int compare( const void *arg1, const void *arg2 ) {
  	return  (*(int *)arg1 - *(int *)arg2) ;
} // compare() // using for c qsort()

class sortTest {
	
	private :
		
		int *unsort ;		// unsorting array
		int length ;		// array length
		
	public :
		
		sortTest() {
			unsort = NULL ;
		} // sort() constructor 
		
		~sortTest() {
			delete unsort ;
			unsort = NULL ;
		} // sort() destructor
		
		int *GetUnsortArray() {
			return unsort ;
		} // GetUnsortArray()
		
		bool LoadFile() {	// }( std::string num ) {
	  		// load in by file
			std::string read = "input.txt";           
      		// read.append( num ) ;
  	  		// read.append( ".txt") ;
  	  		fin.open( read.c_str(), ios::in );	// file open / read 
  	  		if ( !fin )
  	    		return false ;
  	  		else {
        		Read() ;
				// "getline" or "get" here (input)
				fin.close() ;
  	    		return true ;
  	  		} // end else 
  	  
		} // LoadFile()
		
		void Read() {
			fin >> length ;		// get length
			unsort = new int[length+1] ;
			for ( int i = 0 ; i < length ; i++ )
				fin >> unsort[i] ;
		} // Read()
		
		void AInsertionSort( bool write ) {
			int i, j, temp;
			int *aIS = new int[length+1] ;				// initial array
			for ( int k = 0 ; k < length ; k++ )		// set from unsort array
				aIS[k] = unsort[k] ;
			for (i = 1 ; i < length ; i++) {			// one by one
				j = i ;
    			while (j > 0 && aIS[j - 1] > aIS[j]) {	// find the location
    				temp = aIS[j];
					aIS[j] = aIS[j - 1];
					aIS[j - 1] = temp;
					j--;
        		}
	    	}
	    	if ( write )
		    	WriteOut( aIS, "A", "Insertion Sort" ) ; // file output
		} // AInsertionSort()
		
		void Merger( int *arr, int lo, int  mi, int hi ){
    		int *temp = new int[hi-lo+1] ;	//temporary merger array
    		int i = lo, j = mi + 1 ;		//i is for left-hand,j is for right-hand
    		int k = 0 ;						//k is for the temporary array
		    while(i <= mi && j <=hi){
		        if(arr[i] <= arr[j])
		            temp[k++] = arr[i++] ;
		        else
		            temp[k++] = arr[j++] ;
		    }								//rest elements of left-half
		    while(i <= mi)
		        temp[k++] = arr[i++] ;		//rest elements of right-half
		    while(j <= hi)
		        temp[k++] = arr[j++] ;
		    	//copy the mergered temporary array to the original array
		    for(k = 0, i = lo; i <= hi; ++i, ++k)
		        arr[i] = temp[k] ;
		 
		    delete []temp ;
		} // Merger()
		
		void BMergeSort( int *arr, int lo, int hi ){
		    int mid ;
		    if( lo < hi ){								// recursion
		        mid = ( lo+hi ) >> 1 ;					// decomposition
		        BMergeSort( arr, lo, mid ) ;
		        BMergeSort( arr, mid+1, hi ) ;
		        Merger( arr, lo, mid, hi ) ;			// merge
		    }
		} // BMergeSort()
		
		void BMergeSort( bool write ) {					// int arr[], int arr_size){
			int *bMS = new int[length+1] ;				// initial array
			for ( int k = 0 ; k < length ; k++ )		// set by unsort array
				bMS[k] = unsort[k] ;
		    BMergeSort( bMS, 0, length-1 ) ;
		    if ( write )
			    WriteOut( bMS, "B", "Merge Sort" ) ;	// file output
		} // BMergeSort()
		 
		void swap( int *a, int *b ){
    		int temp = *a ;
    		*a = *b ;
    		*b = temp ;
		} // swap()
		 
		int Partition( int *arr, int front, int end ){	// using for quick sort
		    int pivot = arr[end] ;						// find pivot
		    int i = front -1 ;
		    for (int j = front; j < end; j++) {			// set left or right by pivot 
		        if (arr[j] < pivot) {
		            i++ ;
		            swap(&arr[i], &arr[j]) ;
		        }
		    }
		    i++ ;
		    swap(&arr[i], &arr[end]) ;
		    return i ;
		} // Partition()
		
		void QuickSort( int *arr, int front, int end ){
		    if (front < end) {
		        int pivot = Partition(arr, front, end) ;
		        QuickSort(arr, front, pivot - 1) ;
		        QuickSort(arr, pivot + 1, end) ;
		    }
		} // QuickSort()
			
		void CQuickSort( bool write ) {
			int *cQS = new int[length+1] ;				// initial array
			for ( int k = 0 ; k < length ; k++ )		// set by unsort array
				cQS[k] = unsort[k] ;
			QuickSort( cQS, 0, length-1 ) ;
			if ( write )
				WriteOut( cQS, "C", "Quick Sort" ) ;	// file output
		} // CQuickSort()
		
		void Dqsort( bool write ) {
			int *dCQS = new int[length+1] ;				// initial array
			for ( int k = 0 ; k < length ; k++ )		// set by unsort array
				dCQS[k] = unsort[k] ;
			qsort( (void *)dCQS, length, sizeof(int), compare ) ;
			if ( write )
				WriteOut( dCQS, "D", "C qsort()" ) ;	// file output
		} // Dqsort()
		
		void ESTLsort( bool write ) {
			int *eCPPSTLS = new int[length+1] ;			// initial array
			for ( int k = 0 ; k < length ; k++ )		// set by unsort array
				eCPPSTLS[k] = unsort[k] ;
			std::sort( eCPPSTLS, eCPPSTLS+length ) ;
			if ( write )
				WriteOut( eCPPSTLS, "E", "C++ sort()" ) ;	// file output
		} // ESTLsort()

		void PrintSort( int *arr ) {
			for ( int i = 0 ; i < length ; i++ )
				fout << arr[i] << endl ;
			fout << endl ;
		} // PrintSort()
		
		void WriteOut( int *arr, string category, string sortName ) { // std::string num ) {
		
			std::string write ;
			write = "output" ;
	  		write.append( category ) ;
	  		write.append( ".txt" ) ;
	  		fout.open( write.c_str(), ios::out );		// file open / out & append ( ios::out|ios::app )
      		fout << sortName << endl ;
			PrintSort( arr ) ;
			// fout << "Hello!! success" << endl;		// output data in file
      		fout.close() ;
      		cout << "\nFile build" << endl ;
      		
		} // WriteOut()
		
		void ProduceRandom( int num ) {
			int a ;
			length = num ;
			unsort = new int[length+1] ;
			srand(time(NULL)) ;
			for ( int i = 0 ; i < num ; i++ ) {
				a = rand()  ;
				unsort[i] = a ;
			}
			// WriteOut( unsort, "X", "Random Input" ) ;
		} // ProduceRandom()
};

void Report() {
	// unsing in parper report
	bool tle = false ;
	int testingNumbers = 100 ;		// from 100, 500, 1000, 5000......to 10000000
	sortTest a ;
	clock_t aA[11], aB[11], aC[11], aD[11], aE[11], aF[11] ;
	clock_t aASum = 0, aBSum = 0 , aCSum = 0, aDSum = 0, aESum = 0 ;
	for ( int i = 0 ; i < 10 ; i++ ) {
		a.ProduceRandom( testingNumbers ) ;
		
		if ( !tle ) {
			aA[i] = clock() ;
			a.AInsertionSort( false ) ;
			aA[i] = clock()-aA[i] ;
			aASum+=aA[i] ;
			if ( aA[i]/(double)(CLOCKS_PER_SEC) > 300 )
				tle = true ;
		} 
		
		aB[i] = clock() ;		// time start
		a.BMergeSort( false ) ;
		aB[i] = clock()-aB[i] ;	// time stop
		aBSum+=aB[i] ;			// time sum
		
		aC[i] = clock() ;
		a.CQuickSort( false ) ;
		aC[i] = clock()-aC[i] ;
		aCSum+=aC[i] ;
		
		aD[i] = clock() ;
		a.Dqsort( false ) ;
		aD[i] = clock()-aD[i] ;
		aDSum+=aD[i] ;
		
		aE[i] = clock() ;
		a.ESTLsort( false ) ;
		aE[i] = clock()-aE[i] ;
		aESum+=aE[i] ;
	}
	if ( tle ) cout << "A) Insertion\t: "<< "tle" << endl ;
	else cout << "A) Insertion\t: "<< aASum/10/(double)(CLOCKS_PER_SEC) << endl ;
	cout << "B) Merge Sort\t: "<< aBSum/10/(double)(CLOCKS_PER_SEC) << endl ;
	cout << "C) Quick Sort\t: "<< aCSum/10/(double)(CLOCKS_PER_SEC) << endl ;
	cout << "D) C qsort\t: "<< aDSum/10/(double)(CLOCKS_PER_SEC) << endl ;
	cout << "E) C++ STL sort\t: "<< aESum/10/(double)(CLOCKS_PER_SEC) << endl ;
} // Report()

int main() {
	
	sortTest test ;
	if ( !test.LoadFile() ) {
		cout << "fail to load file" << endl ;
		return 0 ;
	}
	
	test.AInsertionSort( true ) ;
	test.BMergeSort( true ) ;
	test.CQuickSort( true ) ;
	test.Dqsort( true ) ;
	test.ESTLsort( true ) ;
	
	// Report() ;
}
