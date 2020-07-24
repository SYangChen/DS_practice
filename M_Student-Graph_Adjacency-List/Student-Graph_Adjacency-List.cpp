#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream> 
#include <vector> 
#include <cmath>
#include <algorithm>    // std::sort 
#define MAX_LENGTH 10 


using namespace std;

fstream fin ;                             // file input
fstream fout ;                            // file output
FILE *fp;

typedef struct data {
	
	char sid1[MAX_LENGTH] ;
	char sid2[MAX_LENGTH] ;
	float weight ;
	
}data;

// adjacency list begin

typedef struct stdNode {
	
	char stdid[MAX_LENGTH] ;
	float weight ;
	stdNode *next = NULL ;

}stdNode;

typedef struct stdList {
	
	char headid[MAX_LENGTH] ;
	stdNode *first = NULL ;
	bool visited = false ;
	
}stdList;


// adjacency list end


typedef struct cc {
	char stdid[MAX_LENGTH] ;
	cc *next = NULL ; 
}cc;

typedef struct ccL {
	int ccSize = 0 ;
	cc *first = NULL ;
}ccL;
bool cmp_size (ccL a,ccL b) { return  a.ccSize>=b.ccSize ;  }  
	
class Assignment {
	
	
	
	private :
		
		vector<data> inList ;
  		vector<stdList> adjList ;
  		vector<stdList> stack ; 
  		vector<ccL> ccList ;
  		
  		
	public :
		
		Assignment() {
			;
		}
		
		
		// *************************************************
  	
  		void Clear() {
  			inList.clear() ;
  			adjList.clear() ;
			stack.clear() ;
			ccList.clear() ;
		}
		
		// *************************************************
		
		
		void ReadBin() {											// read binay file
			int count = 0 ;
			char temp[10] ;
			data tempData ;
			while( ( tempData.sid1[0] = fgetc (fp)) != EOF ) {		// Is the end of file ?
				fread( &tempData.sid1[1], 9, 1, fp ) ;
				fread( &tempData.sid2, 10, 1, fp ) ;
				fread( &tempData.weight, 4, 1, fp ) ;
				PushInList( tempData ) ;
				strcpy( temp, tempData.sid1 );			// it a undirected grapgh
				strcpy( tempData.sid1, tempData.sid2 );
				strcpy( tempData.sid2, temp ) ;
				PushInList( tempData ) ;
			} // while
			
		} // readBin		
		
		// *************************************************
		
		void PushInList( data tempData ){
			int i = 0 ;
			if( inList.empty() )
				inList.push_back( tempData ) ;
			else if( strcmp( inList.back().sid1, tempData.sid1 ) <= 0 ) // no elemen bigger than tempData.sid1
				inList.push_back( tempData ) ;							// tempData.sid1 is the biggest in the inList
																		
			else{
				i = LowerBound( 0, inList.size()-1 , tempData.sid1 ) ;
				inList.insert( inList.begin()+i, tempData ) ;
			}
		}  // PushInList
		
		// *************************************************
		
		
		int LowerBound( int low, int high, char target[10] ){	// 回傳大於target的第一個sid 			
			if( low > high )
				return low ;
  			int mid = low + (high - low) / 2 ;					// 防止溢位
			if( strcmp( inList[mid].sid1, target ) <= 0 )
				return LowerBound( mid+1, high, target ) ;
			else
				return LowerBound( low, mid-1, target ) ;
  			
		} // LowerBound(
		
		// *************************************************
		
		bool LoadInBin( std::string num ) {						// load file in binary mode
			std::string read = "pairs";           
      		read.append( num ) ;
  	  		read.append( ".bin") ;
  	  		fp = fopen(  read.c_str(),"rb" );
  	  		if ( fp == NULL ) 
  	  			return false ;
			else {
				ReadBin() ;
				fclose(fp) ;
				return true ;	
			}
		} // LoadInBin()
		
		// *************************************************
		
		
		void CreateAdjList(){			
			int i = 0 ;
			stdList newHead ;	// create a adjList( by sid ) 
			stdNode *stdCur ; 
			while( i < inList.size() ){
				strcpy( newHead.headid, inList[i].sid1 ) ; // initialize adjList(by sid)
				newHead.first = new stdNode ;
				strcpy( newHead.first->stdid, inList[i].sid2 ) ;
				newHead.first->weight = inList[i].weight ;
				// insert to asjList( by weight )
				for( ; strcmp( newHead.headid, inList[i].sid1 ) == 0 ; ++i ){	
					stdCur = newHead.first ;
					InsertStdNode( newHead.first, stdCur, inList[i] ) ;
				
				} // for
				adjList.push_back( newHead ) ;	// insert to adjList(by sid)	
			} // while
		} // createAdjList

