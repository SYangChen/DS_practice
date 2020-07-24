/*  資工110 
 *  B063040061 
 *  陳少洋
 *  Nov. 27, 2018
 *  Assignmenet #6
 *	使用linked list之資料結構，實作一棵二元搜尋數，並使其可以記載哪些
 *	數字出現過奇數次 ( 將輸入數字加入樹，若重複出現則移除之 )。 
 */

#include <iostream>

using namespace std ;

typedef struct node {
	// binary search tree node define
	int data ;		// data record
	node *left ;	// left element
	node *right ;	// right element
}node; 

class BSTree {
	
	private :
		
		node *root ;			// binary search tree root
		int numOfElement ;		// # of elements on the tree
		int i ;					// using for array index
		
	public :
		
		BSTree() {
			// constructor of binary search tree
			root = NULL ;
			numOfElement = 0 ;
			i = 0 ;
		} // BSTree()
		
		void InsertNode( int inData ) {
			// insert the node into the tree
			// if the data has already on the tree
			// call the delete function to remove that element
			numOfElement++ ;
			bool find = false ;		// find data on exactly node
			node *parent = NULL ;	// record the parent of the current node
			node *current = root ;	// current node
			node *temp = new node ;	// temp node = insert node
			temp->data = inData ;
			temp->left = NULL ;
			temp->right = NULL ;
			if ( root == NULL )
				root = temp ;
			else {
				while ( !find ) {
					// go left, right or excatly find the data
					if ( inData < current->data ) {
						if ( current->left == NULL ) {
							find = true ;
							current->left = temp ;
						} // end if
						else {
							parent = current ;
							current = current->left ;
						} // end else
					} // end if
					else if ( inData > current->data ) {
						if ( current->right == NULL ) {
							find = true ;
							current->right = temp ;
						} // end if
						else {
							parent = current ;
							current = current->right ;
						} // end else
					} // end else if
					else {
						find = true ;
						DeleteNode( parent, current ) ;
						// delete the data which repeated
					} // end else 
				} // end while
			} // end else
		} // InsertNode()
		
		// ----------------------------------------
		
		void DeleteNode( node *parent, node *delNode ) {
			// delete the node ( 3 cases )
			numOfElement-=2 ;	// #ofelement - itself - the node which deleted = -2
			if ( delNode->left == NULL && delNode->right == NULL ) {
				// cout << "11111111" << endl ;
				if ( parent == NULL )
					root = NULL ;
				else if ( delNode->data < parent->left->data )
					parent->left = NULL ;
				else
					parent->right = NULL ;
				delete delNode ;
			} // end if
			else if ( delNode->left == NULL || delNode->right == NULL ) {
				// cout << "22222222" << endl ;
				if ( parent == NULL ) {
					if ( delNode->left != NULL )
						root = delNode->left ;
					else
						root = delNode->right ;	
				} // end if
				else if ( parent->left != NULL && delNode->data < parent->data ) {
					if ( delNode->left != NULL )
						parent->left = delNode->left ;
					else
						parent->left = delNode->right ;
				} // end else if
				else {
					if ( delNode->left != NULL )
						parent->right = delNode->left ;
					else
						parent->right = delNode->right ;
				} // end else
				delete delNode ;
			} // end else if
			else {
				// cout << "3333333" << endl ;
				node *inSuccessor = delNode->right ;	// inorder successor
				node *inSucParent = delNode ;			// inorder successor parent
				for ( ; inSuccessor->left != NULL ; inSuccessor = inSuccessor->left ) 
					inSucParent = inSuccessor ;
				delNode->data = inSuccessor->data ;
				if ( inSuccessor->right != NULL ) {
					if ( inSucParent == delNode )
						inSucParent->right = inSuccessor->right ;
					else
						inSucParent->left = inSuccessor->right ;
				}
				else {
					if ( inSucParent == delNode )
						inSucParent->right = NULL ;
					else
						inSucParent->left = NULL ;
				}
				// delete delNode ; 
			} // end else
		} // DeleteNode()
		
		// -----------------------------------------
		
		void getInorder( node *current, int *l, int *r ) {
			// inorder traversal and record the left right node in arrays
			if ( !current )
				return ;
			getInorder( current->left, l, r ) ;
			cout << current->data ; // << " ";
			if ( i < numOfElement-1 )		// no last white space printed
				cout << " " ;
			if ( current->left != NULL )
				l[i] = current->left->data ;
			else
				l[i] = 0 ;
			if ( current->right != NULL )
				r[i] = current->right->data ;
			else
				r[i] = 0 ;
			i++ ;
			getInorder( current->right, l, r ) ;
			
		}
		
		// -----------------------------------------
		
		void PrintTree() {
			// print out the node and its left, right node
			int *leftBuffer = new int[numOfElement+1] ;
			int *rightBuffer = new int[numOfElement+1] ;
			cout << "node: " ;
			getInorder( root, leftBuffer, rightBuffer ) ;
			cout << endl << "left: " ;
			for( int i = 0 ; i < numOfElement ; i++ ) {
				cout << leftBuffer[i] ; // << " " ;
				if ( i < numOfElement-1 )	// no last white space printed
					cout << " " ;
			}
			cout << endl << "right: " ;
			for( int i = 0 ; i < numOfElement ; i++ ) {
				cout << rightBuffer[i] ; // << " " ;
				if ( i < numOfElement-1 )	// no last white space printed
					cout << " " ;
			}
			cout << endl ;
			delete leftBuffer ;
			delete rightBuffer ; 
		}
		
		// -----------------------------------------
		
		void Clear() {
			// clear the data for next use
			delete root ;
			root = NULL ;
			numOfElement = 0 ;
			i = 0 ;
		}
};

int main() {
	BSTree oetree ;		// Odd Even tree
	int num ;			// input number
	cin >> num ;
	while ( num != EOF ) {
		while ( num != -1 ) {
			oetree.InsertNode( num ) ;
			// oetree.PrintTree() ;
			cin >> num ;
		}
		oetree.PrintTree() ;
		oetree.Clear() ;
		// cin.ignore() ;
		// num = cin.peek() ;
		if ( cin >> num )	// no last end line printed
			cout << endl ;
	}
}
