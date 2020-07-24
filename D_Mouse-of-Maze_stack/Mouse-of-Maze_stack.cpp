#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream> 

using namespace std;
fstream fi ;                            // file input
fstream fo ;                            // file output

bool done ;

typedef struct node {
	
  int walk_x ;
  int walk_y ;
  int steps ;
  node *next ;
  
}node; 

class Stack {
  
  private :
  	
  	node *top ;

  public :
  	
  	void Init() {
  	  
	  top = NULL ; 
	   
	} // Init() 
	
	// *******************************
	
	void push( int x, int y ) {
	  
	  node *temp = new node ;
	  
	  if ( top == NULL )                 // set steps
	    temp->steps = 1 ;
	  else
	    temp->steps = top->steps+1 ;
	
	  temp->walk_x = x ;                 // store data
	  temp->walk_y = y ;
	  temp->next = top ;
	  top = temp ;                       // link
	  
	} // Stack::push()
	
	// *******************************
	
	void pop() {
	  // always remove the last "push" data
	  node *cur ;            
	  if ( top == NULL )
	    cout << "fail" ;
	  else {
	  	cur = top ;
	  	top = cur->next ;
	  }
	  
	} // Stack::pop()
	
	// *******************************
	
	node *GetTop() {
	  
	  return top ;
	  
	} // GetTop()
	
	// *******************************
  	
  	int GetSteps() {
  	  
  	  return top->steps ;
  	  
	} // GetSteps()
	
	// *******************************
	
	void Copy( node *copy ) {
	  
	  // node *paste ;
	  node *temp ;
	  node *walk ;
	  node *cur = NULL ;
	  for ( walk = copy ; walk != NULL ; walk = walk->next ) {
	  	temp = new node ;
	  	temp->walk_x = walk->walk_x ;
	  	temp->walk_y = walk->walk_y ;
	  	temp->steps = walk->steps ;
	  	temp->next = NULL ;
	  	if ( cur == NULL ) {
	  	  top = temp ;
	  	  cur = temp ;
	    } // end if
	  	else {
	  	  cur->next = temp ;
	  	  cur = cur->next ;
	    } // end else
	  } // end for
	  
	  // return paste ;
	  
	}
	
	// *******************************
	
	void PrintXY( int sequence, node *cur ) {
		
	  if ( cur == NULL )
	    ;
	  else {
	    PrintXY( sequence-1, cur->next ) ;
	    cout << "[" << sequence << "]" << cur->walk_x << "," << cur->walk_y << endl ;
      } // end else
      
	} // PrintXY()
  	
  	
};


class Maze {
	
  private :
    
    Stack mouse ;
    Stack min ;
  	char **maze ;
  	// char maze[MAX_ROW][MAX_COL] ;
  	int usingRow, usingCol ;
  	int steps ;
  	int minsteps ;
  	
  	
  public :
  	
  	void SetStart() {
  	  // Set start point and set the obstacles around the maze.
  	  
  	  int i = 0, j = 0 ;
  	  // mouse.Stack() ;
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
  	  
  	  mouse.Init() ;                                                      // INITIATE 
  	  min.Init() ;
  	  steps = 0 ;
  	  minsteps = 0 ;
  	  
	} // SetStart()::maze
	
	// *************************************************
	
	void Read() {                      // build input maze
	  
	  fi >> usingRow ;
      fi >> usingCol ;
      usingRow++, usingCol++ ;
      
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
      steps++ ;
      // Print() ;
	  // system("pause") ; 
      if ( maze[i][j+1] == 'G' ||\
	       maze[i+1][j] == 'G' ||\
		   maze[i][j-1] == 'G' ||\
		   maze[i-1][j] == 'G' ) {
		if ( minsteps == 0 || steps < minsteps ) 
		  minsteps = steps ;
		
		steps-- ;
		done = true ;
      } // end if
      else if ( steps >= minsteps && minsteps != 0 ) ;          // the route is more than the current minimun
      else {
      	
      	if( maze[i+1][j] == 'E' ) Visit( i+1, j ) ;            // right
      	if( maze[i][j-1] == 'E' ) Visit( i, j-1 ) ;            // up
        if( maze[i-1][j] == 'E' ) Visit( i-1, j ) ;            // left
        if( maze[i][j+1] == 'E' ) Visit( i, j+1 ) ;            // down

        maze[i][j] = 'V';
        steps-- ;
      } // end else
      
    } // Visit()
    
    // ************************************************* 
    
