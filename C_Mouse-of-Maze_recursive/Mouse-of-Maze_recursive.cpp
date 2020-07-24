#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

using namespace std;
fstream fi ;                            // file input
fstream fo ;                            // file output

bool second ;                           // determine whether it is the second mission 
bool done ;                             // found the goal 

class Maze {
	
  private :
    
  	char **maze ;
  	// char maze[MAX_ROW][MAX_COL] ;
  	int usingRow, usingCol ;
  	int goalAmounts ;
  	
  public :
  	
  	void SetStart() {
  	  // Set start point and set the obstacles around the maze.
  	  
  	  int i = 0, j = 0 ;
  	  for ( ; j <= usingCol ; j++ )      // left
		maze[i][j] = 'O' ;
	  j = 0 ;
	  for ( ; i <= usingRow ; i++ )      // up
	    maze[i][j] = 'O' ; 
	  i = usingRow ;
	  for ( ; j <= usingCol ; j++ )      // right
	    maze[i][j] = 'O' ;
	  j = usingCol ;
	  for ( ; i >= 0 ; i-- )             // down
	    maze[i][j] = 'O' ;
  	  
	} // SetStart()::maze
	
	// *************************************************
	
	void Read() {                      // build input maze
	  
	  fi >> usingCol ;
      fi >> usingRow ;
      usingRow++, usingCol++ ;
      if ( second )                                 // determine whether it is the second case 
        fi >> goalAmounts ;
      
      maze = new char*[usingRow+1] ;                // Dynamical Memory Allocation of array in two dimension
      for( int a = 0 ; a < usingRow+1 ; a++ ) 
        maze[a] = new char[usingCol+1] ;

  	  int i = 1, j = 1 ;                            // input by file
  	  while ( j < usingCol ) {
  	    if ( i >= usingRow ) {
  	   	  i = 1 ;
  	  	  j++ ;
		} // end if
		fi >> maze[i][j] ;
  	  	i++ ;
	  } // end while
	  SetStart() ;
	  
	} // Read()
	
	// *************************************************
	
	void Print() {
	  // print on screen
	  int i = 1, j = 1 ;
  	  for( j = 1 ; j < usingCol ; j++ ) {
  	    for( i = 1 ; i < usingRow ; i++ ) {
  	      cout << maze[i][j] ;
  	     } // for
  	    cout << endl ;
	  } // for
	  
	} // Print 
	
	// *************************************************
	
	void Write() {
	  // write down in the file
	  int i = 1, j = 1 ;
  	  for( j = 1 ; j < usingCol ; j++ ) {
  	    for( i = 1 ; i < usingRow ; i++ ) {
  	      fo << maze[i][j] ;
  	     } // for
  	    fo << endl ;
	  } // for
	
	} // Write()
	
	// *************************************************
	
	bool LoadIn( std::string num ) {
	  // load in by file
	  std::string read = "input";           
      read.append( num ) ;
  	  read.append( ".txt") ;
  	  fi.open( read.c_str(), ios::in );                    // file open / read 
  	  if ( !fi )
  	    return false ;
  	  else {
        Read() ;
		// "getline" or "get" here (input)
		fi.close() ;
  	    return true ;
  	  } // end else 
  	  
	} // LoadIn()
	
	// *************************************************
	
	void WriteOut( std::string num ) {
		
	  std::string write = "output" ;
	  write.append( num ) ;
	  write.append( ".txt") ;
	  fo.open( write.c_str(), ios::out );               // file open / out & append ( ios::out|ios::app )
      cout << "File Descriptor: " << fo << endl;        // if there are an address than it build successful.
      // fo << "Hello!! success" << endl;               // output data in file
      Write() ;
      fo.close() ;
      
	} // WriteOut()
	
	// *************************************************
	
    void Visit( int i, int j ) {
      // all route it has visited
      maze[i][j] = 'V';
      if ( maze[i][j+1] == 'G' ||\
	       maze[i+1][j] == 'G' ||\
		   maze[i][j-1] == 'G' ||\
		   maze[i-1][j] == 'G' ) {
        Print() ;
        done = true ;
      } // end if
      else {
      	
        if( maze[i][j+1] == 'E' ) Visit( i, j+1 ) ;            // down
        if( maze[i+1][j] == 'E' ) Visit( i+1, j ) ;            // right
        if( maze[i][j-1] == 'E' ) Visit( i, j-1 ) ;            // up
        if( maze[i-1][j] == 'E' ) Visit( i-1, j ) ;            // left

        maze[i][j] = 'V';
      } // end else
      
    } // Visit()
    
