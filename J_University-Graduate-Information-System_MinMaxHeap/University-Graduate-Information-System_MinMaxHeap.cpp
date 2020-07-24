#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream> 
#include <vector> 
#include <cmath>

using namespace std;
fstream fin ;                             // file input
fstream fout ;                            // file output



typedef struct Data {
	
	int schoolCode ;					  // 學校代碼 
	string schoolName ;					  // 學校名稱    !!!
	string deptCode ;					  // 科系代碼 
	string deptName ;					  // 科系名稱    !!!
	string dayType ;					  // 日間/進修別 !!!
	string level ;						  // 等級別      !!!
	string stdnt ;						  // 學生人數
	string teacher ;					  // 教師人數
	int graduate ;						  // 畢業生人數			
	
}Data;

typedef struct Item {
	
	int num ;                // stream number 
	int graduate ;
	
}Item;

class Heap {
	
	private :
		
		Item *heapArray ;
		int heapSize ;
	
	public :
		
		Heap( int size ) {
			heapArray = new Item[size] ;        // dynamic array
			heapSize = 0 ;
		} 
		
		// *************************************************
		
		void Swap( Item &a, Item &b ) {
			Item temp = a ;
			a = b ;
			b = temp ;
		}
		
		// *************************************************
		
		void MMHeapInsert( Item newItem, int size ) {
			heapArray[size] = newItem ;
			int cur = size ;                                          // current node
			int trace = ( cur-1 )/2 ;								  // current node's parent
			int level = log(size+1)/log(2) ;                          // level = 0 -> min     level = 1 -> max
			level = level%2 ;
			if ( level && heapArray[cur].graduate < heapArray[trace].graduate ) {
				Swap( heapArray[cur], heapArray[trace] ) ;
				cur = trace ;
				level-- ;
			}														  // compare with parent node
			if ( !level && heapArray[cur].graduate > heapArray[trace].graduate) {
				Swap( heapArray[cur], heapArray[trace] ) ;
				cur = trace ;
				level++ ;
			}
			trace = ( cur-3 )/4 ;
			if ( level ) {
				while (( cur > 2 ) && ( heapArray[cur].graduate > heapArray[trace].graduate )) {
					Swap( heapArray[cur], heapArray[trace] ) ;
					cur = trace ;
					trace = ( cur-3 )/4 ;
				}
			}														  // compare  with grandparent node
			else {
				while (( cur > 2 ) && ( heapArray[cur].graduate < heapArray[trace].graduate )) {
					Swap( heapArray[cur], heapArray[trace] ) ;
					cur = trace ;
					trace = ( cur-3 )/4 ;
				}
			}
			heapSize++ ;
		}
		
		// *************************************************
		
		int MMHeapDelMax() {
			// swap the biggest one by bottom
			// than trickle down ( max )
			int DelNum ;
			if ( heapSize == 1 ) DelNum = heapArray[0].num ;                              // delete root 
			else if ( heapSize == 2 || heapArray[1].graduate >= heapArray[2].graduate ) {
				// cout << "DELETEMAX" << " " << heapArray[1].num << endl ;
				DelNum = heapArray[1].num ;
				heapArray[1] = heapArray[heapSize-1] ;
				TrickleDownMax( 1 ) ;
			}
			else {
				// cout << "DELETEMAX" << " " << heapArray[2].num << endl ;
				DelNum = heapArray[2].num ;
				heapArray[2] = heapArray[heapSize-1] ;
				TrickleDownMax( 2 ) ;
			}
			heapSize-- ;
			return DelNum ;
		}
		
		// *************************************************
		
		void TrickleDownMax( int cur ) {
			int child = BiggestChild( cur ) ;
			int grandChild = BiggestGrChild( cur ) ;
			if ( child != -1 && heapArray[child].graduate > heapArray[cur].graduate )     // compare with child
				Swap( heapArray[child], heapArray[cur] ) ;
			while ( grandChild != -1 && heapArray[grandChild].graduate > heapArray[cur].graduate ) {
				Swap( heapArray[grandChild], heapArray[cur] ) ;                           // compare with grandchild in loop
				cur = grandChild ;
				child = BiggestChild( cur ) ;
				if ( child != -1 && heapArray[child].graduate > heapArray[cur].graduate ) 
					Swap( heapArray[child], heapArray[cur] ) ;                            // compare with child in loop
				grandChild = BiggestGrChild( cur ) ;
			}
			
			child = BiggestChild( cur ) ;
			if ( child != -1 && heapArray[child].graduate > heapArray[cur].graduate )     // check child node
				Swap( heapArray[child], heapArray[cur] ) ;
		}
		
		// *************************************************
		
		int BiggestChild( int cur ) {
			// find biggest child
			if ( cur*2+1 > heapSize-1 )
				return -1 ;
			else if ( cur*2+2 > heapSize-1 || heapArray[cur*2+1].graduate >= heapArray[cur*2+2].graduate ) // choose left? right? 
				return cur*2+1 ;
			else
				return cur*2+2 ;
		}
		