    void RouteStack( int i, int j ) {
      // just one route to goal
      maze[i][j] = 'V';
      // Print() ;
	  // system("pause") ; 
      mouse.push( i, j ) ;
      if ( maze[i][j+1] == 'G' ||\
	       maze[i+1][j] == 'G' ||\
		   maze[i][j-1] == 'G' ||\
		   maze[i-1][j] == 'G' ) {
		   	
		if ( maze[i][j+1] == 'G' ) mouse.push( i, j+1 ) ;           // push "goal" step
		if ( maze[i+1][j] == 'G' ) mouse.push( i+1, j ) ;
		if ( maze[i][j-1] == 'G' ) mouse.push( i, j-1 ) ;
		if ( maze[i-1][j] == 'G' ) mouse.push( i-1, j ) ;
		
        if ( min.GetTop() == NULL || mouse.GetSteps() < min.GetSteps() ) 
          min.Copy( mouse.GetTop() );                                     // Duplicate
          
        mouse.pop() ;
        mouse.pop() ;
        maze[i][j] = 'E' ;
      } // end if
      else if ( min.GetTop() != NULL && mouse.GetSteps() >= min.GetSteps() ) {
        mouse.pop() ; 
	    maze[i][j] = 'E' ;                                          // the route is more than the current minimun
      } // end else if
      else {

      	if( maze[i+1][j] == 'E' ) RouteStack( i+1, j ) ;            // right
      	if( maze[i][j-1] == 'E' ) RouteStack( i, j-1 ) ;            // up
        if( maze[i-1][j] == 'E' ) RouteStack( i-1, j ) ;            // left
        if( maze[i][j+1] == 'E' ) RouteStack( i, j+1 ) ;            // down

        mouse.pop() ;
        maze[i][j] = 'E' ;
        
      } // else
      
    } // Route()
    
    // ************************************************* 
    
    void ChangeRoute() {
      // change the original maze map to the maze with the shortest route
      node *change = min.GetTop() ;
      node *cur = change->next ;             // print 'r' without goal 
      for ( ; cur != NULL ; cur = cur->next )
        maze[cur->walk_x][cur->walk_y] = 'R' ;
      
	} // PrintRoute()
	
	// ************************************************* 
	
	void Printxy() {
	  
	  cout << endl << "The shortest path to the nearest goal is as follows:" << endl ;
	  min.PrintXY( min.GetSteps(), min.GetTop() ) ;
	  
	} // Printxy()
	
	// ************************************************* 
	
	void PrintShortest() {
	  
	  cout << endl << "Shortest path length = " << min.GetSteps() << endl ;
	  
	} // PrintShortest()

    
};


	
int main() {
	
  Maze maze ;                               // maze for visit 
  Maze maze2 ;                              // maze for route
  std::string num ;
  int command ;        
  done = false ;
  cout << "******** Shortest Path Finding ********\n\
* 0. Quit                               *\n\
* 1. Shortest path to a goal            *\n\
* 2. Shortest path to the nearest goals *\n\
-----------------------------------------\n\
Input a command(0, 1, 2) : " ;
  cin >> command ;
  while ( command != 0 ) {

    if ( command == 1 ) {
    	
      cout << "Input a file number (e.g., 311, 312, 313) :" ;
      cin >> num ;
      if ( !maze.LoadIn( num ) )
        cout << "Input file does not exist, please try again!" << endl ;
      else { 
        // maze.WriteOut( num ) ;
        maze2.LoadIn( num ) ;
        maze.Print() ;
        cout << endl ;
        maze.Visit( 1, 1 ) ;
        maze.Print() ;
        cout << endl ;
        if ( !done )
          cout << "Couldn't find any target." << endl ;
        else {
          maze2.RouteStack( 1, 1 ) ;
          maze2.ChangeRoute() ;
          maze2.Print() ;
          maze2.PrintShortest() ;
        } // end if
      } // end else  
      
	} // end if
	
	else if ( command == 2 ) {
		
	  cout << "Input a file number (e.g., 311, 312, 313) :" ;
      cin >> num ;
      if ( !maze.LoadIn( num ) )
        cout << "Input file does not exist, please try again!" << endl ;
      else {
        maze2.LoadIn( num ) ;
        maze.Print() ;
        cout << endl ;
        maze.Visit( 1, 1 ) ;
        maze.Print() ;
        cout << endl ;
        if ( !done )
          cout << "Couldn't find any target." << endl ;
        else {
          maze2.RouteStack( 1, 1 ) ;
          maze2.ChangeRoute() ;
          maze2.Print() ;
          maze2.Printxy() ;
        } // end else
	  } // end else                        
	  
    } // end else if
    
	else
	  cout << "Couldn't find command, please try again!" << endl ;
    cout << "******** Shortest Path Finding ********\n\
* 0. Quit                               *\n\
* 1. Shortest path to a goal            *\n\
* 2. Shortest path to the nearest goals *\n\
-----------------------------------------\n\
Input a command(0, 1, 2) : " ;
    cin >> command ;
    num.clear() ;                                   // clear content
    done = false ;
  } // end while
  
} // main()
 


