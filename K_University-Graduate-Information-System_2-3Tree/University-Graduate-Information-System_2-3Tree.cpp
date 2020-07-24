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
	int order ;
	
}Data;

typedef struct Item {
	
	int num ;                // stream number 
	string schoolName ;
	Item *next ; 
	
}Item;

typedef struct Node {
	Item *itemLeft ;         // key1 
	Item *itemRight ;        // key2
	int itemNum ;            // the amount of keys
	Node *left ;
	Node *middle ;
	Node *right ;
	Node *parent ;
}Node;


class TwoThreeTree {
	
	private :
		
		Node *root ;
		Item *foundItem ;
	
	public :
		
		TwoThreeTree() {
			root = NULL ;
		}
		
		// *************************************************
		
		void ttClear() {
			delete root ;
			root = NULL ;
		}
		
		// *************************************************
		
		Item *GetRootItemL() {
			return root->itemLeft ;
		}
		
		// *************************************************
		
		Item *GetRootItemR() {
			return root->itemRight ;
		}
	
		// *************************************************
		
		Item *FindRear( Item *pLine ) {
			for ( ; pLine->next != NULL ; pLine = pLine->next )
				;
			return pLine ;
		} 
		
		// *************************************************
		
		Node *findLeaf( Node *walk, Item *item ) {
			if ( walk->left == NULL && walk->middle == NULL && walk->right == NULL ) {           // case leaffffff
				if ( walk->itemLeft->schoolName == item->schoolName ) {
					Item *rear = FindRear( walk->itemLeft ) ;                                    // same name linked together
					rear->next = item ;
					return NULL ;
				}
				else if ( walk->itemNum == 2 && walk->itemRight->schoolName == item->schoolName ) {
					Item *rear = FindRear( walk->itemRight ) ;                                   // same name linked together
					rear->next = item ;
					return NULL ;
				}
				return walk ;
			}
			else if ( walk->itemNum == 1 ) {                                                     // case one key
				if ( item->schoolName < walk->itemLeft->schoolName ) {
					return findLeaf( walk->left, item ) ;
				}
				else if ( item->schoolName == walk->itemLeft->schoolName ) {
					Item *rear = FindRear( walk->itemLeft ) ;                                    // same name linked together
					rear->next = item ;
					return NULL ;
				}
				else {
					return findLeaf( walk->right, item ) ;
				}
			}
			else {                                                                               // case two keys
				if ( item->schoolName < walk->itemLeft->schoolName ) {
					return findLeaf( walk->left, item ) ;
				}
				else if ( item->schoolName == walk->itemLeft->schoolName ) {
					Item *rear = FindRear( walk->itemLeft ) ;                                    // same name linked together
					rear->next = item ;
					return NULL ;
				}
				else if ( item->schoolName == walk->itemRight->schoolName ) {
					Item *rear = FindRear( walk->itemRight ) ;                                   // same name linked together
					rear->next = item ;
					return NULL ;
				}
				else if ( item->schoolName < walk->itemRight->schoolName ) {
					return findLeaf( walk->middle, item ) ;
				}
				else 
					return findLeaf( walk->right, item ) ;
				
			}
		}
		
		void InsertItem( Item *newItem ) {
			if ( root == NULL ) {
				root = new Node ;
				root->itemNum = 1 ;
				root->itemLeft = newItem ;
				root->itemRight = NULL ;
				root->middle = NULL ;
				root->left = NULL ;
				root->right = NULL ;
				root->parent = NULL ;	
			}
			else {
				Node *walk = findLeaf( root, newItem ) ;                        // return NULL means the school has already saved
				if ( walk != NULL ) {                                           // and it was pointed by the last one(same school name)
					if ( walk->itemNum == 1 ) {
						if ( newItem->schoolName > walk->itemLeft->schoolName ) // small left <-> big right
							walk->itemRight = newItem ;
						else {
							walk->itemRight = walk->itemLeft ;
							walk->itemLeft = newItem ;
						}
						walk->itemNum = 2 ;
					}
					else {                                                      // when there are need to be split up
						Node *temp = new Node ;
						temp->itemNum = 1 ;
						temp->itemLeft = newItem ;
						temp->itemRight = NULL ;
						temp->left = NULL ;
						temp->middle = NULL ;
						temp->right = NULL ; 
						temp->parent = NULL ;
						Split ( walk, temp ) ;
					}
				}
			}
		}
		