		// *************************************************
  		
  		void InsertStdNode( stdNode *pre, stdNode *cur, data newData ){
  			// insert a new node into a ptrList 
  			// the ptrList oder decided by weight value
  			// first is biggest
  			if( cur == NULL ){									// create newNode   			
  				cur = new stdNode ;
  				cur->weight = newData.weight ;
  				strcpy( cur->stdid, newData.sid2 ) ;
  				pre->next = cur ;
			  } // if
			else if( newData.weight < cur->weight )
				InsertStdNode( cur, cur->next, newData ) ;
			
			else if( newData.weight >= cur->weight ){
				stdNode *newNode = new stdNode ; 
				newNode->weight = cur->weight ; 				// newNode deep copy curNode
				strcpy( newNode->stdid, cur->stdid ) ;
				cur->weight = newData.weight ;
  				strcpy( cur->stdid , newData.sid2 ) ;
  				newNode->next = cur->next ;
  				cur->next = newNode ;
			} // else if
		} // InsertStdNode
		
		
		// *************************************************
		void WriteOut( std::string num, int type ) {					// output a file of hashTable
			std::string write ;
			write = "input" ;
	  		write.append( num ) ;
	  		if( type == 1 )
	  			write.append( ".adj" ) ;
	  		if( type == 2 )
	  			write.append( ".cc" ) ;
	  		fp = fopen(  write.c_str(),"w+" );	               // file open / out & append ( ios::out|ios::app )
	  		
	  		
	  		// mission one output
			if( type == 1 ){		
				for( int i = 0 ; i < adjList.size() ; i++ ){
					fprintf( fp, "\n[%3d] %s: \n", i+1, adjList[i].headid ) ;
					stdNode *stdWalk = adjList[i].first ;
					for( int j = 1 ; stdWalk != NULL ; stdWalk = stdWalk->next, j++ ){
						fprintf( fp, "\t(%2d)  %s,  %.2f", j, stdWalk->stdid, stdWalk->weight ) ;
						if( j % 5 == 0  ) fprintf( fp, "\n " ) ;
					} // for	
		    	} // for
		    fprintf( fp, "\n\n<<< There are %d nodes in total. >>>\n", inList.size()) ;
			} // if
			
			// mission two output
			if( type == 2 ){
				for( int i = 0 ; i < ccList.size() ; i++ ){	
					fprintf( fp, "{%2d} Connected Component: size = %d\n ", i+1, ccList[i].ccSize) ;
					cc *ccWalk = ccList[i].first ;
					for( int j = 1 ; ccWalk != NULL ; ccWalk = ccWalk->next, j++ ){
						fprintf( fp, "  (%3d) %s", j, ccWalk->stdid ) ;
						if( j % 5 == 0  )
							fprintf( fp, "\n " ) ;
					} // for
					fprintf( fp, "\n" )	;
		    	} // for
			} // if
			
      		fclose(fp) ;										// output file done
      		
		} // WriteOutAdj()
			
			
		// *************************************************
			
		void Print() {
			
			printf("<<< %d pairs => %d nodes >>>\n\n", inList.size()/2, inList.size() ) ;
			cout<< "Adjacency lists are written into a file... \n\n"  ;
			printf("<<< There are %d nodes in total. >>>\n\n", inList.size() ) ;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;
			cout << "Mission 2: Find connected components  " << endl ;
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl ;
			printf( "~~~ Connected Components ~~~ ") ;
				for( int i = 0 ; i < ccList.size() ; i++ ){	
					printf( "\n{%2d} Connected Component: size = %d\n    ", i+1, ccList[i].ccSize) ;
					cc *ccWalk = ccList[i].first ;
					for( int j = 1 ; ccWalk != NULL ; ccWalk = ccWalk->next, j++ ){
						printf( "  (%3d) %s", j, ccWalk->stdid ) ;
						if( j % 5 == 0  )
							printf(  "\n    " ) ;
					} // for
		    	} // for			
		} // Print 
		
		
		
		// *************************************************


		