		// *************************************************
		
		int BiggestGrChild( int cur ) {
			// find biggest grandchild
			if ( cur*4+3 > heapSize-1 )
				return -1 ;
			int big = cur*4+3 ;
			for ( int i = 4 ; i < 7 && cur*4+i < heapSize ; i++ ) {
				if ( heapArray[big].graduate < heapArray[cur*4+i].graduate )
					big = cur*4+i ;
			}
			return big ;
		}
		
		// *************************************************
		
		void HeapPrint() {
			int size = heapSize ;
			cout << "root : [" << heapArray[0].num << "] " << heapArray[0].graduate << endl ;
			cout << "bottom : [" << heapArray[size-1].num << "] " << heapArray[size-1].graduate << endl ;
			size = log(size)/log(2) ;                                 // log2(x)
			size = pow( 2, size ) ;                                   // 2^x
			cout << "leftmost bottom : [" << heapArray[size-1].num << "] " << heapArray[size-1].graduate << endl ;
		}
	
};

class Assignment {
	
	private :

		vector<Data> list ;
		vector<Data> modifiedList ;
		Heap *heap ;
		 
  		
	public :
		
		Assignment() {
			;
		}
		
		// *************************************************
  	
  		void Clear() {
  			list.clear() ;
  			modifiedList.clear() ;	
		}
		
		// *************************************************
		
		int getMSize() {
			return modifiedList.size() ;
		}
		
		// *************************************************
  	
		void Read() {
		
			Data temp ;  
			string s ;  
			string tempstring ;  
			char c ;         
			int i = 0 ;
		  	getline( fin, s ) ;							              // first line will not input list
		  	getline( fin, s ) ;
	  		getline( fin, s ) ;
	  		while( getline( fin, s ) ) {
	  			for ( i = 0 ; s[i] != '\t' ; i++ ) 
	  				tempstring = tempstring+s[i] ;
				temp.schoolCode = atoi( tempstring.c_str() ) ;        // std::stoi require newest compiler
				for ( i++ ; s[i] != '\t' ; i++ ) 
					temp.schoolName = temp.schoolName+s[i] ;
				for ( i++ ; s[i] != '\t' ; i++ )
					temp.deptCode = temp.deptCode+s[i] ;
				for ( i++ ; s[i] != '\t' ; i++ )
					temp.deptName = temp.deptName+s[i] ;
				for ( i++ ; s[i] != '\t' ; i++ )
					temp.dayType = temp.dayType+s[i] ;
				for ( i++ ; s[i] != '\t' ; i++ )
					temp.level = temp.level+s[i] ;
				for ( i++ ; s[i] != '\t' ; i++ )
					temp.stdnt = temp.stdnt+s[i] ;
				for ( i++ ; s[i] != '\t' ; i++ )
					temp.teacher = temp.teacher+s[i] ;
				tempstring.clear() ;
				for ( i++ ; s[i] != '\t' ; i++ )
					tempstring = tempstring+s[i] ;
				if ( !tempstring.empty() ) {
					temp.graduate = atoi( tempstring.c_str() ) ;
					list.push_back( temp ) ;                          // if the graduate number is a empty blank
				}                                                     // than ignore this data
				
		  		temp.schoolName.clear() ;
		  		temp.deptCode.clear() ;
		  		temp.deptName.clear() ;
	  			temp.dayType.clear() ;
	  			temp.level.clear() ;
	  			temp.stdnt.clear() ;
	  			temp.teacher.clear() ;
			} // while		
			
		} // Read()
	
		// *************************************************
		
		void Print() {
			
			cout << "*** There are " << modifiedList.size() << " matched records, listed as below:" << endl ;
			for ( int i = 0 ; i < modifiedList.size() ; i++ ) {
				cout << "[" << i+1 << "] " << modifiedList[i].schoolName << modifiedList[i].deptName << ",\t"\
					 << modifiedList[i].dayType << ",\t" << modifiedList[i].level << ",\t" << modifiedList[i].graduate << endl ;
			}
			cout << "*******************************************************************\n" << endl ;
		
		} // Print 
	
		// *************************************************
	
		bool LoadIn( std::string num ) {
	  		// load in by file
			std::string read = "input";           
      		read.append( num ) ;
  	  		read.append( ".txt") ;
  	  		fin.open( read.c_str(), ios::in );                    // file open / read 
  	  		if ( !fin )
  	    		return false ;
  	  		else {
        		Read() ;
				// "getline" or "get" here (input)
				fin.close() ;
  	    		return true ;
  	  		} // end else 
  	  
		} // LoadIn()
	
		// *************************************************
	