		void Split( Node *treeNode, Node *tempN ) {
			
			if ( treeNode == root ) {
				root = new Node ;
				root->itemNum = 1 ;
				root->itemRight = NULL ;
				root->parent = NULL ;
				int mid = DetermineMid( treeNode->itemLeft, treeNode->itemRight, tempN->itemLeft ) ;
				if ( mid == 1 ) {
					root->itemLeft = treeNode->itemLeft ;
					treeNode->itemLeft = treeNode->itemRight ;
					root->left = tempN ;
					root->right = treeNode ;
				}
				else if ( mid == 2) {
					root->itemLeft = treeNode->itemRight ;
					root->left = treeNode ;
					root->right = tempN ;
				}
				else {
					root->itemLeft = tempN->itemLeft ;
					tempN->itemLeft = treeNode->itemRight ;
					root->left = treeNode ;
					root->right = tempN ;
				}
				treeNode->itemNum = 1 ;
				treeNode->itemRight = NULL ;
				root->left->parent = root ;                                         // set parent
				root->right->parent = root ;
				root->middle = NULL ;
				if ( !IsLeaf( treeNode ) ) {                                        // special case 
					if ( treeNode->left == NULL )                                   // the node is not leaf
						treeNode->left = treeNode->middle ;
					else if ( treeNode->right == NULL )
						treeNode->right = treeNode->middle ;
					else {
						treeNode->middle = treeNode->right ;                        // use as temp spack
						treeNode->right = tempN->left ;
						tempN->left->parent = treeNode ;
						tempN->left = tempN->right ;
						tempN->right = treeNode->middle ;                           // temp store back
						tempN->right->parent = tempN ;
					}
					treeNode->middle = NULL ;
				}
			}
			else if ( !IsLeaf( treeNode ) ) {                                        // not leaf node
				if ( treeNode->parent->itemNum == 1 ) {                              // one key(parent) internal node
				 	if ( treeNode->left == NULL ) {
				 		if ( treeNode->itemLeft->schoolName < treeNode->parent->itemLeft->schoolName ) {
				 			treeNode->parent->itemRight = treeNode->parent->itemLeft ;
				 			treeNode->parent->itemLeft = treeNode->itemLeft ;
				 			treeNode->parent->middle = treeNode->parent->left ;
				 			treeNode->parent->left = tempN ;
						}
						else {
							treeNode->parent->itemRight = treeNode->itemLeft ;
							treeNode->parent->middle = tempN ;
						}
						treeNode->parent->itemNum = 2 ;
						tempN->parent = treeNode->parent ;
						treeNode->itemLeft = treeNode->itemRight ;
			 			treeNode->itemRight = NULL ;
			 			treeNode->itemNum = 1 ;
			 			treeNode->left = treeNode->middle ;
			 			treeNode->middle = NULL ;
					} 
					else if ( treeNode->middle == NULL ) {                                   // need to relocate their children
						if ( tempN->itemLeft->schoolName < treeNode->parent->itemLeft->schoolName ) {
							treeNode->parent->itemRight = treeNode->parent->itemLeft ;
							treeNode->parent->itemLeft = tempN->itemLeft ;
							treeNode->parent->middle = new Node ;
							treeNode->parent->middle->parent = treeNode->parent ;            // QQ
							treeNode->parent->middle->itemLeft = treeNode->itemRight ;
							treeNode->parent->middle->left = tempN->right ;
							treeNode->parent->middle->right = treeNode->right ;
							treeNode->right = tempN->left ;
							treeNode->right->parent = treeNode ;
						}
						else {
							treeNode->parent->itemRight = tempN->itemLeft ;
							treeNode->parent->middle = new Node ;
							treeNode->parent->middle->parent = treeNode->parent ;            // QQ
							treeNode->parent->middle->itemLeft = treeNode->itemLeft ;
							treeNode->itemLeft = treeNode->itemRight ;
							treeNode->parent->middle->left = treeNode->left ;
							treeNode->parent->middle->right = tempN->left ;
							treeNode->left = tempN->right ;
							treeNode->left->parent = treeNode ;
						}
						treeNode->parent->itemNum = 2 ;
						treeNode->parent->middle->itemRight = NULL ;
						treeNode->parent->middle->itemNum = 1 ;
						treeNode->itemRight = NULL ;
						treeNode->itemNum = 1 ;
						treeNode->parent->middle->middle = NULL ; 
						treeNode->parent->middle->left->parent = treeNode->parent->middle ;
						treeNode->parent->middle->right->parent = treeNode->parent->middle ;
						// tempN = NULL ;
						// delete tempN ;
					}
					else { // (tree right == NULL )
					 	if ( treeNode->itemRight->schoolName < treeNode->parent->itemLeft->schoolName ) {
					 		treeNode->parent->itemRight = treeNode->parent->itemLeft ;
					 		treeNode->parent->itemLeft = treeNode->itemRight ;
					 		treeNode->parent->middle = tempN ;
						}
						else {
							treeNode->parent->itemRight = treeNode->itemRight ;
							treeNode->parent->middle = treeNode ;
							treeNode->parent->right = tempN ;
						}
						treeNode->parent->itemNum = 2 ;
						tempN->parent = treeNode->parent ;
						treeNode->itemRight = NULL ;
						treeNode->itemNum = 1 ;
						treeNode->right = treeNode->middle ;
						treeNode->middle = NULL ;
					}
				}
				else {                                                 // two keys(parent) at internal node
					int mid = DetermineMid( treeNode->itemLeft, treeNode->itemRight, tempN->itemLeft ) ;
					Node *mergeN = treeNode->parent ;
					if ( treeNode->parent->left == treeNode )
						treeNode->parent->left = NULL ;
					else if ( treeNode->parent->middle == treeNode ) 
						treeNode->parent->middle = NULL ;
					else
						treeNode->parent->right = NULL ;
						
					if ( treeNode->left == NULL ) {
				 		Node *p = new Node ;
						p->itemLeft = treeNode->itemLeft ;
						p->itemNum = 1 ;
						treeNode->itemLeft = treeNode->itemRight ;
						treeNode->itemRight = NULL ;
						treeNode->itemNum = 1 ;
						treeNode->left = treeNode->middle ;
						treeNode->middle = NULL ;
						p->left = tempN ;
						p->right = treeNode ;
						p->middle = NULL ;                               // bug here?
						p->left->parent = p ;
						p->right->parent = p ;
						Split( mergeN, p ) ;
					} 
					else if ( treeNode->middle == NULL ) {
						Node *p = new Node ;
						p->itemLeft = tempN->itemLeft ;
						p->itemNum = 1 ;
						tempN->itemLeft = treeNode->itemRight ;
						treeNode->itemRight = NULL ;
						treeNode->itemNum = 1 ;
						p->left = treeNode ;
						p->right = tempN ;
						p->middle = NULL ;                               // bug here?
						p->left->parent = p ;
						p->right->parent = p ;
						treeNode->middle = treeNode->right ;      // work as temp space
						treeNode->right = tempN->left ;
						treeNode->right->parent = treeNode ;         // QQQQQQQQQQQQQ
						tempN->left = tempN->right ;
						tempN->right = treeNode->middle ;         // work as temp store back
						tempN->right->parent = tempN ;               // QQQQQQQQQQQQQQQQ
						treeNode->middle = NULL ;
						Split( mergeN, p ) ;
					}
					else {
					 	Node *p = new Node ;
						p->itemLeft = treeNode->itemRight ;
						p->itemNum = 1 ;
						treeNode->itemRight = NULL ;
						treeNode->itemNum = 1 ;
						treeNode->right = treeNode->middle ;
						treeNode->middle = NULL ;
						p->left = treeNode ;
						p->right = tempN ;
						p->middle = NULL ;                         // bug here?
						p->left->parent = p ;
						p->right->parent = p ;
						Split( mergeN, p ) ;
					}
				}
			}
			else {                                                       // two keys encounter to leaffffffffff
				int mid = DetermineMid( treeNode->itemLeft, treeNode->itemRight, tempN->itemLeft ) ;
				if ( treeNode->parent->itemNum == 1 ) {                  // one key(parent) at leaf
					if ( mid == 1 ) {
						if ( treeNode->itemLeft->schoolName < treeNode->parent->itemLeft->schoolName ) {
							treeNode->parent->itemRight = treeNode->parent->itemLeft ;
							treeNode->parent->itemLeft = treeNode->itemLeft ;
							treeNode->parent->middle = treeNode ;
							treeNode->parent->left = tempN ;
						}
						else {
							treeNode->parent->itemRight = treeNode->itemLeft ;
							treeNode->parent->middle = tempN ;
						}
						treeNode->itemLeft = treeNode->itemRight ;
						treeNode->itemRight = NULL ;
						treeNode->parent->itemNum = 2 ;
						treeNode->itemNum = 1 ;
						tempN->parent = treeNode->parent ;
					}
					else if ( mid == 2 ) {
						if ( treeNode->itemRight->schoolName < treeNode->parent->itemLeft->schoolName ) {
							treeNode->parent->itemRight = treeNode->parent->itemLeft ;
							treeNode->parent->itemLeft = treeNode->itemRight ;
							treeNode->parent->middle = tempN ;
						}
						else {
							treeNode->parent->itemRight = treeNode->itemRight ;
							treeNode->parent->middle = treeNode ;
							treeNode->parent->right = tempN ;
						}
						treeNode->parent->itemNum = 2 ;
						treeNode->itemRight = NULL ;
						treeNode->itemNum = 1 ;
						tempN->parent = treeNode->parent ;
					}
					else {
						if ( tempN->itemLeft->schoolName < treeNode->parent->itemLeft->schoolName ) {
							treeNode->parent->itemRight = treeNode->parent->itemLeft ;
							treeNode->parent->itemLeft = tempN->itemLeft ;
							treeNode->parent->middle = treeNode ;
							treeNode->parent->left = tempN ;
							tempN->itemLeft = treeNode->itemLeft ;
							treeNode->itemLeft = treeNode->itemRight ;
						}
						else {
							treeNode->parent->itemRight = tempN->itemLeft ;
							treeNode->parent->middle = treeNode ;
							treeNode->parent->right = tempN ;
							tempN->itemLeft = treeNode->itemRight ;
						}
						treeNode->itemRight = NULL ;
						treeNode->itemNum = 1 ;
						treeNode->parent->itemNum = 2 ;
						tempN->parent = treeNode->parent ;
					}
					
				}
				else {                                                             // two keys(parent) at leaf
					if ( mid == 1 ) {
						tempN->left = new Node ;
						tempN->left->left = NULL ;                        // bug here?
						tempN->left->middle = NULL ;                        // bug here?
						tempN->left->right = NULL ;                        // bug here?
						tempN->left->itemLeft = tempN->itemLeft ;
						tempN->left->itemRight = NULL ;
						tempN->right = treeNode ;
						tempN->itemLeft = treeNode->itemLeft ;
						treeNode->itemLeft = treeNode->itemRight ;
						treeNode->itemRight = NULL ;
					}
					else if ( mid == 2 ) {
						tempN->right = new Node ;
						tempN->right->left = NULL ;                        // bug here?
						tempN->right->middle = NULL ;                        // bug here?
						tempN->right->right = NULL ;                        // bug here?
						tempN->right->itemLeft = tempN->itemLeft ;
						tempN->right->itemRight = NULL ;
						tempN->left = treeNode ;
						tempN->itemLeft = treeNode->itemRight ;
						treeNode->itemRight = NULL ;
					}
					else {
						tempN->right = new Node ;
						tempN->right->left = NULL ;                        // bug here?
						tempN->right->middle = NULL ;                        // bug here?
						tempN->right->right = NULL ;                        // bug here?
						tempN->right->itemLeft = treeNode->itemRight ;
						treeNode->itemRight = NULL ;
						tempN->left = treeNode ;
					}
					tempN->right->itemNum = 1 ;
					tempN->left->itemNum = 1 ;
					Node *p = treeNode->parent ;
					if ( p->left == treeNode )
						p->left = NULL ;
					else if ( p->middle == treeNode ) 
						p->middle = NULL ;
					else
						p->right = NULL ;
					tempN->left->parent = tempN ;
					tempN->right->parent = tempN ;
					// treeNode = NULL ;               //  ///////////////////////////////////////
					// delete treeNode ;
					Split( p, tempN ) ;
				}
			}
		}
		
