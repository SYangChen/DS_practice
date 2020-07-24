/*  
 *  資工110
 *  B063040061 
 *  陳少洋
 *  Sep. 17, 2018
 *  Assignmenet #1.1
 *  製作並印出邊長分別為1、3、5、7、9的 Magic Square
 *  Magic Square 為一任意行列數字和為相同值之正方格
 */ 

#include <iostream>

using namespace std;

// ---------------using function-------------------
void MagicSquare( int num ) ;            // num is x level magic square 
void PrintS( int **square, int num ) ;   // square is an two dynamic array store the numbers
// ---------------using function-------------------

int main() {
	MagicSquare(1) ;
	MagicSquare(3) ;
	MagicSquare(5) ;
	MagicSquare(7) ;
	MagicSquare(9) ;
	system("pause") ; 
} // main()

// ------------------------------------------------

void MagicSquare( int num ) {
	// build up a two dimension dynamic array ( magic square ) 
	int i, j ;                     // row, column
	int **square = new int*[num] ; // magic square
	for ( i = 0 ; i < num ; i++ )
		square[i] = new int[num] ;
	// initialize array and set as 0 ( symbolize empty )
	for ( i = 0, j = 0 ; i < num ; i++ ) {
		for ( j = 0 ; j < num ; j++ )
			square[i][j] = 0 ;
	}
	// fill up the number into matrix
	square[num-1][num/2] = 1 ; // set start point ( can be any point )
	i = num ;                  // num-1+1 -> i++
	j = num/2+1 ;              // num/2+1 -> j++
	for ( int k = 2 ; k <= num*num ; k++, i++, j++ ) {
		if ( square[i%num][j%num] == 0 )
			square[i%num][j%num] = k ;
		else {
			i = i-2 ;
			j = j-1 ;
			square[(num+i)%num][(num+j)%num] = k ;
		}
	}
	PrintS( square, num ) ;
} // MagicSquare() 

// ------------------------------------------------

void PrintS( int **square, int num ) {
	// print out the square
	cout << "Magic Square " << num << "x" << num << endl ;
	for ( int i = num-1, j = num-1 ; i >= 0 ; i-- ) {
		for ( j = num-1 ; j >= 0 ; j-- )
			cout << square[i][j] << "\t" ;
		cout << endl << endl ;
	}
} // PrintS()

