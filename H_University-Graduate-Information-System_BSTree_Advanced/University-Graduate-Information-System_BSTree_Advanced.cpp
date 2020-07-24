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
	string dayType1 ;					  // 日間/進修別 
	string level1 ;						  // 等級別 
	string stdnt ;						  // 學生人數
	string teacher ;					  // 教師人數
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
					 << cur->data.dayType1 << '\t'\
					 << cur->data.level1 << '\t'\
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
					 << cur->data.dayType1 << '\t'\
					 << cur->data.level1 << '\t'\
					 << cur->data.stdnt << '\t' << cur->data.teacher << '\t' << cur->data.graduate << endl ;
				SearchGraduate( find, cur->left ) ;                                    // find the left node to the end
				return SearchGraduate( find, cur->right ) ;                            // than start to print all of the nodes at right
			}
			else 
				return SearchGraduate( find, cur->right ) ;                            // find the right node
			
		}
				// *************************************************
		
		bool IsSame( TreeNode *a, TreeNode *b ){
			if( a->data.schoolName == b->data.schoolName && a->data.deptName == b->data.deptName )
				if( a->data.stdnt == b->data.stdnt && a->data.teacher == b->data.teacher )
					if( a->data.dayType1 == b->data.dayType1 && a->data.level1 == b->data.level1 )
				    	if( a->data.graduate == b->data.graduate )
				    		return true ;
			
			return false ;
		}
		
		// ********************************************
		
		void Remove_graduate( BSTree &treeNG, TreeNode *deleteNode, TreeNode *treeNG_cur, TreeNode *treeNG_pre ) {

			if( treeNG_cur->data.graduate == deleteNode->data.graduate ) {					 // NGtree must have the same node
				if ( IsSame( treeNG_cur, deleteNode ) )  {
					treeNG.DeleteNode( treeNG_cur, treeNG_pre ) ;
				}
				else 
					Remove_graduate( treeNG, deleteNode, treeNG_cur->right, treeNG_cur ) ;	 // because the same graduates will be right node
			}
			else if( treeNG_cur->data.graduate > deleteNode->data.graduate )
				Remove_graduate( treeNG, deleteNode, treeNG_cur->left, treeNG_cur ) ;
			else if( treeNG_cur->data.graduate < deleteNode->data.graduate )
				Remove_graduate( treeNG, deleteNode, treeNG_cur->right, treeNG_cur ) ;
		}
		
		bool DeleteSchool( string del, TreeNode *cur, TreeNode *pre, BSTree &treeNG ) {  
			if ( cur == NULL || found && del != cur->data.schoolName )            		    // base case ( recursion )
				return found ;	
			else if ( del == cur->data.schoolName ) {                              		    // found the same string
				printf( "[%1d]\t", i ) ;
				i++ ;
				cout << cur->data.schoolName << '\t' << cur->data.deptName << '\t'\
					 << cur->data.dayType1 << '\t'\
					 << cur->data.level1 << '\t'\
					 << cur->data.stdnt << '\t' << cur->data.teacher << '\t' << cur->data.graduate << endl ;							
 				Remove_graduate( treeNG, cur, treeNG.GetRoot(), NULL ) ;					// delete Same Node in other tree
			   	cur = DeleteNode( cur, pre ) ;												// Delete Node then update curNode		
				found = true ;
				return DeleteSchool( del, cur, pre, treeNG ) ;	    	                    // the cur of this line is newCur
			}
			else if ( del < cur->data.schoolName ) 
				return DeleteSchool( del, cur->left, cur, treeNG ) ;
			else 
				return DeleteSchool( del, cur->right, cur, treeNG ) ;
		}
		
		// *************************************************
				
		void Remove_school( BSTree &treeSN, TreeNode *deleteNode, TreeNode *treeSN_cur, TreeNode *treeSN_pre ) {
			if( treeSN_cur->data.schoolName == deleteNode->data.schoolName ) {				// SNtree must have the same node
				if ( IsSame( treeSN_cur, deleteNode ) )  									
					treeSN.DeleteNode( treeSN_cur, treeSN_pre ) ;
				else Remove_school( treeSN, deleteNode, treeSN_cur->right, treeSN_cur ) ;	// because the same name of school will be right node
			}
			else if( treeSN_cur->data.schoolName > deleteNode->data.schoolName )
				Remove_school( treeSN, deleteNode, treeSN_cur->left, treeSN_cur ) ;
			else if( treeSN_cur->data.schoolName < deleteNode->data.schoolName )
				Remove_school( treeSN, deleteNode, treeSN_cur->right, treeSN_cur ) ;
		}		
		
		bool DeleteGraduate( int del, TreeNode *cur, TreeNode *pre, BSTree &treeSN ) {  
			if ( cur == NULL )                                                         	 // base case ( recursion )
				return found ;
			else if ( del >= cur->data.graduate ) {                                 	 // check the input number is smaller or equal to the current number
				found = true ;
				
				printf( "[%1d]\t", i ) ;
				i++ ;
				cout << cur->data.schoolName << '\t' << cur->data.deptName << '\t'\
					 << cur->data.dayType1 << '\t'\
					 << cur->data.level1 << '\t'\
					 << cur->data.stdnt << '\t' << cur->data.teacher << '\t' << cur->data.graduate << endl ; 
				Remove_school( treeSN, cur, treeSN.GetRoot(), NULL ) ;					// delete Same Node in other tree
				cur = DeleteNode( cur, pre ) ;  										// Delete Node then update curNode
				return DeleteGraduate( del, cur, pre, treeSN ) ;					
 	
			}
			else 
				return DeleteGraduate( del, cur->left, cur, treeSN ) ;                            
		}
		
		// *************************************************
		
		TreeNode * DeleteNode( TreeNode *deleteNode, TreeNode *pre ) {
			if( deleteNode->left == NULL && deleteNode->right == NULL ) {		// deleteNode is a leaf
				if( pre == NULL )												// deleteNode is root
					root = NULL ; 
				else if( pre->left == deleteNode ) 								// deleteNode is left child of PreNode
					pre->left = NULL ;				
				else if( pre->right == deleteNode )								// deleteNode is right child of PreNode
					pre->right = NULL ; 
				deleteNode = NULL ;
			}
			else if( deleteNode->left == NULL )	{								// deleteNode has a child (right node)
				TreeNode *temp = deleteNode ;	
				if( pre == NULL ){												// deleteNode is root and the root has a child
					deleteNode = deleteNode->right ;							// right child replace deleteNode
					root = deleteNode ;											// updata root
				}
				else{
					if ( pre->left == deleteNode ) {							// pre's left child will be replaced to delete's right child
						pre->left = deleteNode->right ;							// right child replace deleteNode
						deleteNode = pre->left ; 								// updata deleteNode
					}
					else if( pre->right == deleteNode ) {						// pre's right child will be replaced to delete's right child
						pre->right = deleteNode->right ;						// right child replace deleteNode
						deleteNode = pre->right ; 								// updata deleteNode
					}
				}
				delete temp ;													// release temp memory
			}
			else if( deleteNode->right == NULL ){								// deleteNode has a child (left node)
				TreeNode *temp = deleteNode ;									
				if( pre == NULL ){												// deleteNode is root and the root has a child
					deleteNode = deleteNode->left ;								// left child replace deleteNode
					root = deleteNode ;											// updata root
				}
				else{
					if ( pre->left == deleteNode ) {							// pre's left child will be replaced to delete's left child
						pre->left = deleteNode->left ;							// left child replace deleteNode
						deleteNode = pre->left ; 								// updata deleteNode
					}
					else if( pre->right == deleteNode ) {						// pre's right child will be replaced to delete's left child
						pre->right = deleteNode->left ;							// left child replace deleteNode
						deleteNode = pre->right ; 								// updata deleteNode
					}
				}
				delete temp ;
			}
			else if( deleteNode->left != NULL && deleteNode->right != NULL ) {				// have two child
				TreeNode *successor = deleteNode->right ; 									// find the node that the next node of deleteNode in inorder 
				TreeNode *successorPre = deleteNode ;
				while( successor->left != NULL ) {											// successor only has right node
					successorPre = successor ;
					successor = successor->left ;
				}
				deleteNode->data = successor->data ;										// copy the data of successor to deleteNode						
				DeleteNode( successor, successorPre ) ;										// Delete successor
			}
			return deleteNode ;
		}
	
		// *************************************************

		
		void SetQQ() {
			found = false ;                                                            // reset
			i = 1 ;
		}
		
		// *************************************************
		
		void WriteInOrder( TreeNode *cur ) {												
			// left print right
			if ( cur == NULL )	return ;
			WriteInOrder( cur->left ) ;
			fout << cur->data.schoolName << '\t' << cur->data.deptName << '\t'\
				 << cur->data.dayType1 << '\t' << cur->data.level1 << '\t'\
				 << cur->data.stdnt << '\t' << cur->data.teacher << '\t' << cur->data.graduate << endl ;
			WriteInOrder( cur->right ) ;
			
		} // Write()
		
		
};