		// *************************************************
		
		bool IsLeaf( Node *test ) {
			if ( test->left == NULL && test->middle == NULL && test->right == NULL )
				return true ;
			return false ;
		}
		
		// *************************************************
		
		int DetermineMid( Item *one, Item *two, Item *three ) {
			if ( three->schoolName > one->schoolName && three->schoolName < two->schoolName )
				return 3 ;
			else if ( three->schoolName > one->schoolName && three->schoolName > two->schoolName)
				return 2 ;
			else
				return 1 ;
		}
		
		// *************************************************
		
		Item* Search( string target ) {									// to search name
			SearchName( target, root ) ;								// then return the search result
			return foundItem ;
		}
		
		// *************************************************
		
		void SearchName( string target, Node* current ){				
			if( current == NULL )
				foundItem = NULL ;
				
			else if( current->itemNum == 1 ){							// only exist itemLeft
				if( target < current->itemLeft->schoolName )			// target smaller than itemleft
					SearchName( target, current->left ) ;				// to compare leftchild
				else if( target > current->itemLeft->schoolName )
					SearchName( target, current->right ) ;
				else													// find the matched item
					foundItem = current->itemLeft ;
			}
			
			
			else {														// exist itemLeft and itemRight
				if ( target < current->itemLeft->schoolName )			// target smaller than itemleft
					SearchName( target, current->left ) ;
				else if ( target == current->itemLeft->schoolName )		// find the matched item
					foundItem = current->itemLeft ;
				else if ( target == current->itemRight->schoolName )	// find the matched item
					foundItem = current->itemRight ;
				else if ( target > current->itemRight->schoolName )		// target bigger than itemRight
					SearchName( target, current->right ) ;
				else													// target bigger than itemleft , smaller than itemRight
					SearchName( target, current->middle ) ;
			}
		}
};

