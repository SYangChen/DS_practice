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
	
	int num ;
	int graduate ;
	
}Item;

class Heap {
	
	private :
		
		Item *heapArray ;
	
	public :
		
		Heap( int size ) {
			heapArray = new Item[size] ;
		} 
		
		void HeapInsert( Item newItem, int size ) {
			heapArray[size] = newItem ;
			int cur = size ;                                          // current node
			int parent = ( cur-1 )/2 ;								  // current node's parent
			while (( parent >= 0) && ( heapArray[cur].graduate > heapArray[parent].graduate )) {
				Item temp = heapArray[parent] ;
				heapArray[parent] = heapArray[cur] ;                  // swap
				heapArray[cur] = temp ;
				cur = parent ;
				parent = ( cur-1 )/2 ;
			}
			// size++ ;
		}
		
		void HeapPrint( int size ) {
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
  	
  		void Clear() {
  			modifiedList.clear() ;	
		}
		
		int getMSize() {
			return modifiedList.size() ;
		}
  	
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
		
		void BuildHeap() {
			heap = new Heap( modifiedList.size() ) ;
			for ( int i = 0 ; i < modifiedList.size() ; i++ ) {
				Item newItem ;
				newItem.num = i+1 ;                                   // stream number
				newItem.graduate = modifiedList[i].graduate ;
				heap->HeapInsert( newItem, i ) ;
			}
			heap->HeapPrint( modifiedList.size() ) ;
		}
	
	}; 


	
int main() {
	
	Assignment assignment ;
	std::string num ;
	std::string schoolName ;
	std::string deptName ;
	std::string dayType ;
	std::string level ;
	std::string command = "87" ;     
	cout << "Input the file number: 101, 102, ... [0]Quit" << endl ;
	cin >> num ;
	if ( num == "0" ) return 0 ;
	while ( num != "0" ) {
		if ( !assignment.LoadIn( num ) ) {
			cout << "No such file, please enter again!" << endl << "Input the file number: 101, 102, ... [0]Quit" << endl ;
			cin >> num ;
			if ( num == "0" ) return 0 ;
		}
		else num = "0" ;
	}
	while ( command != "0" ) {
		cout << "\n\n************************************************************\n" ;
		cout << "*** Mission One: Select Matched Records from a Text File ***\n" ;
		cout << "************************************************************\n" ;
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
		cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;
		cout << "@@@ Mission Two: Build a Max Heap from the Selected Data @@@" << endl ;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl ;
		cout << "<Max Heap>" << endl ;
		if ( assignment.getMSize() == 0 )
			cout << "###  There is nothing mathced!  ###" << endl ;
		else
			assignment.BuildHeap() ;
		
		cout << "\n[0]Quit or [Any other]continue?" << endl ;
		cin >> command ;
		assignment.Clear() ;
	}
} // main()





