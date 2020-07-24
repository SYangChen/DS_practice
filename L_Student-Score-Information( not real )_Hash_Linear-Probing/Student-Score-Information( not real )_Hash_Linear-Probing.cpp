/*  資訊二甲 
 *  第 12 組 
 *  陳少洋
 *  10527130
 *  林亞吟 
 *  10527132 
 */ 

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



typedef struct Student {
	
	char sid[10] = {0};					  
	char sname[10] = {0};				  
	unsigned char score1  ;
	unsigned char score2  ;
	unsigned char score3  ;
	unsigned char score4  ;
	unsigned char score5  ;
	unsigned char score6  ;
	float average ;
	
}Student;

typedef struct HTData {
	
	char sid[10] = {0};					  
	char sname[10] = {0};				  
	unsigned char score1  ;
	unsigned char score2  ;
	unsigned char score3  ;
	unsigned char score4  ;
	unsigned char score5  ;
	unsigned char score6  ;
	float average ;
	int hvalue = -1 ;
	
}HTData;

	
class Assignment {
	
	
	
	private :
		FILE *pf;
		vector<Student> list ;
		vector<HTData> hT ;
		float suc_comparison = 0.0 ;
		float unsuc_comparison = 0.0 ;
		 
  		
	public :
		
		Assignment() {
			;
		}
		
		
		
		// *************************************************
  	
  		void Clear() {
  			list.clear() ;
			hT.clear() ;
			suc_comparison = 0.0 ;
		 	unsuc_comparison = 0.0 ;
		}
		
		// *************************************************
  	
		void Read() {
		
			Student temp ;  
			string s ;  
			string tempstring ;  	
			char c ;         
			int i = 0, j = 0, tempint = 0 ;
	  		while( getline( fin, s ) && s != "\n" ) {
	  			for ( i = 0, j = 0 ; s[i] != '\t' ; i++, j++ ) 
	  				temp.sid[j] = s[i] ;

				for ( i++, j = 0 ; s[i] != '\t' ; i++, j++ ) 
					temp.sname[j] = s[i] ;
					

				for ( i++ ; s[i] != '\t' ; i++ )
					tempstring = tempstring+s[i] ;
				tempint = atoi( tempstring.c_str() ) ;
				temp.score1 = (unsigned char)tempint ;	
				tempstring.clear() ;	
			
				for ( i++ ; s[i] != '\t' ; i++ )
					tempstring = tempstring+s[i] ;
				tempint = atoi( tempstring.c_str() ) ;
				temp.score2 = (unsigned char)tempint ;	
				tempstring.clear() ;
				
								
				for ( i++ ; s[i] != '\t' ; i++ )
					tempstring = tempstring+s[i] ;
				tempint = atoi( tempstring.c_str() ) ;
				temp.score3 = (unsigned char)tempint ;	
				tempstring.clear() ;
				
				for ( i++ ; s[i] != '\t' ; i++ )
					tempstring = tempstring+s[i] ;
				tempint = atoi( tempstring.c_str() ) ;
				temp.score4 = (unsigned char)tempint ;	
				tempstring.clear() ;
				
				for ( i++ ; s[i] != '\t' ; i++ )
					tempstring = tempstring+s[i] ;
				tempint = atoi( tempstring.c_str() ) ;
				temp.score5 = (unsigned char)tempint ;	
				tempstring.clear() ;
				
				for ( i++ ; s[i] != '\t' ; i++ )
					tempstring = tempstring+s[i] ;
				tempint = atoi( tempstring.c_str() ) ;
				temp.score6 = (unsigned char)tempint ;	
				tempstring.clear() ;
				
				for ( i++ ; i < s.size() ; i++ ) 
					tempstring = tempstring+s[i] ;
				temp.average = atof( tempstring.c_str() ) ;	
				tempstring.clear() ;
				
				list.push_back( temp ) ;
				memset(temp.sid, '\0', sizeof(temp.sid)) ;
				memset(temp.sname, '\0', sizeof(temp.sname)) ;
	  			s.clear() ;
			} // while		
			
		} // Read()
	