// ==================================================================================

class Assignment {
	
	private :

		vector<Data> list ;
		vector<Data> searchList ;		
		vector<Data> rootList ;
		vector<Data> tempList ;
		TwoThreeTree ttTree ;
		 
  		
	public :
		
		Assignment() {
			;
		}
		
		// *************************************************
  	
  		void Clear() {
  			list.clear() ;
  			searchList.clear() ;
  			rootList.clear() ;
  			ttTree.ttClear() ;
		}
		
		// *************************************************
  	
		void Read() {
		
			Data temp ;  
			string s ;  
			string tempstring ;  
			char c ;         
			int i = 0 ;
			int order = 1 ;
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
				if ( !tempstring.empty() ) 
					temp.graduate = atoi( tempstring.c_str() ) ;
				
				temp.order = order ;
				order++ ;
				list.push_back( temp ) ;
				
		  		temp.schoolName.clear() ;
		  		temp.deptCode.clear() ;
		  		temp.deptName.clear() ;
	  			temp.dayType.clear() ;
	  			temp.level.clear() ;
	  			temp.stdnt.clear() ;
	  			temp.teacher.clear() ;
	  			tempstring.clear() ;
	  			s.clear() ;
			} // while		
			
		} // Read()
	
		// *************************************************
		
		void Print() {
			
			cout << "*** There are " << list.size() << " matched records, listed as below:" << endl ;
			for ( int i = 0 ; i < list.size() ; i++ ) {
				cout << "[" << list[i].order << "] " << list[i].schoolName<< ", " << list[i].deptName << ",\t"\
					 << list[i].dayType << ",\t" << list[i].level << ",\t" << list[i].graduate << endl ;
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
		
		void BuildttTree() {
			Item *newItem = new Item ;
			for ( int i = 1 ; i <= list.size() ; i++ ) {
				newItem->num = i ;
				newItem->schoolName += list[i-1].schoolName ;
				newItem->next = NULL ;
				ttTree.InsertItem( newItem ) ;
				newItem = NULL ;
				delete newItem ;
				newItem = new Item ;
			}
		//	ttTree.PrintRoot() ;
			cout << "########################################################" << endl ;
			cout << "Mission 1: Build a 2-3 tree" << endl ;
			cout << "########################################################" << endl ;
			PrintRoot() ;
		}
		
		// *************************************************
		
		void SearchSchool( std::string target ) {						
			Item* foundItem = ttTree.Search( target ) ;						// function will return a match Item 
			if ( foundItem == NULL ) 										// match Item is NOT exist  
				cout << target << " cannot find a match!!!" << endl ;
			
			else {
				for( ; foundItem != NULL ; foundItem = foundItem->next )	// find match item 
					searchList.push_back( list[foundItem->num-1] ) ;		// To get the data of matched item from input list
				Sort() ;													// and push them into a new list(called searchList) 
			}			
		}
		
		// *************************************************
			
		void Sort() {														// To sort the searchList by graduates
			for ( int i = 0 ; i < searchList.size() ; i++ ) 	
				for ( int j = 0 ; j < searchList.size()-i-1 ; j++ ) 
					if ( searchList[j].graduate < searchList[j+1].graduate ) {
						tempList.clear() ;
						tempList.push_back( searchList[j] ) ;
						searchList[j] = searchList[j+1] ;
						searchList[j+1] = tempList[0] ;
					}
			PrintList( searchList ) ;
		}
		
		// *************************************************
		
		void PrintRoot () {												// get root itemLeft ( must Exist )
			Item* getItem = ttTree.GetRootItemL() ;						// then get the data of items from input list
																		
			for( ; getItem != NULL ; getItem = getItem->next )			// and push them into a new list(called rootList) 
				rootList.push_back( list[getItem->num-1] ) ;
				
			getItem = ttTree.GetRootItemR() ;							// get root itemRight 
			if( getItem != NULL )										// if itemRight exist, do the same steps as itemLeft
				for( ; getItem != NULL ; getItem = getItem->next )
					rootList.push_back( list[getItem->num-1] ) ;
					
			PrintList( rootList ) ;
		}
		
		// *************************************************
		
		void PrintList( vector<Data> list ) {							// Print list with Number, order

			for ( int i = 0 ; i < list.size() ; i++ ) {
				cout << "  " << i+1 << ": " << "[" << list[i].order << "] "<< list[i].schoolName << ", " 
					 << list[i].deptName << ",\t" << list[i].dayType << ",\t" 
				     << list[i].level << ",\t" << list[i].graduate << endl ;
			}
		
		} // PrintSearchList
	
	}; 

// ==================================================================================
	
int main() {
	
	Assignment assignment ;
	int k ;
	std::string num ;
	std::string command = "87" ;     
	std::string searchTarget = "87" ; 
	while ( command != "0" ) {
		cout << "*********************************" << endl ;
		cout << "* On-machine Exercise           *" << endl ;
		cout << "* Mission 1: Build a 2-3 tree   *" << endl ;
		cout << "* Mission 2: Search a 2-3 tree  *" << endl ;
		cout << "*********************************" << endl ; 
		cout << "Input the file number[0]Quit : " << endl ;
		while ( num != "0" ) {
			cin >> num ;
			if ( num == "0" ) return 0 ;
			if ( !assignment.LoadIn( num ) ) 
				cout << "No such file, please enter again!" << endl << "Input the file number[0]Quit : " << endl ;
			else num = "0" ;
		}
		assignment.Print() ;
		assignment.BuildttTree() ;
		
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl ;
		cout << "Mission 2: Search a 2-3 tree" << endl ;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl ;
		cout << "Enter a name to search:" << endl ;
		cin >> searchTarget ;
		assignment.SearchSchool( searchTarget ) ;
		
		cout << "please enter '0' to quit or any other to continue" << endl ;
		assignment.Clear() ;
		cin >> command ; 
	}
} // main()





