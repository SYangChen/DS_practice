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
	stdNode *next ;

}stdNode;

typedef struct stdList {
	
	char headid[MAX_LENGTH] ;
	stdNode *first ;
	bool visited ;
	int order ;
	
}stdList;


// adjacency list end


typedef struct cc {
	char stdid[MAX_LENGTH] ;
	cc *next ; 
}cc;

typedef struct ccL {
	int ccSize ;
	cc *first ;
}ccL;
bool cmp_size (ccL a,ccL b) { return  a.ccSize>=b.ccSize ;  }  

	
	
class Edge {
	
	public:
		char beginID[MAX_LENGTH] ;
		char endID[MAX_LENGTH] ;
		float weight ;
	
	EdgeInfo( char inputBeginID[10], char inputEndID[10], float inputWeight ){
		strcpy( beginID, inputBeginID );
		strcpy( endID, inputEndID );
		weight = inputWeight ; 
	} // 建構子 
};
bool edge_cmp_weight (Edge a,Edge b) { return  a.weight>=b.weight ;  }  
	
class Assignment {
	
	private :
		
		vector<data> inList ;
  		vector<stdList> adjList ;
  		vector<stdList> stack ; 
  		vector<ccL> ccList ;
  		vector<Edge> priorityQ ;
  		vector<Edge> sp ;
  		
	public :
		
		Assignment() {
			;
		}
		
  		void Clear() {
  			inList.clear() ;
  			adjList.clear() ;
			stack.clear() ;
			ccList.clear() ;
			priorityQ.clear() ;
		}
		
/*******************************************************************************************
							Ex05
*******************************************************************************************/
		
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
		
		int LowerBound( int low, int high, char target[10] ){	// 回傳大於target的第一個sid 			
			if( low > high )
				return low ;
  			int mid = low + (high - low) / 2 ;					// 防止溢位
			if( strcmp( inList[mid].sid1, target ) <= 0 )
				return LowerBound( mid+1, high, target ) ;
			else
				return LowerBound( low, mid-1, target ) ;
  			
		} // LowerBound(
		
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
				
		void CreateAdjList(){			
			int i = 0 ;
			stdList newHead ;	// create a adjList( by sid ) 
			newHead.visited = false ;
			stdNode *stdCur ; 
			while( i < inList.size() ){
				strcpy( newHead.headid, inList[i].sid1 ) ; // initialize adjList(by sid)
				newHead.first = new stdNode ;
				newHead.first->next = NULL ;
				strcpy( newHead.first->stdid, inList[i].sid2 ) ;
				newHead.first->weight = inList[i].weight ;
				// insert to asjList( by weight )
				for( i= i+1 ; strcmp( newHead.headid, inList[i].sid1 ) == 0 ; i++ ){	
					stdCur = newHead.first ;
					InsertStdNode( newHead.first, stdCur, inList[i] ) ;
				
				} // for
				adjList.push_back( newHead ) ;	// insert to adjList(by sid)	
			} // while
			
			for( int j = 0 ; j < adjList.size() ; j++ )
				adjList[j].order = j+1 ;
			
		} // createAdjList