class Assignment {
	
	private :

		vector<Data> list ;
		vector<Data> listBSN, listBNG ;
		BSTree treeSN, treeNG ;                                  // Binary Search tree
		BSTree treeBSN, treeBNG ;                                // Balanced Binary Search tree
		 
  		
	public :
		
		Assignment() {
			;
		}
  	
  		// *************************************************
  		
  		void Clear() {
  			
  			list.clear() ;
  			listBSN.clear() ;
  			listBNG.clear() ;
  			treeSN = BSTree() ;
  			treeNG = BSTree() ;
  			treeBSN = BSTree() ;
  			treeBNG = BSTree() ;
  			
		}
		
		// *************************************************
		
		void Reset() {
			
			treeSN.SetQQ() ;
			treeNG.SetQQ() ;
			
		}
  	
  		// *************************************************
  	
		void Read() {                         // for normal and for balanced tree
		
			Data temp ;  
			string s ;    
			char c ;         
			int i = 0 ;
		  	getline( fin, s ) ;							// first line will not input list
		  	getline( fin, s ) ;
	  		getline( fin, s ) ;
	  		while( fin >> i ) {
	  			temp.schoolCode = i ;
	  			fin >> temp.schoolName ;
	  			fin >> temp.deptCode ;
	  			fin >> temp.deptName ;
	  			
	  			fin.get( c ) ;
	  			for ( fin.get( c ) ; c != '\t' ; fin.get( c ) ) 
	  				temp.dayType1 = temp.dayType1+c ;	
				
	  			// fin >> temp.dayType1 >> temp.dayType2 ;
	  			
	  			for ( fin.get( c ) ; c != '\t' ; fin.get( c ) ) 
	  				temp.level1 = temp.level1+c ;	
				
	  			// fin >> temp.level1 >> temp.level2 ;
	  			
	  			for ( fin.get( c ) ; c != '\t' ; fin.get( c ) ) 
	  				temp.stdnt = temp.stdnt+c ;	
				
	  			// fin >> temp.stdnt ;
	  			
	  			for ( fin.get( c ) ; c != '\t' ; fin.get( c ) ) 
	  				temp.teacher = temp.teacher+c ;	
	  				
	  			// fin >> temp.teacher ;
	  			
	  			fin >> temp.graduate ;
	  			getline( fin, s ) ;				 
		  		list.push_back( temp ) ;
	  			temp.dayType1.clear() ;
	  			temp.level1.clear() ;
	  			temp.stdnt.clear() ;
	  			temp.teacher.clear() ;
			} // while		
			
		} // Read()
	