		void Traversal(){
			int i = 0, j = 0 ;
			for( i = 0 ; i < adjList.size() ; i++ ) {
 				if( ! adjList[i].visited )
 					DFSIterative( &adjList[i] ) ;
			} // for
			
    		std::sort(ccList.begin(), ccList.end(),cmp_size);		// sort ccLsit by size
		} // Traversal
		
		


		
		void DFSIterative( stdList *vp ){
			int cc_count = 1 ;
			ccL newcc ;										// create a linked list for cc and initialize 
			newcc.first = new cc ;							// 配置記憶體 
			strcpy ( newcc.first->stdid, vp->headid );		// the linked list first data	
			
			// start DFStraversal
			vp->visited = true ;
			stack.push_back( *vp ) ;							// push into stack

			while( ! stack.empty() ){
				stdList u = stack.back();							// getTop
				stdList *wp = FindStdNode_NearVertex( u.first ) ;	// find a vertex "w" near by u and unvisited
				if( wp != NULL ){									// w exist and wp is point to w
					cc_count++ ; 
					cc *cur = newcc.first ;
				
					InsertccNode( newcc.first, cur, wp->headid ) ;
					wp->visited = true ;
					stack.push_back( *wp ) ;
				} // if
				else
					stack.pop_back() ;
			} // while
			newcc.ccSize = cc_count ;
			ccList.push_back( newcc ) ;
		} // DFSIterative
		
		void InsertccNode( cc *pre, cc *cur, char newSid[10] ){
			// insert newNode into cc
			// the order of this linked list decided by the value of sid 
			if( cur == NULL ){
				cur = new cc ;
				strcpy( cur->stdid, newSid ) ;
				pre->next = cur ;
			}  // if
			else if( strcmp( cur->stdid, newSid ) < 0 )
				InsertccNode( cur, cur->next, newSid ) ;
			else {
				cc *NewNode = new cc ;
				strcpy( NewNode->stdid, cur->stdid ) ;
				strcpy( cur->stdid, newSid ) ;
				NewNode->next = cur->next ;
				cur->next = NewNode ;
			} // else
			
		} // InsertccNode

		// *************************************************
		
		stdList* FindStdNode_NearVertex( stdNode *u ){	
		// return a pointer which point to the unvisite vertex near by vertex U.
		
			stdNode *walk = u ;							// adjList(by weight) teversal pointer.
			stdList *vp ;								// the vertex in adjList(by sid) which corresponding to the
														// node in adjList(by weight).
			while( walk != NULL ){						
				vp = BinarySearchStdList( walk->stdid ) ; // search the vertex in adjList(sid) which coresponding to 
				if( ! vp->visited )						  // the node in adjList(weight)
					return vp ;							  // traversal until find unvisited vertex
				else
					walk = walk->next ;
			} // while
			return NULL ;
		} // FindStdNode_NearVertex
		
		stdList* BinarySearchStdList( char target[10] ){			// 尋找對應點 
			int low = 0, high = adjList.size() ;
			while( low <= high ){
				int mid = low + ( high - low ) / 2 ;
				if ( strcmp( adjList[mid].headid, target ) < 0 )
					low = mid + 1 ;
				if ( strcmp( adjList[mid].headid, target ) > 0 )
					high = mid - 1 ;
				if ( strcmp( adjList[mid].headid, target ) == 0 )
					return &adjList[mid] ;
			} // while 			
			return NULL ;
		}
	}; 


	
int main() {
	
	Assignment assignment ;
	int k ;
	std::string num ;
	std::string command = "87" ;     
	std::string searchTarget = "87" ; 
	while ( command != "0" ) {
		cout << "******************************************" << endl ;
		cout << "* On-machine Exercise                    *" << endl ;
		cout << "*  Mission 1: Build adjacency lists      *" << endl ;
		cout << "* Mission 2: Find connected components   *" << endl ;
		cout << "******************************************" << endl ; 
		cout << "########################################################" << endl ;
		cout << "Mission 1: Build adjacency lists  " << endl ;
		cout << "########################################################" << endl ;
		cout << "Input the file number[0]Quit : " << endl ;
		cin >> num ;
		while ( num != "0" ) {
			if ( !assignment.LoadInBin( num ) ) {
				cout << "No such file, please enter again!" << endl << "Input the file number[0]Quit : " << endl ;
				cin >> num ;
				if ( num == "0" ) return 0 ;
			}
			else {

				assignment.CreateAdjList() ;
				assignment.WriteOut( num, 1 ) ;
				assignment.Traversal() ;
				assignment.Print() ;			// print to screen
				assignment.WriteOut( num, 2 ) ;
				num = "0" ;
			}
			
		}


		cout << "\n\nplease enter '0' or any other to continue" << endl ;
		assignment.Clear() ;
		cin >> command ; 
	}
} // main()