  		void InsertStdNode( stdNode *pre, stdNode *cur, data newData ){
  			// insert a new node into a ptrList 
  			// the ptrList oder decided by weight value
  			// first is biggest
  			if( cur == NULL ){									// create newNode   			
  				cur = new stdNode ;
  				cur->next = NULL ;
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
		
		void WriteOut( std::string num, int type ) {					// output a file of hashTable
			std::string write ;
			write = "pairs" ;
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

		void WriteOut( std::string num, char id[10] ) {					// output a file of hashTable
		
			for ( int gap = sp.size()/2 ; gap > 0 ; gap = gap / 2 ) {    // shell sort by id 
				for ( int i = gap ; i < sp.size() ; i ++ ) {
					for ( int q = i ; q >= gap && ( strcmp ( sp.at(q).endID, sp.at(q-gap).endID ) < 0 ) ; q-=gap )	
						swap( sp[q], sp[q-gap] ) ;
				} // for
			} // for
		
			std::string write ;
			write = "pairs" ;
	  		write.append( num ) ;
	  		write.append( ".dis" ) ;
	  		fp = fopen(  write.c_str(),"a" );	               // file open / out & append ( ios::out|ios::app )
	  		fprintf( fp, "\norigin: %s\n", id ) ;
	  		int order = 0 ;
	  		stdList *temp ;
	  		for( int i = 0 ; i < sp.size() ; i++ ){
	  			temp  = BinarySearchStdList( sp[i].endID ) ;
	  			order = temp->order ;
	  			fprintf( fp, "(%3d)  %s, %g  ", order, sp[i].endID, sp[i].weight ) ;
	  			if( (i+1) % 5 == 0 ) fprintf( fp, "\n" ) ;
			  } //for
			fprintf( fp, "\n" ) ;
			
      		fclose(fp) ;										// output file done
      		cout << "\n~~~ Shortest Distances are computed! ~~~  \n\n" ;
      		sp.clear() ;
		} // WriteOutAdj()

						
		void Print( int command ) {
			if( command == 1 ){
				printf( "~~~ Connected Components found ~~~ ") ;
				for( int i = 0 ; i < ccList.size() ; i++ ){	
					printf( "\n{%2d} Connected Component: size = %d\n    ", i+1, ccList[i].ccSize) ;
					cc *ccWalk = ccList[i].first ;
					for( int j = 1 ; ccWalk != NULL ; ccWalk = ccWalk->next, j++ ){
						printf( "  (%3d) %s", j, ccWalk->stdid ) ;
						if( j % 5 == 0  )
							printf(  "\n    " ) ;
					} // for
		    	} // for	
			}
			if( command == 2 ){
				for( int i = 0 ; i < adjList.size() ; i++ ){
					printf( "  %s", adjList[i].headid ) ;
					if( (i+1) % 5 == 0 ) printf("\n") ;	
		    	} // for
			}
						
		} // Print 

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
			ccL newcc ;	
			newcc.ccSize = 0 ;									// create a linked list for cc and initialize 
			newcc.first = new cc ;							// 配置記憶體 
			strcpy ( newcc.first->stdid, vp->headid );		// the linked list first data	
			newcc.first->next = NULL ;
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
				cur->next = NULL ;
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

/*******************************************************************************************
							Ex06 M1
*******************************************************************************************/

		void BuildMST(){
			vector<Edge> mst ;
			float sumOfWeight = 0;
			int i = 0, j = 0 ;
			for( i = 0 ; i < adjList.size() ; i++ ) 	// 初始化~~ya 
				adjList[i].visited = false ;
				
			for( i = 0 ; i < ccList.size() ; i++ ){		// 一組一組進行 
				stdList *vertex = BinarySearchStdList( ccList[i].first->stdid ) ;	// 獲得該組連通成分的第一個 
				if( vertex->visited == false ) { 								
					PrimeMST( mst, vertex, ccList[i].ccSize ) ;				//建立MST 
					
					for( j = 0, sumOfWeight = 0.0 ; j < mst.size() ; j++ )	// 加總該連通成分MST的權重 
						sumOfWeight = sumOfWeight + mst[j].weight ;
						
					printf("\nThe MST cost of connected component { %d} = %.4f \n", i+1, sumOfWeight ) ;
					
				}  // if
				
				mst.clear() ;	// 清空~給下一組連通成分使用 
				priorityQ.clear() ;
			} // for
			
		} // BuildMST
		
		void PrimeMST( vector<Edge> &mst, stdList *vp, int ccSize ){
			Edge newEdge ;
			stdList *up ;
			vp->visited = true ;					
			InsertMinEdge( vp ) ;				// 把"該點可以到達的點"的邊 放進priorityQ 
			int count = 0 ;	
			while( count < ccSize-1 ){
				up = PickMinEdge( newEdge ); 	// get 權重最小的邊(from visted v to unvisted u)
				up->visited = true ;			// 得到了當然要放手 將u點改成走訪過了 
				InsertMinEdge( up ) ;			// 把"該點可以到達的點"的邊 放進priorityQ 
				mst.push_back( newEdge ) ;
				count++ ; 
			} // while
		} // PrimeMST
			
		stdList* PickMinEdge( Edge &newEdge ){	// 拿取權重最小的邊 
			while( !priorityQ.empty() ){
				Edge temp = priorityQ.back() ;
				stdList *up = BinarySearchStdList( temp.endID ) ;
				if( ! up->visited ){			// 檢查有沒有visited過了
					newEdge = temp ;			// 還沒visited過，回傳邊並從priorityQ刪除 
					priorityQ.pop_back() ;
					return up ;
				} // if
				else
					priorityQ.pop_back() ;		// visited過了，把他刪除，讓priority最小的浮上來，重複執行 
			} // while
		} //  PickMinEdge
		
		void InsertMinEdge( stdList *vp ){		// 把該點可以到達的點 的 邊 放進priorityQ 
			Edge temp ;
			stdNode *walk = vp->first ;
			for( ; walk != NULL ; walk = walk->next )
				if( BinarySearchStdList( walk->stdid )->visited == false ){
					temp.EdgeInfo( vp->headid, walk->stdid, walk->weight ) ;
					InsertQ( temp ) ;
				} // if
		//	
		} // PushMinEdge
		
		void InsertQ( Edge temp ){		// 由大到小插入 
			int i = 0 ;
			if( priorityQ.empty() )
				priorityQ.push_back( temp ) ;
			else if( priorityQ.back().weight > temp.weight  ) 
				priorityQ.push_back( temp ) ;					
																		
			else{
				i = LowerBound( 0, priorityQ.size()-1 , temp.weight ) ;
				priorityQ.insert( priorityQ.begin()+i, temp ) ;
			}
		}  // PushInList
		
		int LowerBound( int low, int high, float target ){	// 回傳小於target的第一個sid 			
			if( low > high )
				return low ;
  			int mid = low + (high - low) / 2 ;					// 防止溢位
			if( priorityQ[mid].weight >= target )
				return LowerBound( mid+1, high, target ) ;
			else
				return LowerBound( low, mid-1, target ) ;
  			
		} // LowerBound(

/*******************************************************************************************
							Ex06 M2
*******************************************************************************************/
		
		void ShortestPath( char target[MAX_LENGTH] ){
			stdList *vp ;
			int i = 0, j = 0 ;
			for( i = 0 ; i < adjList.size() ; i++ )
				adjList[i].visited = false ;
			float weight_v_To_BeginID = 0.0 ;
			vp = BinarySearchStdList( target ) ;
			while( vp != NULL ){							// 將該點所有配對在sp中更新 
				DijkstraSP( target, vp, weight_v_To_BeginID ) ;
				vp = FindUnvisted_ShortestVertex( weight_v_To_BeginID ) ; // 在sp list中獲取權重最小的path和其path 
			} // while

		} // ShortestPath
		
		void DijkstraSP( char beginID[MAX_LENGTH], stdList *vp, float v_weight ){
			Edge temp ;
			Edge *up ;
			stdNode *walk = vp->first ;
 			vp->visited = true ;
			for( ; walk != NULL ; walk = walk->next ){		// 將點v的所有配對在sp更動(新增或更新) 
				if( sp.empty() ){							// sp為空，直接推入 
					temp.EdgeInfo( beginID, walk->stdid, walk->weight + v_weight ) ;
					sp.push_back(temp) ;
				}
														
				else if( SearchSP( walk->stdid ) == NULL && strcmp( beginID, walk->stdid )!= 0 ){  
					temp.EdgeInfo( beginID, walk->stdid, walk->weight + v_weight ) ;
					sp.push_back(temp) ;						// sp不為空，且此終點未出現過 
				} // if
				else if( SearchSP( walk->stdid ) != NULL ){		// sp中已存在該點	
					up = SearchSP( walk->stdid ) ;				// 找到該點 
					if( up->weight > (v_weight + walk->weight) )
						up->weight =  v_weight + walk->weight ;		// 比較哪條路徑比較短 						
				} // else if			
			} // for
		} // DijkstraSP
		
		stdList* FindUnvisted_ShortestVertex( float & weight_v_To_BeginID ){
			// shell sort by weight , small to big
			for ( int gap = sp.size()/2 ; gap > 0 ; gap = gap / 2 ) {    
				for ( int i = gap ; i < sp.size() ; i ++ ) {
					for ( int q = i ; q >= gap && ( sp.at(q).weight < sp.at(q-gap).weight ) ; q-=gap )	
						swap( sp[q], sp[q-gap] ) ;
				} // for
			} // for
			
			int i = 0 ;									// traversel to find unvisited and smallest-weight path 
			stdList *vp ;						
			while( i < sp.size() ){						
				vp = BinarySearchStdList( sp[i].endID ) ; // search the vertex in adjList which coresponding to endID 
				if( ! vp->visited )	{					  
					weight_v_To_BeginID = sp[i].weight ;  // check it is unvisited?
					return vp ;							  // traversal until find unvisited vertex
				}
				else
					i++ ;
			} // while
			return NULL ;
			
		}
		
		Edge* SearchSP( char targetEndID[10] ){			// 尋找再SP list中的對應點 
			for( int i = 0 ; i < sp.size() ; i++ ){
				if( strcmp( targetEndID, sp[i].endID ) == 0 )
					return &sp[i] ;
			}			
			return NULL ;
		} // BinarySearch

} ;
	
int main() {
	
	Assignment assignment ;
	int k ;
	std::string num;
	char id[MAX_LENGTH] ;
	std::string command = "87" ;     
	std::string searchTarget = "87" ; 
	while ( command != "0" ) {
		cout << "******************************************" << endl ;
		cout << "* On-machine Exercise                    *" << endl ;
		cout << "* Mission 1: Minimum Spanning Tree       *" << endl ;
		cout << "* Mission 2: Shortest Distances		  *" << endl ;
		cout << "******************************************" << endl ; 
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
				assignment.Print(1) ;			// print to screen
				assignment.WriteOut( num, 2 ) ;
				cout << "\n\n########################################################" << endl ;
				cout << "Mission 1: Minimum Spanning Tree   " << endl ;
				cout << "########################################################" << endl ;
				assignment.BuildMST() ;
				strcpy( id, "1") ;
				while ( strcmp( id ,"0" ) != 0) {
					cout << "\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;
					cout << "Mission 2: Shortest Distances  " << endl ;
					cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl ;
					assignment.Print(2) ;
					cout << "\nInput a student id from the above:   " << endl ;
					cin >> id ;
			
					if( assignment.BinarySearchStdList( id ) == NULL ){
						cout << endl << id <<  " does not exist!!! " << endl ;
					} // if
					else{
						assignment.ShortestPath( id ) ;
						assignment.WriteOut( num, id ) ;
					}
					cout << "\n[0]Quit or [Any other key]continue?  \n" ;
					cin >> id ;
					
				} // while
				num = "0" ;
			} // else
			
		} // while


		cout << "\n\nplease enter '0' or any other to continue" << endl ;
		assignment.Clear() ;
		cin >> command ; 
	}
} // main()





