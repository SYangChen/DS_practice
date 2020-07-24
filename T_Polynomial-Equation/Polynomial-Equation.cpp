/*  資工110 
 *  B063040061 
 *  陳少洋
 *  Nov. 10, 2018
 *  Assignmenet #5
 *	使用linked list資料結構，建立多項式方程式，重載 + * 運算子，
 *	並根據使用者輸入之多項式，進行加法與乘法之運算，並輸出結果。 
 */
#include <iostream>

using namespace std ;

typedef struct poly {
	int coef ;	// coefficient 
	int exp ;	// exponent 
	poly *next ;// next location 
}poly; 

class Polynomial {
	
	private :
		
		poly *equation ;		// polynomial equation linked list
		
	public :
		
		Polynomial() {
			equation = NULL ;
		} // Polynomial() constructor 
		
		// -----------------------------------------
		
		void setEqnElement( int coefficient, int exponent ) {
			// set equation elements one by one
			poly *pre, *temp ;			// prenode, tempnode(to add element)
			bool add = false ;			// whether add or not
			temp = new poly ;			// new node for adding element
			temp->coef = coefficient ;	// set node
			temp->exp = exponent ;
			temp->next = NULL ;
			if ( equation != NULL )	{	// not the first node of all
				for ( poly *walk = equation ; !add && walk != NULL ; walk = walk->next ) {
					// find the location through power down equation and insert it
					if ( walk->exp == exponent ) {	// find the same exponent (compound)
						walk->coef = walk->coef+coefficient ;
						if ( walk->coef == 0 ) {
							if ( walk == equation ) 
								equation = walk->next ;
							else 
								pre->next = walk->next ;
							walk->next = NULL ;		// **delete** the node
							delete walk ;			// if the compound coefficient is 0	
						}
						add = true ;
					}
					else if ( walk->exp < exponent ) { // found the location to insert
						temp->next = walk ;
						if ( equation == walk )
							equation = temp ;
						else
							pre->next = temp ;
						add = true ;
					}
					else ;	// walk->exp > exponent still need to find next location do nothing
					pre = walk ;	// get walk preNode
				}
			}
			if ( !add ) {	// means this node need to insert at the end
				if ( equation == NULL )
					equation = temp ;
				else
					pre->next = temp ;
			}
		} // setEqnElement()
		
		// -----------------------------------------
		
		void PrintEqn() {
			// print out the equation
			if ( equation == NULL )
				cout << "0 0" << endl ;
			else {
				for ( poly *cur = equation ; cur != NULL ; cur = cur->next ) 
					cout << cur->coef << " " << cur->exp << endl ;
			}
		} // PrintEqn()
		
		// -----------------------------------------
		
		void Clear() {
			// reset the equation
			delete equation ;
			equation = new poly ;
			equation = NULL ; 
		} // Clear()
		
		// -----------------------------------------
		
		Polynomial operator+( Polynomial &b ) {
			// overloading operator + 
			// push all element into result
			Polynomial result ;
			for ( poly *walkA = equation ; walkA != NULL ; walkA = walkA->next ) 
				result.setEqnElement( walkA->coef, walkA->exp ) ;
			for ( poly *walkB = b.equation ; walkB != NULL ; walkB = walkB->next )
				result.setEqnElement( walkB->coef, walkB->exp ) ;
			return result ;
		} // operator overloading +
		
		// -----------------------------------------
		
		Polynomial operator*( Polynomial &b ) {
			// overloading operator *
			// after multiply each other push all element into result
			Polynomial result ;
			for ( poly *walkA = equation ; walkA != NULL ; walkA = walkA->next ) {
				for ( poly *walkB = b.equation ; walkB != NULL ; walkB = walkB->next ) 
					result.setEqnElement( walkA->coef*walkB->coef, walkA->exp+walkB->exp ) ;
			}
			return result ;
		} // operator overloading *
};

int main() {
	int num, num2, cases = 0  ;		// how many elements for equation 
	int coefficient, exponent ;		// coefficient , exponent
	Polynomial a, b, rADD, rMUL ;	// object of polynomial equation
	cin >> num ;
	if ( num == 0 )
		cin >> num2 ;
	while ( num != 0 || num2 != 0 ) {
		for ( int i = 0 ; i < num ; i++ ) {
			cin >> coefficient >> exponent ;
			a.setEqnElement( coefficient, exponent ) ;
		}
		if ( num != 0 )
			cin >> num2 ;
		for ( int i = 0 ; i < num2 ; i++ ) {
			cin >> coefficient >> exponent ;
			b.setEqnElement( coefficient, exponent ) ;
		}
		cout << "case:" << ++cases << endl ;
		// a.PrintEqn() ;
		// b.PrintEqn() ;
		rADD = a+b ;
		rMUL = a*b ;
		cout << "ADD" << endl ;
		rADD.PrintEqn() ;
		cout << "MULTIPLY" << endl ;
		rMUL.PrintEqn() ;
		a.Clear() ;
		b.Clear() ;
		rADD.Clear() ;
		rMUL.Clear() ;
		cin >> num ;
		if ( num == 0 )
			cin >> num2 ;
	}
	system("pause") ;
}