    // ************************************************* 
    
    void Route( int i, int j ) {
      // just one route to goal
      maze[i][j] = 'R';
      if ( maze[i][j+1] == 'G' ||\
	       maze[i+1][j] == 'G' ||\
		   maze[i][j-1] == 'G' ||\
		   maze[i-1][j] == 'G' ) 
        Print() ;
      else {

        if( maze[i][j+1] == 'E' ) Route( i, j+1 ) ;
        if( maze[i+1][j] == 'E' ) Route( i+1, j ) ;
        if( maze[i][j-1] == 'E' ) Route( i, j-1 ) ;
        if( maze[i-1][j] == 'E' ) Route( i-1, j ) ;
        

        maze[i][j] = 'E' ;
      } // else
      
    } // Route()
  	
  	// *************************************************
  	
  	void VisitMoreGoal( int i, int j, std::string num ) {
      // every route it has visited for more than one goal 
      maze[i][j] = 'V';
      if ( ( maze[i][j+1] == 'G' ) ||\
	       ( maze[i+1][j] == 'G' ) ||\
		   ( maze[i][j-1] == 'G' ) ||\
		   ( maze[i-1][j] == 'G' ) ) {                       // if it find any goal
		goalAmounts-- ;
	    if ( goalAmounts == 0 ) {                            // base case
	      done = true ;
	      WriteOut( num ) ;
          // Print( maze ) ;
        } // end if
        
        if( maze[i][j+1] == 'E' ) VisitMoreGoal( i, j+1, num );
        if( maze[i+1][j] == 'E' ) VisitMoreGoal( i+1, j, num );
        if( maze[i][j-1] == 'E' ) VisitMoreGoal( i, j-1, num );
        if( maze[i-1][j] == 'E' ) VisitMoreGoal( i-1, j, num );
      } // end if
      else {

        if( maze[i][j+1] == 'E' ) VisitMoreGoal( i, j+1, num );
        if( maze[i+1][j] == 'E' ) VisitMoreGoal( i+1, j, num );
        if( maze[i][j-1] == 'E' ) VisitMoreGoal( i, j-1, num );
        if( maze[i-1][j] == 'E' ) VisitMoreGoal( i-1, j, num );

        maze[i][j] = 'V';
      } // end else
      
    } // VisitMoreGoal()
    
};


	
int main() {
	
  Maze maze ;                               // maze for visit 
  Maze maze2 ;                              // maze for route
  std::string num ;
  int command ;        
  cout << "****** Path Finding ******\n\
* 0. Quit                *\n\
* 1. A goal              *\n\
* 2. More goals          *\n\
--------------------------\n\
Input a command(0, 1, 2) : " ;
  cin >> command ;
  second = false ;
  done = false ;
  while ( command != 0 ) {

    if ( command == 1 ) {
    	
      cout << "Input a file number (e.g., 311, 312, 313) :" ;
      cin >> num ;
      if ( !maze.LoadIn( num ) )
        cout << "Input file does not exist, please try again!" << endl ;
      else { 
        // maze.WriteOut( num ) ;
        maze2.LoadIn( num ) ;
        maze.Visit( 1, 1 ) ;
        if ( !done )                                   // if it can not find any goal
          maze.Print() ;
        done = false ;                                 // initiate boolean
        cout << endl ;
        maze2.Route( 1, 1 ) ;
      } // end else  
      
	} // end if
	else if ( command == 2 ) {
		
	  second = true ;
	  cout << "Input a file number (e.g., 311, 312, 313) :" ;
      cin >> num ;
      if ( !maze.LoadIn( num ) )
        cout << "Input file does not exist, please try again!" << endl ;
      else {
      	maze.VisitMoreGoal( 1, 1, num ) ;
      	if ( !done )                                  // if it can not reach the goal amounts
      	  maze.WriteOut( num ) ;
      	done = false ;                                // initiate boolean
	  } // end else
	  second = false ;                                // initiate boolean
	  
    } // end else if
	else
	  cout << "Couldn't find command, please try again!" << endl ;
    cout << "****** Path Finding ******\n\
* 0. Quit                *\n\
* 1. A goal              *\n\
* 2. More goals          *\n\
--------------------------\n\
Input a command(0, 1, 2) : " ;
    cin >> command ;
    num.clear() ;                                   // clear content
  } // end while
  
} // main()



