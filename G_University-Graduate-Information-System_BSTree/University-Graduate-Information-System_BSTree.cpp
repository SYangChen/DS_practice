/*  資訊二甲 
 *  第 10 組 
 *  陳少洋
 *  10527130
 *  林亞吟
 *  10527132 
 */ 

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <cstdio>
#include <fstream> 
#include <vector> 
#include <algorithm>

using namespace std;
fstream fin ;                             // file input
fstream fout ;                            // file output



typedef struct Data {
	
	int schoolCode ;					  // 學校代碼 
	string schoolName ;					  // 學校名稱 
	string deptCode ;					  // 科系代碼
	string deptName ;					  // 科系名稱 
	string dayType1, dayType2 ;			  // 日間/進修別 
	string level1, level2 ;				  // 等級別 
	int stdnt ;							  // 學生人數
	int teacher ;						  // 教師人數
	int graduate ;						  // 畢業生人數			
	
}Data;

typedef struct TreeNode {
	
	Data data ;
	TreeNode *left ;
	TreeNode *right ;
	
}TreeNode;


class BSTree {
	
	private :
		
		TreeNode *root ;
		bool found ;
		int i ;
	
	public :
		
		BSTree() {
			root = NULL ;
			found = false ;
			i = 1 ;
		}
		
		// *************************************************
		
		TreeNode *GetRoot() {
			
			return root ;
			
		}
		
		// *************************************************
		
		void AddBySN( TreeNode *walk, Data data ) {
			
			if ( root == NULL ) {                                    // The data is the first one built on the tree
				root = new TreeNode ;                                // create the first node
				root->data = data ;                                  // remember to give the "NULL" value
				root->left = NULL ;
				root->right = NULL ;
				return ;
			}
			if ( data.schoolName < walk->data.schoolName ) {         // if the data is smaller than the current data
				if ( walk->left == NULL ) {                          // check the current left node is empty 
					walk->left = new TreeNode ;
					walk->left->data = data ;
					walk->left->left = NULL ;
					walk->left->right = NULL ;
				}
				else                                                 // or it might to check the next current left node ( recursion )
					return AddBySN( walk->left, data ) ;
			}
			else                                                     // if the data is bigger than or equal to the current data
				if ( walk->right == NULL ) {                         // check the current right node is empty 
					walk->right = new TreeNode ;
					walk->right->data = data ;
					walk->right->left = NULL ;
					walk->right->right = NULL ;
				}
				else                                                 // or it might to check the next current right node ( recursion )
					return AddBySN( walk->right, data ) ;
			
		}
		
		// *************************************************
		
		void AddByNG( TreeNode *walk, Data data ) {
			                                                         // same as the above function
			if ( root == NULL ) {
				root = new TreeNode ;
				root->data = data ;
				root->left = NULL ;
				root->right = NULL ;
				return ;
			}
			if ( data.graduate < walk->data.graduate ) {
				if ( walk->left == NULL ) {
					walk->left = new TreeNode ;
					walk->left->data = data ;
					walk->left->left = NULL ;
					walk->left->right = NULL ;
				}
				else
					return AddByNG( walk->left, data ) ;
			}
			else
				if ( walk->right == NULL ) {
					walk->right = new TreeNode ;
					walk->right->data = data ;
					walk->right->left = NULL ;
					walk->right->right = NULL ;
				}
				else
					return AddByNG( walk->right, data ) ;
			
		}
		
		// *************************************************
		
		int GetHeight( TreeNode *node ) {
			if ( node == NULL )                                                        // ( recursion ) base case
				return 0;

 			return 1 + max( GetHeight( node->left ), GetHeight( node->right ) ) ;      // choose the longest way
		}
		
		// *************************************************
		