		// *************************************************
		
		
		void PutIntoTable( HTData data, int index ){
			suc_comparison++ ;
			if( hT[index].hvalue == -1 ) 				// 這個欄位還沒存過資料 
				hT[index] = data ;
			else {										// linear Probe
				if( index  ==  hT.size()-1 )			// if the index is the last of the bottom
					PutIntoTable( data, 0 ) ;			// 從頭開始probe 
				else
					PutIntoTable( data, index+1 ) ;		
			}
				
		}
		
		
		int HashFunction( char key[10] ){			// culculate the hash value of id 
			int i = 0 ; 
			unsigned long long hvalue = 1 ;
			for( i = 0 ; key[i] != 0 ; i++ )
				hvalue = hvalue * key[i] ;
			hvalue = hvalue % hT.size() ; 
			return hvalue ;
			
		}
		
		void ReadBin() {									// read binay file
			int i = 0 ;
			char c[2] ;
			HTData tempData ;
			while( i < list.size() ) {
				fread( &tempData.sid, 10, 1, pf ) ;
				fread( &tempData.sname, 10, 1, pf ) ;
				fread( &tempData.score1, 1, 1, pf ) ;
				fread( &tempData.score2, 1, 1, pf ) ;
				fread( &tempData.score3, 1, 1, pf ) ;
				fread( &tempData.score4, 1, 1, pf ) ;
				fread( &tempData.score5, 1, 1, pf ) ;
				fread( &tempData.score6, 1, 1, pf ) ;
				fread( &c[0], 2, 1, pf ) ;
				fread( &tempData.average, 4, 1, pf ) ;
				tempData.hvalue = HashFunction( tempData.sid ) ;		// get hash value
				PutIntoTable( tempData, tempData.hvalue ) ;				// put data into hashtable
				i++ ;													// next data


			} // while
			
		} // readBin
		
		
		// *************************************************
	
		bool LoadIn( std::string num ) {
	  		// load in by file
			std::string read = "input";           
      		read.append( num ) ;
  	  		read.append( ".txt") ;
  	  		fin.open( read.c_str(), ios::in );                  // file open / read 
  	  		if ( !fin )											// not find file
  	    		return false ;
  	  		else {												// find file then read
        		Read() ;
				fin.close() ;
  	    		return true ;
  	  		} // end else 
  	  
		} // LoadIn()
	
		// *************************************************
	
		void WriteOutBin( std::string num ) {
		
			std::string write ;
			write = "input" ;
	  		write.append( num ) ;
	  		write.append( ".bin" ) ;
	  		pf = fopen(  write.c_str(),"wb+" );					 // create file in binary mode
	  		fwrite( &list[0],32,list.size(),pf) ;				 // output data in file		  
      		fclose(pf) ;
      		
		} // WriteOut()
	
		// *************************************************
		
		void LoadInBin( std::string num ) {						// load file in binary mode
			std::string read = "input";           
      		read.append( num ) ;
  	  		read.append( ".bin") ;
  	  		pf = fopen(  read.c_str(),"rb" );					// file open / read
  	  		ReadBin() ;
			fin.close() ;	                
			
  	  
		} // LoadIn()
		
		void WriteOutTab( std::string num ) {					// output a file of hashTable
			std::string write ;
			write = "input" ;
	  		write.append( num ) ;
	  		write.append( ".tab" ) ;
	  		fout.open( write.c_str(), ios::out );               // file open / out & append ( ios::out|ios::app )

      		fout << " --- Hash Table --- by Linear probing" << endl ;  // write all data
			for ( int i = 0 ; i < hT.size() ; i++ ) {				
				fout << "[" << i << "] "  ;
				
				if( hT[i].hvalue == -1 )
					fout << endl ;
					
				else{
					fout << "         "<< hT[i].hvalue << ",   " \
						 << hT[i].sid<< ",     " << hT[i].sname << ",      "\
					 	 << hT[i].average << endl ;
				}
			}

      		fout.close() ;										// output file done
      		

		} // WriteOut()
			