		// *************************************************
		
		void Read( int type ) {
			
			Data temp ;  
			string s ;    
			char c ;         
			while( fin >> temp.schoolName ) {
	  			fin >> temp.deptName ;
	  			fin.get( c ) ;
	  			for ( fin.get( c ) ; c != '\t' ; fin.get( c ) ) 
	  				temp.dayType1 = temp.dayType1+c ;	
	  			for ( fin.get( c ) ; c != '\t' ; fin.get( c ) ) 
	  				temp.level1 = temp.level1+c ;	
	  			for ( fin.get( c ) ; c != '\t' ; fin.get( c ) ) 
	  				temp.stdnt = temp.stdnt+c ;	
	  			for ( fin.get( c ) ; c != '\t' ; fin.get( c ) ) 
	  				temp.teacher = temp.teacher+c ;	
	  			fin >> temp.graduate ;	
				if ( type == 2 )		 
			  		listBSN.push_back( temp ) ;
			  	else
			  		listBNG.push_back( temp ) ;
	  			temp.dayType1.clear() ;
	  			temp.level1.clear() ;
	  			temp.stdnt.clear() ;
	  			temp.teacher.clear() ;
	  		}
		}
		
		void Print( int type ) {
			
			vector<Data>::iterator iter ;
			int i = 1 ;
			printf( "\n" ) ;
			if ( type == 1 ) {
				iter = list.begin() ;
				for( iter, i ; iter != list.end() ; ++iter, i++ ) {
				 	printf( "[%1d]\t", i ) ;
					cout << iter->schoolName << '\t' << iter->deptName << '\t'\
					<< iter->dayType1 << '\t' << iter->level1 << '\t'\
					<< iter->stdnt << '\t' << iter->teacher << '\t' << iter->graduate << endl ;   	
				} // for
			}
			if ( type == 2 ) {
				iter = listBSN.begin() ;
				for( iter, i ; iter != listBSN.end() ; ++iter, i++ ) {
				 	printf( "[%1d]\t", i ) ;
					cout << iter->schoolName << '\t' << iter->deptName << '\t'\
					<< iter->dayType1 << '\t' << iter->level1 << '\t'\
					<< iter->stdnt << '\t' << iter->teacher << '\t' << iter->graduate << endl ;   	
				} // for
			}
			if ( type == 3 ) {
				iter = listBNG.begin() ;
				for( iter, i ; iter != listBNG.end() ; ++iter, i++ ) {
				 	printf( "[%1d]\t", i ) ;
					cout << iter->schoolName << '\t' << iter->deptName << '\t'\
					<< iter->dayType1 << '\t' << iter->level1 << '\t'\
					<< iter->stdnt << '\t' << iter->teacher << '\t' << iter->graduate << endl ;   	
				} // for
			}

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
	
		bool LoadInBal( string num, int type ) {
			
			string read = "tree" ;
			read.append( num ) ;
			if ( type == 2 )
				read.append( "name.txt" ) ;
			else
				read.append( "num.txt" ) ;
			fin.open( read.c_str(), ios::in ) ;
			if ( !fin )
				return false ;
			else {
				Read( type ) ;
				fin.close() ;
				return true;
			}
			
		}
	
		// *************************************************
	
		void WriteOut( std::string num, int type ) {
		
			std::string write ;
			write = "tree" ;
	  		write.append( num ) ;
	  		if ( type == 1 )
	  			write.append( "name.txt" ) ;
	  		else
	  			write.append( "num.txt" ) ;
	  		fout.open( write.c_str(), ios::out );               // file open / out & append ( ios::out|ios::app )
      		// fout << "Hello!! success" << endl;               // output data in file
      		if ( type == 1 )
	      		treeSN.WriteInOrder( treeSN.GetRoot() ) ;
	      	else
	      		treeNG.WriteInOrder( treeNG.GetRoot() );
      		fout.close() ;
      		cout << "\nFile build : " << fout << endl ;
      		
		} // WriteOut()
	
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
		
		void AddBalancedNodes( int min, int max, int type ) {
			
			if ( min > max )	return ;
			else {
				int mid = ( max+min )/2 ;
				if ( type == 3 )
					treeBSN.AddBySN( treeBSN.GetRoot(), listBSN[mid] ) ;
				if ( type == 4 )
					treeBNG.AddByNG( treeBNG.GetRoot(), listBNG[mid] ) ;
				AddBalancedNodes( min, mid-1, type ) ;
				AddBalancedNodes( mid+1, max, type ) ;
				
			}
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
		
				
		bool Delete( string delSchool, int delGraduate, int type ) {
			
			if ( type == 1 ) {
				if( treeSN.DeleteSchool( delSchool, treeSN.GetRoot(), NULL, treeNG ) ) {
					cout << "\nTree heights :" << endl 
					<< "{ School Name } = " << treeSN.GetHeight( treeSN.GetRoot() ) << endl 
					<< "{ Number of Graduates } = " << treeNG.GetHeight( treeNG.GetRoot() ) << endl ; 
					return true ;
				}
			}
			else if ( type == 2 ) {
				if ( treeNG.DeleteGraduate( delGraduate, treeNG.GetRoot(), NULL, treeSN ) ){
					cout << "\nTree heights :" << endl 
					<< "{ School Name } = " << treeSN.GetHeight( treeSN.GetRoot() ) << endl 
					<< "{ Number of Graduates } = " << treeNG.GetHeight( treeNG.GetRoot() ) << endl ;
					return true ;
				}
			}
			else
				return false ;
				
		} // end delete
		
		// *************************************************************
		
		int getLength( int type ) {
			if ( type == 3 )
				return listBSN.size() ;
			if ( type == 4 )
				return listBNG.size() ;
		}
		
		void gpHeight() {
			cout << "\nTree heights :" << endl 
				 << "{ School Name } = " << treeBSN.GetHeight( treeBSN.GetRoot() ) << endl 
				 << "{ Number of Graduates } = " << treeBNG.GetHeight( treeBNG.GetRoot() ) << endl ;
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
		 << "* 4. Removal by School Name                  *\n"
		 << "* 5. Removal by Number of Graduates          *\n"
		 << "* 6. Save BST                                *\n"
		 << "* 7. Load BST                                *\n"
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
				list.Print( 1 ) ;
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
		else if ( command == 4 ) {
			
			cout << "Input a school name : " ;
			cin >> findSchool ;
			cout << "\nDeleted records:" << endl ;
			if ( !list.Delete( findSchool, findGraduate, 1 ) )
				cout << "There is no match!" << endl ;
			
			findSchool.clear() ;
			list.Reset() ;
			
		} // end else if
		else if ( command == 5 ) {
			
			cout << "Input the number of graduates : " ;
			cin >> findGraduate ;
			cout << "\nDeleted records:" << endl ;
			if ( !list.Delete( findSchool, findGraduate, 2 ) )
				cout << "There is no match!" << endl ;
			
			findSchool.clear() ;
			list.Reset() ;
			
		} // end else if		
		else if ( command == 6 ) {
			list.WriteOut( num, 1 ) ;
			list.WriteOut( num, 2 ) ;
		}
		else if ( command == 7 ) {
			if ( !list.LoadInBal( num, 2 ) || !list.LoadInBal( num, 3 ) )
				cout << "Please SAVE the in-order data first by using command 6 !" << endl ;
			else  {
				cout << "***Loaded data sorting by school name.***" << endl ;
				list.Print( 2 ) ;
				cout << "***Loaded data sorting by number of graduates.***" << endl ;
				list.Print( 3 ) ;
				list.AddBalancedNodes( 0, list.getLength( 3 )-1, 3 ) ;
				list.AddBalancedNodes( 0, list.getLength( 4 )-1, 4 ) ;
				list.gpHeight() ;
        	}
		}
		else
			cout << "Couldn't find command, please try again!" << endl ;
			
		cout << "\n*** University Graduate Information System ***\n"
			 << "* 0. Quit                                    *\n"
			 << "* 1. Create Two Binary Search Trees          *\n"
			 << "* 2. Search by School Name                   *\n"
			 << "* 3. Search by Number of Graduates           *\n"
			 << "* 4. Removal by School Name                  *\n"
			 << "* 5. Removal by Number of Graduates          *\n"
			 << "* 6. Save BST                                *\n"
			 << "* 7. Load BST                                *\n"
			 << "----------------------------------------------\n"
			 << "Input a command : " ;
		cin >> command ;
	} // end while
  
} // main()





