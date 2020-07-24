/*  資訊二甲 
 *  陳少洋
 *  10527130 
 */ 

// #include <cstdlib>
#include <math.h>
#include <iostream>
// #include <string.h>
// #include <stdio.h>

using namespace std;

int gOuterTimes = 0 ;                               
unsigned long long int gx, gy ;                   // using the biggest integer size
int gSequence ;

// ****************Using Function******************
void LoopOfFibNum() ;
unsigned long long int RecOfFibNum( int testNum, unsigned long long int fibNum, unsigned long long int prev ) ;
unsigned long long  int FindBiggestFactor_L( unsigned long long int & x, unsigned long long int & y, unsigned long long int fibNum ) ;
unsigned long long  int FindBiggestFactor_R( unsigned long long int x, unsigned long long int y,\
                                             unsigned long long int fibNum, unsigned long long times ) ;
void PrintCurrentResult( int sequence, unsigned long long int fibNum, int lOrR ) ;

// ****************Using Function******************


int main() {
	
  int command ;
  int numForR ;         // number for recursion
  cout << "** Fibonacci Series Generator **\n\
* 0. Quit                      *\n\
* 1. Iterative generation      *\n\
* 2. Recursive generation      *\n\
--------------------------------\n\
Input a command(0, 1, 2): " ;
  cin >> command ;
  while ( command != 0 ) {
    if ( command == 1 ) {
      cout << "Input a number: " ;
  	  LoopOfFibNum() ;
    } // end if
    else if ( command == 2 ) {
      cout << "Input a number: " ;
      cin >> numForR ;
      gSequence = numForR ;
      numForR = RecOfFibNum( numForR, 1, 1 ) ;               // test here
      cout << "< Outer Loop : " << gOuterTimes << " times >" << endl ;
    } // end else if
    else
      cout << "Couldn't find command, please try again!" << endl ;
    cout << "** Fibonacci Series Generator **\n\
* 0. Quit                      *\n\
* 1. Iterative generation      *\n\
* 2. Recursive generation      *\n\
--------------------------------\n\
Input a command(0, 1, 2): " ;
    cin >> command ;
    gOuterTimes = 0 ;
  }

  cout << "Thanks for your visting!" ;
  
} // main()

// *************************************************

void LoopOfFibNum() {
  // finding fibonacci series and output it in the meantime
  int loop = 1 ;
  int testNum ;
  unsigned long long int temp ;
  int outerTimes = 0 ;
  int sequence = 1 ;
  unsigned long long int fibNum = 1 ;
  unsigned long long int lastNum = 1 ;
  cin >> testNum ;
  while ( testNum >= sequence ) {
    PrintCurrentResult( sequence, fibNum, loop ) ;
    temp = fibNum ;
	fibNum = fibNum+lastNum ;
	lastNum = temp ;             // last fibonacci number
    outerTimes++ ;
    sequence++ ;
  } // end while()
  
  cout << "< Outer Recursion : " << outerTimes << " times >" << endl ;
  
} // LoopOfFibNum()

// **************************************************

unsigned long long int RecOfFibNum( int testNum, unsigned long long int fibNum , unsigned long long int prev ) {
  // finding fibonacci series and output it in the meantime
  if( testNum == 0 ) { 
    gOuterTimes++ ;
    PrintCurrentResult( testNum, fibNum, 2 ) ;
    return prev;
  } // end if                              
  if( testNum == 1 ) {
  	gOuterTimes++ ;
  	PrintCurrentResult( testNum, fibNum, 2 ) ;
    return fibNum;
  } // end if
  
  PrintCurrentResult( testNum, fibNum, 2 ) ;                          
  gOuterTimes++ ;
  return RecOfFibNum( testNum-1, fibNum+prev, fibNum );    // sequence, next fibonacci number, last fibnacci number
 
} // RecOfFibNum()  

// ***************************************************

void PrintCurrentResult( int sequence, unsigned long long int fibNum, int lOrR ) {    // loop or recursion
	
  unsigned long long int x = 0, y = 0 ;
  unsigned long long  int innerLoop ;
  gx = 1, gy = 1 ;
  if ( lOrR == 1 )
    innerLoop = FindBiggestFactor_L( x, y, fibNum ) ;
  else {
  	x = sqrt( fibNum ) ;
  	y = fibNum/x ;
    innerLoop = FindBiggestFactor_R( x, y, fibNum, 0 ) ;
    x = gx ;                                               // recursion couldnt use call by reference
    y = gy ;                                               // so using global variables to set the factor that multiply by two numbers
    sequence = gSequence-sequence+1 ;                      // recursion sequence is reversed
  } // end else
  if ( gx == -1 )
    cout << "[ " << sequence << " ] " << fibNum << " = " << "( Inner recursion more than 100000000 times )" << endl ;
                                                         // if the recursion more than 10^8 needs at least 5G memory to complete it 
  else
    cout << "[ " << sequence << " ] " << fibNum << " = " << x << "*" \
    << y << "    ( Inner recursion : " << innerLoop << " times )" << endl ;
  
} // PrintCurrentResult_L()

// ***************************************************

unsigned long long  int FindBiggestFactor_L( unsigned long long int & x, unsigned long long int & y, unsigned long long int fibNum ) {
  // square root of fibonacci number, than minus one to find the biggest factor
  unsigned long long  int times ;
  x = sqrt( fibNum ) ;
  for ( times = 1 ; fibNum%x != 0 ; times++ )
    x-- ;
  y = fibNum/x ;
  return times ;
  
} // FindBiggestFactor_L()

// ***************************************************

unsigned long long  int FindBiggestFactor_R( unsigned long long int x, unsigned long long int y,\
                                             unsigned long long int fibNum, unsigned long long times ) {
  // square root of fibonacci number, than minus one to find the biggest factor ( x has already square root of fibNum )
  if ( fibNum == 1 ) {
    gx = 1 ;
    gy = 1 ;
    return 1 ;
  } // end if
  else if ( x*y == fibNum ) {
  	gx = x ;
  	gy = y ;
    return 1 ;
  } // end else if
  else if ( times > 100000000 ) {         //  if the recursion more than 10^8 times needs at least 5G memory to complete it
  	gx = -1 ;                             //  so i try to stop at 10^8 times
  	return 1 ;
  }
  else 
    return FindBiggestFactor_R( x-1 , fibNum/(x-1), fibNum, times+1 )+1 ;
} // FindBiggestFactor_R() 
