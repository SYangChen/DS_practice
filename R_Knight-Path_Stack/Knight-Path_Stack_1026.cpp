/*  資工110 
 *  B063040061 
 *  陳少洋
 *  Oct. 25, 2018
 *  Assignmenet #3
 *  以C++ class使用Stack的資料結構，判斷西洋棋棋士是否能以其限制之走法，
 *	完成一個使用者所輸入的棋盤大小，若能完整走完棋盤的每一格，
 *	則輸出其中一種走法。 
 */ 

#include <iostream>
#include <cstdlib>

using namespace std ;


typedef struct chessLoc {
	// chess loacation
	// using for storing the last step data int stack
	int i ;			// row
	int j ;			// column
	int direction ;	// for each direction 1~8
	chessLoc *next ;// stack link list
	
}chessLoc;

class stack {
	// using link list to complete stack ADT
	private :
		// stack top ( FILO )
		chessLoc *top ;
		
	public :
		
		stack() {
			// constructor for stack
			top = NULL ;
		} // stack()
		
		void push( int i , int j , int dir ) {
			// push into stack list
			chessLoc *temp = new chessLoc ;
	  
			temp->i = i ;                 // store data
			temp->j = j ;
			temp->direction = dir ;
	  		temp->next = top ;
	  		top = temp ;                  // link
	  		
		} // push()
		
		void pop() {
	  		// always remove the last "push" data
	  		chessLoc *cur ;            
	  		if ( top == NULL )
	    		cout << "fail" ;	// if there are any "error"
	  		else {
	  			cur = top ;
	  			top = cur->next ;
	  		}
	  
		} // Stack::pop()
		
		chessLoc *getTop() {
			// get top data ( last data )
			return top ;
		} // getTop()
			
}; 


void Init( int n, int **&board, int **&check ) {
	// initiate the board and check array
	// they're 2D dynamic array
	board = new int*[n+1] ;
	for ( int i = 0 ; i < n ; i++ ) 
		board[i] = new int[n+1] ;
		
	for ( int i = 0 ; i < n ; i++ ) {
		for ( int j = 0 ; j < n ; j++ ) 
				board[i][j] = 0 ;
	}
	
	check = new int*[n*n+2] ;
	for ( int i = 0 ; i < n*n+1 ; i++ )
		check[i] = new int[10] ;
		
	for ( int i = 0 ; i < n*n+1 ; i++ ) {
		for ( int j = 0 ; j < 9 ; j++ )
			check[i][j] = 0 ;
	}
} // Init()

void Print( int n, int **board ) {
	// output the chess board answer
	for ( int i = 0 ; i < n ; i++ ) {
		for ( int j = 0 ; j < n ; j++ )
			cout << board[i][j] << "\t" ;
		cout << endl << endl ;
	}
} // Print()

int main() {
	int **board ;						// chess board coordinate
	int **check ;						// checking for the direction whether it has done
	int steps, square, i, j, direction ;// steps order, n*n square, i&j coordinates, direction
	bool go ;							// if there are not any answer
	stack chess ;						// stack for chess
	int x = 6 ;
	for( square = 1 ; square <= x ; square++ ) {
		go = true ;
		steps = 1 ;
		Init( square, board, check ) ;	// initiate data
		// Print( square, board ) ;
		i = 0 ; j = 0 ;
		board[0][0] = steps ;			// set first steps at left-up board
		while ( go ) {
			// eight direction K1 to K8 ( below in order )
			if ( i-2 >= 0 && j+1 < square && board[i-2][j+1] == 0 && check[steps][1] == 0 ) {
				steps++ ;				// next steps
				chess.push( i, j, 1 ) ;	// push into stack ( i, j, direction )
				i -= 2 ; j += 1 ;		// update the coordinates
				board[i][j] = steps ;	// set steps on board
			}
			else if ( i-1 >= 0 && j+2 < square &&  board[i-1][j+2] == 0 && check[steps][2] == 0 ) {
				steps++ ;
				chess.push( i, j, 2 ) ;
				i -= 1 ; j += 2 ;
				board[i][j] = steps ;
			}
			else if ( i+1 < square && j+2 < square && board[i+1][j+2] == 0 && check[steps][3] == 0 ) {
				steps++ ;
				chess.push( i, j, 3 ) ;
				i += 1 ; j += 2 ;
				board[i][j] = steps ;
			}
			else if ( i+2 < square && j+1 < square && board[i+2][j+1] == 0 && check[steps][4] == 0 ) {
				steps++ ;
				chess.push( i, j, 4 ) ;
				i += 2 ; j += 1 ;
				board[i][j] = steps ;
			}
			else if ( i+2 < square && j-1 >= 0 && board[i+2][j-1] == 0 && check[steps][5] == 0 ) {
				steps++ ;
				chess.push( i, j, 5 ) ;
				i += 2 ; j -= 1 ;
				board[i][j] = steps ;
			}
			else if ( i+1 < square && j-2 >= 0 && board[i+1][j-2] == 0 && check[steps][6] == 0 ) {
				steps++ ;
				chess.push( i, j, 6 ) ;
				i += 1 ; j -= 2 ;
				board[i][j] = steps ;
			}
			else if ( i-1 >= 0 && j-2 >= 0 && board[i-1][j-2] == 0 && check[steps][7] == 0 ) {
				steps++ ;
				chess.push( i, j, 7 ) ;
				i -= 1 ; j -= 2 ;
				board[i][j] = steps ;
			}
			else if ( i-2 >= 0 && j-1 >= 0 && board[i-2][j-1] == 0 && check[steps][8] == 0 ) {
				steps++ ;
				chess.push( i, j, 8 ) ;
				i -= 2 ; j -= 1 ;
				board[i][j] = steps ;
			}
			else {
				// if there are not any way for the chess go next step
				// check whether pop out the data or it is the right answer
				chessLoc *temp = chess.getTop() ;
				if ( temp == NULL || steps == square*square )
					go = false ;
				else {
					chess.pop() ;
					for ( int k = 0 ; k < 9 ; k++ )
						check[steps][k] = 0 ;
					steps-- ;
					board[i][j] = 0 ;
					i = temp->i ;
					j = temp->j ;
					check[steps][temp->direction] = 1 ;
				}
			}
			// Print( square, board ) ;
			// cout << "-------------------------------------" << endl ;
		}
		cout << "n = " << square << endl ;
		if ( steps == square*square )  // output the board answer
			Print( square, board ) ;
		else
			cout << "no solution" << endl << endl ;
	}
	system("pause") ;
}
