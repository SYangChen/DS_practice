/*  資訊二甲 
 *  陳少洋
 *  10527130 
 */ 

// #include <cstdlib>
// #include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>

using namespace std;
int gSequence ;
int gFound ;

// ****************Using Function******************
void Combination( int pickNum, int target, int result[], int index ) ;
void Permutation( int start, int targetNum, int result[], int index ) ;
void Duplication( int result[], int index ) ;
void PrintCurrent( int result[], int index ) ;
void IntToIntArray( int number, int result[], int index ) ;
// ****************Using Function******************

int main() {
  
  int command ;
  int testNum ;         
  cout << "**** Recursive Generator ****\n\
* 0. Quit                        *\n\
* 1. Combination generation      *\n\
* 2. Permutation generation      *\n\
-----------------------------__---\n\
Input a command(0, 1, 2): " ;
  cin >> command ;
  while ( command != 0 ) {
  	gSequence = 1;
  	gFound = true ;
    if ( command == 1 ) {
      cout << "Input a number : " ;
  	  cin >> testNum ;
  	  if ( testNum > 10 || testNum < 1 )
        cout << "Please enter the range between 1-10." << endl ;
      else {
  	    int result[testNum-1] ;
  	    clock_t t = clock() ;                                    // time start
  	    Combination( 10, testNum, result, 0 ) ;
  	    t = clock()-t ;                                          // time stop
  	    cout << "Cost : " << t << " ms" << endl ;
  	  } // end else
  	  // insert the function of combination
    } // end if
    else if ( command == 2 ) {
      cout << "Input a number :" ;
      cin >> testNum ;
      if ( testNum > 10 || testNum < 1 )
        cout << "Please enter the range between 1-10." << endl ;
      else {
        int result[testNum-1] ;
        int powerOfTen = 1 ;
        int per = 1 ;
        for ( int i = testNum ; i != 0 ; i-- )                         // 10^n power
          powerOfTen = powerOfTen*10 ;
        if ( testNum == 10 )
          per = 123456789 ;
        clock_t t = clock() ;                                          // time start 
        Permutation( per, powerOfTen, result, testNum-1 ) ;     
        t = clock()-t ;                                                // time stop
	    cout << "Cost : " << t << " ms" << endl ;
      } // end else
      // insert the function of permutation
	} // end else if
	else 
	  cout << "Couldn't find command, please try again." << endl ;
	cout << "**** Recursive Generator ****\n\
* 0. Quit                        *\n\
* 1. Combination generation      *\n\
* 2. Permutation generation      *\n\
-----------------------------__---\n\
Input a command(0, 1, 2): " ;
    cin >> command ;
  } // end while  
  
  cout << "Thanks for visiting!" ; 
} // main()

// ********************************************************************

void Combination( int pickNum, int target, int result[], int index ) {
  // using recursion to find the combination generation
  // expand and increase in the meantime
  if ( index == target ) {                                          // if found the number than print it out
     PrintCurrent( result, index-1 ) ;
    return ;
  } // end if
  for ( int i = (10-pickNum) ; i < 10 ; i++ ) {                     // from 0 to 9 for the level
    result[index] = i ;
    Combination( 10-(i+1), target, result, index+1 ) ;              // from i to 9 for expand
  } // end for
   
} // Combination()

// ********************************************************************

void Permutation( int start, int targetNum, int result[], int index ) {
  // call this recursion for plus one to examine whether the number is duplicative.
  // if it has not found the same number and print it out.
  if ( !gFound )
    PrintCurrent( result, index ) ;
  if ( start == targetNum )
    return ;
  else {
  	gFound = false ;
  	IntToIntArray( start, result, index ) ;                           // integer convert to array
    Duplication( result, index ) ;
    Permutation( start+1, targetNum, result, index ) ;
  } // end else
  
} // Permutation()

// ********************************************************************

void Duplication( int result[], int index ) {
  // using recursion to find the same number.
  // if it has found than gFound set as true.
  if ( gFound )
    return ;
  else if ( index == 0 )
    return ;
  else {
  	for ( int i = index-1 ; i >= 0 ; i-- ) {
  	  if ( result[index] == result[i] ) {
  	    gFound = true ;
      } // end if
	} // end for
  	  
    Duplication( result, index-1 ) ;
  } // end else
} // SameNotFound()

// ********************************************************************

void PrintCurrent( int result[], int index ) {
  // print out with sequence counting.
  cout << "[ " << gSequence << " ]  " ;
  for ( int i = 0 ; i <= index ; i++ )
    cout << result[i] << " ";
  cout << endl ;
  gSequence++ ;
  
} // PrintCurrent()

// ********************************************************************

void IntToIntArray( int number, int result[], int index ) {
  // integer convert to int array
  for ( int i = index ; i >= 0 ; i-- ) {
  	if ( number == 0 )                  // fill zero into the front of number
  	  result[i] = 0 ;                   // ex. "1" in 5 digits number --> "00001" in int array
  	else {
      result[i] = number % 10;
      number /= 10;
    } // end else
  } // end for
  
} // IntToIntArray()