		void WriteOut( std::string num ) {
		
			std::string write ;
			write = "output" ;
	  		write.append( num ) ;
	  		write.append( "txt" ) ;
	  		fout.open( write.c_str(), ios::out );               // file open / out & append ( ios::out|ios::app )
      		// fout << "Hello!! success" << endl;               // output data in file
      		fout.close() ;
      		cout << "\nFile build : " << fout << endl ;
      		
		} // WriteOut()
	
		// *************************************************
		
		void Pick( std::string sName, std::string dName, std::string dType, std::string level ) {
			
			std::size_t found ;
			for ( int i = 0 ; i < list.size() ; i++ ) {
				found = list[i].schoolName.find( sName ) ;
				if ( sName == "*" || found != std::string::npos ) {
					found = list[i].deptName.find( dName ) ;
					if ( dName == "*" || found != std::string::npos ) {
						found = list[i].dayType.find( dType ) ;
						if ( dType == "*" || found != std::string::npos ) {
							found = list[i].level.find( level ) ;
							if ( level == "*" || found != std::string::npos )
								modifiedList.push_back( list[i] ) ;             // all matched
						}
					} 
				}
			}
		}
		
		// *************************************************
		
		void BuildMMHeap() {
			heap = new Heap( modifiedList.size() ) ;
			for ( int i = 0 ; i < modifiedList.size() ; i++ ) {
				Item newItem ;
				newItem.num = i+1 ;                                   // stream number
				newItem.graduate = modifiedList[i].graduate ;
				heap->MMHeapInsert( newItem, i ) ;
			}
			heap->HeapPrint() ;
		}
		
		// *************************************************
		
		void DeleteKnodes( int k ) {
			int streamNum ;
			for ( int i = 0 ; k > i ; i++ ) {
				streamNum = heap->MMHeapDelMax() ;
				cout << "Top " << i+1 << ": [" << streamNum << "]\t" \
					 << modifiedList[streamNum-1].schoolName << modifiedList[streamNum-1].deptName << ",\t"\
					 << modifiedList[streamNum-1].dayType << ",\t" << modifiedList[streamNum-1].level \
					 << ",\t" << modifiedList[streamNum-1].graduate << endl ; 
			}
				
		}
	
	}; 


	
int main() {
	
	Assignment assignment ;
	int k ;
	std::string num ;
	std::string schoolName ;
	std::string deptName ;
	std::string dayType ;
	std::string level ;
	std::string command = "87" ;     
	while ( command != "0" ) {
		cout << "*************************************************" << endl ;
		cout << " On-machine Exercise                            *" << endl ;
		cout << " Mission 1: Construct a min-max heap            *" << endl ;
		cout << " Mission 2: Find top-K maximums by min-max heap *" << endl ;
		cout << "*************************************************" << endl ; 
		cout << "Input the file number[0]Quit : " << endl ;
		cin >> num ;
		while ( num != "0" ) {
			if ( !assignment.LoadIn( num ) ) {
				cout << "No such file, please enter again!" << endl << "Input the file number[0]Quit : " << endl ;
				cin >> num ;
				if ( num == "0" ) return 0 ;
			}
			else num = "0" ;
		}
		cout << "Enter a keyword of 學校名稱: [*]for all" << endl ;
		getline( cin, num ) ;   // read trash ( \n )
		getline( cin, schoolName ) ;
		cout << "Enter a keyword of 科系名稱: [*]for all" << endl ;
		getline( cin, deptName );
		cout << "Enter a keyword of 日間/進修別: [*]for all" << endl ;
		getline( cin, dayType ) ;
		cout << "Enter a keyword of 等級別: [*]for all" << endl ;
		getline( cin, level ) ;
		assignment.Pick( schoolName, deptName, dayType, level ) ;
		assignment.Print() ;
		system("pause") ;
		cout << "\n========================================================" << endl ;
		cout << "Mission 1: Build a Min-Max Heap from the Selected Data" << endl ;
		cout << "========================================================\n" << endl ;
		cout << "<Min-Max Heap>" << endl ;
		if ( assignment.getMSize() == 0 )
			cout << "###  There is nothing mathced!  ###" << endl ;
		else {
			assignment.BuildMMHeap() ;
			cout << "\nEnter the value of 'K' items delete from Min-Max Heap." << endl ;
			cout << "[1~" << assignment.getMSize() << "] K=?????" << endl ;
			cin >> k ;
			cout << "\n========================================================" << endl\
				 << "Mission 2: Top-K maximums from min-max heap  (K=26)" << endl\
				 << "========================================================\n" << endl ; 
			if ( k > assignment.getMSize() )
				assignment.DeleteKnodes( assignment.getMSize() ) ;
			else
				assignment.DeleteKnodes( k ) ;
		}
		cout << "\n[0]Quit or [Any other]continue?" << endl ;
		cin >> command ;
		assignment.Clear() ;
	}
} // main()