		bool SearchSchool( string find, TreeNode *cur ) {
			
			if ( cur == NULL || ( found && find != cur->data.schoolName ) )                // base case ( recursion )
				return found ;
			else if ( find == cur->data.schoolName ) {                                 // found the same string
				printf( "[%1d]\t", i ) ;
				i++ ;
				cout << cur->data.schoolName << '\t' << cur->data.deptName << '\t'\
					 << cur->data.dayType1 << ' ' << cur->data.dayType2 << '\t'\
					 << cur->data.level1 << ' ' << cur->data.level2 << '\t'\
					 << cur->data.stdnt << '\t' << cur->data.teacher << '\t' 
					 << cur->data.graduate << endl ;
				found = true ;
				return SearchSchool( find, cur->right ) ;	                           // the same string will put at the right node
			}
			else if ( find < cur->data.schoolName ) 
				return SearchSchool( find, cur->left ) ;
			else 
				return SearchSchool( find, cur->right ) ;
		}
		
		// *************************************************
		
		bool SearchGraduate( int find, TreeNode *cur ) {
			
			if ( cur == NULL )                                                         // base case ( recursion )
				return found ;
			else if ( find <= cur->data.graduate ) {                                   // check the input number is smaller or equal to the current number
				found = true ;
				printf( "[%1d]\t", i ) ;
				i++ ;
				cout << cur->data.schoolName << '\t' << cur->data.deptName << '\t'\
					 << cur->data.dayType1 << ' ' << cur->data.dayType2 << '\t'\
					 << cur->data.level1 << ' ' << cur->data.level2 << '\t'\
					 << cur->data.stdnt << '\t' << cur->data.teacher << '\t' << cur->data.graduate << endl ;
				SearchGraduate( find, cur->left ) ;                                    // find the left node to the end
				return SearchGraduate( find, cur->right ) ;                            // than start to print all of the nodes at right
			}
			else 
				return SearchGraduate( find, cur->right ) ;                            // find the right node
			
		}
		
		// *************************************************
		
		void SetQQ() {
			found = false ;                                                            // reset
			i = 1 ;
		}
		
		
};

class Assignment {
	
	private :

		vector<Data> list ;
		BSTree treeSN, treeNG ; 
  		
	public :
		
		Assignment() {
			;
		}
  	
  		// *************************************************
  		
  		void Clear() {
  			
  			list.clear() ;
  			treeSN = BSTree() ;
  			treeNG = BSTree() ;
  			
		}
		
		// *************************************************
		
		void Reset() {
			
			treeSN.SetQQ() ;
			treeNG.SetQQ() ;
			
		}
  	
  		// *************************************************
  	
		void Read() {    		
		
			Data temp ;  
			string s ;             
			int i = 0 ;
	  		getline( fin, s ) ;							// first line will not input list
	  		getline( fin, s ) ;
	  		getline( fin, s ) ;
	  		while( fin >> i ) {
	  			temp.schoolCode = i ;
	  			fin >> temp.schoolName ;
	  			fin >> temp.deptCode ;
	  			fin >> temp.deptName ;
	  			fin >> temp.dayType1 >> temp.dayType2 ;
	  			fin >> temp.level1 >> temp.level2 ;
	  			fin >> temp.stdnt ;
	  			fin >> temp.teacher ;
	  			fin >> temp.graduate ;
	  			getline( fin, s ) ;					 
	  			list.push_back( temp ) ;
			} // while		
			
		} // Read()
	
		// *************************************************
		void Print() {
			
			printf( "\n" ) ;
			vector<Data>::iterator iter = list.begin();
			int i = 1 ;
			for( iter, i ; iter != list.end() ; ++iter, i++ ) {
				 	printf( "[%1d]\t", i ) ;
					cout << iter->schoolName << '\t' << iter->deptName << '\t'\
					<< iter->dayType1 << ' ' << iter->dayType2 << '\t'\
					<< iter->level1 << ' ' << iter->level2 << '\t'\
					<< iter->stdnt << '\t' << iter->teacher << '\t' << iter->graduate << endl ;   	
			} // for

		} // Print 
	