		// *************************************************	
			
		void Print() {
			
			cout << "~~ A binary file has been successfully created! ~~" << endl ;
			for ( int i = 0 ; i < list.size() ; i++ ) {
				cout << "[" << i+1 << "] " << list[i].sid<< ", " << list[i].sname << ",\t"\
					 << (int)list[i].score1 << "\t" <<  (int)list[i].score2 << "\t" \
					 << (int)list[i].score3 << "\t" <<  (int)list[i].score4 << "\t" \
					 << (int)list[i].score5 << "\t" <<  (int)list[i].score6 << "\t" \
					 << list[i].average << endl ;
			}

		
		} // Print 
		
		void PrintComparison() {
			
			// these(comparison aver.) will output in screen
			cout << "~~ The hash table has been successfully created! ~~    \n" ;
			CulculateComparison();
      		cout << "unsuccessful search: " << unsuc_comparison / hT.size() << " comparisons on average\n" << endl ;
      		cout << "successful search: " << suc_comparison / list.size() << "comparisons on average\n" << endl ;
		} // Print 
		
		void CulculateComparison(){
			int count = 0 ;
			for( int i = 0 ; i < hT.size() ; i++ ){					// from first to last comparison
				if( hT[i].hvalue != -1 ){							// base case : compare util the coulumm is "empty" NOT end
					count = 0 ;										
					for( int j = i  ; hT[j].hvalue != -1 ; j++ ){
						count++ ;
						if( j ==  hT.size()-1 )						// if this column is the last of the table
							j = -1 ;								// go back to the first of table then compare										
					}
				unsuc_comparison = unsuc_comparison + count ; 		// add into sum of not_exist_value comparisons
				}
				 // if

			} //for
		}
		
		// *************************************************
		
		void BuildTable(){											// table(vector) is built
			int tableSize = list.size() * 1.2 ;						// just need to resize 
			tableSize = FindNextPrime( list.size() * 1.2 ) ;		// to get the size
			hT.resize(tableSize) ;
		} // BuildTable

		// *************************************************
		
		int FindNextPrime( int n ) {				// find the smallest Prime greater than n
			bool found = false ;
			while ( found == false ){
				n++ ;
				if( IsPrime(n) == true )
					found = true ;
			}
			return n ;
			
		} // FindNextPrime
		
		bool IsPrime( int n ){						// Is n a Prime ? 
			
			
			for( int i=2 ; i <= n/2 ; i++ ) {
   		    	if( n % i == 0 )
           			return false ;
        	}	
     		
     		return true;

		} // IsPrime 
	
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
		cout << "*  Mission 1: Make a binary file         *" << endl ;
		cout << "* Mission 2: Hashing with Linear probing *" << endl ;
		cout << "******************************************" << endl ; 
		cout << "########################################################" << endl ;
		cout << "Mission 1: Transform a text file into a binary file " << endl ;
		cout << "########################################################" << endl ;
		cout << "Input the file number[0]Quit : " << endl ;
		cin >> num ;
		while ( num != "0" ) {
			if ( !assignment.LoadIn( num ) ) {
				cout << "No such file, please enter again!" << endl << "Input the file number[0]Quit : " << endl ;
				cin >> num ;
				if ( num == "0" ) return 0 ;
			}
			else {
				assignment.Print() ;
				assignment.WriteOutBin(num);
				cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;
				cout << "Mission 2: Build a hash table by linear probing" << endl ;
				cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl ;
				assignment.BuildTable() ;
				assignment.LoadInBin(num) ;
				assignment.WriteOutTab(num) ;
				//assignment.CulculateComparison() ;
				assignment.PrintComparison() ;
				num = "0" ;
			}
			
		}


		cout << "please enter '0' or any other to continue" << endl ;
		assignment.Clear() ;
		cin >> command ; 
	}
} // main()





