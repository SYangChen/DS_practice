/*  
 *  資工110
 *  B063040061 
 *  陳少洋
 *  Sep. 30, 2018
 *  Assignmenet #2
 *  以C++ class製作一個集合，使其擁有聯集、交集、差集、包含、屬於等功能， 
 *  根據使用者輸入之集合A、集合B及一個欲判斷屬於之字元x，分別輸出A+B、A*B、
 *	A-B、B-A、A>=B、B>=A、x in B、x in A等功能之判斷結果。 
 */ 
#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX 256

using namespace std ;

bool compare( char a, char b ) {
	// build this compare function for sort
	return a <= b ;
}

class Set {
	
	private :
		char set[MAX] ;
		
	public :
		Set() {
			// reset
			memset( set, '\0', MAX ) ;
		} // Set()
		
		//*************************************************
		
		void setSet( char *inputSet ) {
			// set = inputSet ;
			// avoid repeat item
			for ( int i = 0, s = 0 ; inputSet[i] != '\0' ; i++ ) {
				if ( !( i != 0 && inputSet[i] == set[s-1] ) ) {
					set[s] = inputSet[i] ;
					s++ ;
				}
			}
		} // setSet()
		
		//*************************************************
		
		char *getSet() {
			return set ;
		} // getSet()
		
		//*************************************************
		
		Set operator+( Set &b ) {
			// find setA and setB all item till the end of those
			Set union_ ;                    // union set
			int i = 0, j = 0, k = 0 ;		// index for 3 set
			while( set[i] != '\0' || b.set[j] != '\0' ) {
				if ( set[i] == '\0' ) {
					for ( ; b.set[j] != '\0' ; j++, k++ )
						union_.set[k] = b.set[j] ;
				}
				else if ( b.set[j] == '\0' ) {
					for ( ; set[i] != '\0' ; i++, k++ )
						union_.set[k] = set[i] ;
				}
				else if ( set[i] == b.set[j] ) {
					union_.set[k] = set[i] ;
					i++ ;
					j++ ;
				}
				else if ( set[i] < b.set[j] ) {
					union_.set[k] = set[i] ;
					i++ ;
				}
				else {
					union_.set[k] = b.set[j] ;
					j++ ;
				}
				k++ ;
			}
			return union_ ;
		} // operator+ overloading
		
		//*************************************************
		
		Set operator*( Set &b ) {
			// find the same item in setA and setB
			Set intersection ;				// intersection set
			int i = 0, j = 0 , k = 0 ;		// index for 3 set
			while ( set[i] != '\0' && b.set[j] != '\0' ) {
				if ( set[i] == b.set[j] ) {
					intersection.set[k] = set[i] ;
					k++ ;
					i++ ;
					j++ ;
				}
				else if ( set[i] < b.set[j] )
					i++ ;
				else
					j++ ;
			}
			return intersection ;
		} // operator* overloading
		
		//*************************************************
		
		Set operator-( Set &b ) {
			// find the difference of setA and setB
			Set difference ;				// difference set
			int i = 0, j = 0 , k = 0 ;		// index of 3 set
			while ( set[i] != '\0' ) {
				if ( b.set[j] == '\0' ) {
					for ( ; set[i] != '\0' ; i++, k++ )
						difference.set[k] = set[i] ;
				}
				else if ( set[i] < b.set[j] ) {
					difference.set[k] = set[i] ;
					k++ ;
					i++ ;
				}
				else if ( set[i] > b.set[j] )
					j++ ;
				else {
					i++ ;
					j++ ;
				}
			}
			return difference ;
		} // operator- overloading
		
		//*************************************************
		
		bool operator>=( Set &b ) {
			// find whether setA is contain setB than return boolean
			int i = 0 , j = 0 ;				// index of setA、B
			while ( b.set[j] != '\0' ) {
				if ( set[i] == '\0' )
					return false ;
				else if ( set[i] == b.set[j] ) {
					i++ ;
					j++ ;
				}
				else if ( set[i] < b.set[j] )
					i++ ;
				else
					return false ;
			}
			return true ;
		} // operator>= overloading
		
		//*************************************************
		
		bool BelongTo( char ch ) {
			// find whether the charater is belong to the set
			for ( int i = 0 ; set[i] != '\0' ; i++ ) {
				if ( ch == set[i] )
					return true ;
			}
			return false ;
		} // BelongTo()
		
		//*************************************************
		
		void PrintSet( bool clear ) {
			// print out the set ( and clear the printed set )
			cout << "{" ;
			for( int i = 0 ; set[i] != '\0' ; i++ )
				cout << set[i] ;
			cout << "}" << endl ;
			if ( clear )
				Clear() ;
		} // PrintSet()
		
		//*************************************************
		
		void Clear() {
			// clear data in the set
			// set[0] = '\0' ;
			memset( set, '\0', MAX ) ;
		} // Clear()
		
}; 

int main() {
	char a[MAX], b[MAX] ;			// char array but didnt push to the set
	char test_ch ;					// testing charater
	int times, testCase = 0 ;		// times of case
	Set setA, setB, setC ;			// set A B C
	cin >> times ;
	while ( times-- ) {
		cin.ignore() ;				// ignore the '\n' ( trash )
		cin.getline( a, sizeof(a) ) ;
		cin.getline( b, sizeof(b) ) ;
		// cin >> test_ch ;			// using get instead of cin >> 
		cin.get( test_ch ) ;		// because it might be the char ' '
		sort( a, a+strlen(a), compare ) ;
		sort( b, b+strlen(b), compare ) ;
		setA.setSet( a ) ;			// push char array to set
		setB.setSet( b ) ;			// push char array to set
		cout << "Test case " << ++testCase << " :\n" ;
		cout << "A : " ;
		setA.PrintSet( false ) ;
		cout << "B : " ;
		setB.PrintSet( false ) ;
		cout << "A+B : " ;
		setC = setA+setB ;
		setC.PrintSet( true ) ;		// setC.Clear() ;
		cout << "A*B : " ;
		setC = setA*setB ;
		setC.PrintSet( true ) ;		// setC.Clear() ;
		cout << "A-B : " ;
		setC = setA-setB ;
		setC.PrintSet( true ) ;		// setC.Clear() ;
		cout << "B-A : " ;
		setC = setB-setA ;
		setC.PrintSet( true ) ;		// setC.Clear() ;
		cout << ( setA >= setB ? "A contains B\n" : "A does not contain B\n" ) ;
		cout << ( setB >= setA ? "B contains A\n" : "B does not contain A\n" ) ;
		// if ( setA.BelongTo( test_ch ) )
		cout << "'" << test_ch << ( setA.BelongTo( test_ch ) ? "' is in A\n" : "' is not in A\n" ) ;
		cout << "'" << test_ch << ( setB.BelongTo( test_ch ) ? "' is in B\n" : "' is not in B\n" );
		cout << endl ;
		setA.Clear() ;
		setB.Clear() ;				// set Clear
	}
}