		// *************************************************
	/*
		void Write( int type ) {												
			
			
		} // Write()
	*/
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
	/*
		void WriteOut( std::string num ) {
		
			std::string write ;
			write = "87" ;
	  		write.append( num ) ;
	  		write.append( ".txt") ;
	  		fout.open( write.c_str(), ios::out );               // file open / out & append ( ios::out|ios::app )
      		// fout << "Hello!! success" << endl;               // output data in file
      		Write( type ) ;
      		fout.close() ;
      		cout << "\nFile build : " << fout << endl ;
      		
		} // WriteOut()
	*/
		// *************************************************
		
		void AddNodes() {
			
			for ( int i = 0 ; i < list.size() ; i++ ) 
				treeSN.AddBySN( treeSN.GetRoot(), list[i] ) ;
			for ( int i = 0 ; i < list.size() ; i++ ) 
				treeNG.AddByNG( treeNG.GetRoot(), list[i] ) ;
			cout << "\nTree heights :" << endl 
				 << "{ School Name } = " << treeSN.GetHeight( treeSN.GetRoot() ) << endl 
				 << "{ Number of Graduates } = " << treeNG.GetHeight( treeNG.GetRoot() ) << endl ;
				 
		}
		
		// *************************************************
		
		bool Search( string findSchool, int findGraduate, int type ) {
			
			if ( type == 1 )
				return treeSN.SearchSchool( findSchool, treeSN.GetRoot() ) ;
			else if ( type == 2 )
				return treeNG.SearchGraduate( findGraduate, treeNG.GetRoot() ) ;
			else
				return false ;
				
		}
		
		
		
};


	
int main() {
	
	Assignment list ;                          	
	std::string num ;
	int command ;      
	string findSchool ;
	int findGraduate = -1 ;  
	cout << "\n*** University Graduate Information System ***\n"
		 << "* 0. Quit                                    *\n"
		 << "* 1. Create Two Binary Search Trees          *\n"
		 << "* 2. Search by School Name                   *\n"
		 << "* 3. Search by Number of Graduates           *\n"
		 << "----------------------------------------------\n"
		 << "Input a command : " ;
	cin >> command ;
	while ( command != 0 ) {
		if ( command == 1 ) {
			
			list.Clear() ;
			num.clear() ;                                    // content clear
			cout << "Input a file number :" ;	
			cin >> num ;
	    	if ( !list.LoadIn( num ) )
				cout << "Input file does not exist, please try again!" << endl ;
			else  {
				list.Print() ;
				list.AddNodes() ;
        	}
        	
        } // end if
		else if ( command == 2 ) {
			
			cout << "Input a school name : " ;
			cin >> findSchool ;
			cout << "\nSearch results:" << endl ;
			if ( !list.Search( findSchool, findGraduate, 1 ) )
				cout << "Couldn't find the school, please try again!" << endl ;
			
			findSchool.clear() ;
			list.Reset() ;
			
		} // end else if
    	else if ( command == 3 ) {
    		
    		cout << "Input the number of graduates : " ;
			cin >> findGraduate ;
			cout << "\nSearch results:" << endl ;
			if ( !list.Search( findSchool, findGraduate, 2 ) )
				cout << "Couldn't find the number of graduates, please try again!" << endl ;
				
			findGraduate = -1 ;
			list.Reset() ;
			
		}
		else
			cout << "Couldn't find command, please try again!" << endl ;
			
		cout << "\n*** University Graduate Information System ***\n"
			 << "* 0. Quit                                    *\n"
			 << "* 1. Create Two Binary Search Trees          *\n"
			 << "* 2. Search by School Name                   *\n"
			 << "* 3. Search by Number of Graduates           *\n"
			 << "----------------------------------------------\n"
			 << "Input a command : " ;
		cin >> command ;
	} // end while
  
} // main()





