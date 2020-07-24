/*  資工110 
 *  B063040061 
 *  陳少洋
 *  Oct. 26, 2018
 *  Assignmenet #4
 *  使用Recursion的寫法，判斷西洋棋棋士是否能以其限制之走法，
 *	完成一個使用者所輸入的棋盤大小，若能完整走完棋盤的每一格，
 *	則輸出其中一種走法。 
 */ 
 
#include <iostream>
#include <cstdlib>

using namespace std ;

bool ok ;	// to check if there are any answer that we have gotten

void Init( int n, int **&board ) {
	// initiate the board
	// they're 2D dynamic array
	board = new int*[n+1] ;
	for ( int i = 0 ; i < n ; i++ ) 
		board[i] = new int[n+1] ;
		
	for ( int i = 0 ; i < n ; i++ ) {
		for ( int j = 0 ; j < n ; j++ ) 
				board[i][j] = 0 ;
	}
	
}

void Print( int n, int **board ) {
	// output the board answer
	for ( int i = 0 ; i < n ; i++ ) {
		for ( int j = 0 ; j < n ; j++ )
			cout << board[i][j] << "\t" ;
		cout << endl << endl ;
	}
}

void run( int square, int **board, int i , int j, int steps ) {
	// recursion function 
	// find if there have next step
	board[i][j] = steps ;
	// check[steps-1][dir] = 1 ;
	if ( steps == square*square ) {
		Print( square, board ) ;
		ok = true ;
	}
	else if ( ok ) ;
	else {
		// using 8 "is" instead of "else if"
		// because after it return back it can try the next direction atomatic
		if ( i-2 >= 0 && j+1 < square && board[i-2][j+1] == 0 ) {
			run( square, board, i-2, j+1, steps+1 ) ;
			board[i-2][j+1] = 0 ;
			// return back, set as 0 ( not finish )
		}
		if ( i-1 >= 0 && j+2 < square &&  board[i-1][j+2] == 0 ) {
			run( square, board, i-1, j+2, steps+1 ) ;
			board[i-1][j+2] = 0 ;
		}
		if ( i+1 < square && j+2 < square && board[i+1][j+2] == 0 ) {
			run( square, board, i+1, j+2, steps+1 ) ;
			board[i+1][j+2] = 0 ;
		}
		if ( i+2 < square && j+1 < square && board[i+2][j+1] == 0 ) {
			run( square, board, i+2, j+1, steps+1 ) ;
			board[i+2][j+1] = 0 ;
		}
		if ( i+2 < square && j-1 >= 0 && board[i+2][j-1] == 0 ) {
			run( square, board, i+2, j-1, steps+1 ) ;
			board[i+2][j-1] = 0 ;
		}
		if ( i+1 < square && j-2 >= 0 && board[i+1][j-2] == 0 ) {
			run( square, board, i+1, j-2, steps+1 ) ;
			board[i+1][j-2] = 0 ;
		}
		if ( i-1 >= 0 && j-2 >= 0 && board[i-1][j-2] == 0 ) {
			run( square, board, i-1, j-2, steps+1 ) ;
			board[i-1][j-2] = 0 ;
		}
		if ( i-2 >= 0 && j-1 >= 0 && board[i-2][j-1] == 0 ) {
			run( square, board, i-2, j-1, steps+1 ) ;
			board[i-2][j-1] = 0 ;
		}
		
	}
}

int main() {
	
	int **board ;				// chess board
	int square, steps ;			// n*n square, steps order
	int x = 6 ;
	for( square = 1 ; square <= x ; square++ ) {
		Init( square, board ) ;	// initiate data
		ok = false ;			// no answer
		cout << "n = " << square << endl ;
		run( square, board, 0, 0, 1 ) ;
		if ( !ok )				// there have not any answer
			cout << "no solution" << endl << endl ;
	}
	system("pause") ;
}


