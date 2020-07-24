/*  
 *  資工110
 *  B063040061 
 *  陳少洋
 *  Sep. 17, 2018
 *  Assignmenet #1.2 
 *  根據使用者輸入數字(1~50)，輸出1~n階層結果。 
 *  由於integer型態能表示的數字有限，故使用陣列存放數字之型式儲存。 
 */ 

#include <iostream>
#define MAX	100

using namespace std;

class BigNumber {
	
	private :
		int bNum[MAX] ;      // using int array to store the factorial result 
		int digit ;          // the digit of the factorial result
		
		
	public :
		BigNumber() {
			// constructor
			digit = 0 ;
			// bNum[MAX] = {0} ; this statement same as below (loop)
			for ( int i = 0 ; i < MAX ; i++ )
			 	bNum[i] = 0 ;
		}
		
		//*************************************************
		
		void Factorial( int order ) {
			// computing n! result
			// order is the target of factorial level
			bNum[0] = 1 ;    // set the number as 1
			digit = 1 ;      // 1 digit already
			for ( int i = 1 ; order >= i ; i++ ) 
				BigNumberMult( i ) ;
				// bNum = bNum*order ;
		}
		
		//*************************************************
		
		void BigNumberMult( int order ) {
			// using the function to multiple int array instead of using '*' 
			// order is the target of factorial level
			int i ;      // walking iterater
			for ( i = 0 ; i < digit ; i++ )               // bNum[i] != -1
				bNum[i] *= order ;
			for ( i = 0 ; i < digit ; i++ ) {             // bNum[i] != -1
				if ( i+1 == digit && bNum[i]/10 > 0 )     // bNum[i+1] == -1
					digit++ ;                             // bNum[i+1]++ ;
				bNum[i+1] += bNum[i]/10 ;
				bNum[i] %= 10 ;
			}
			cout << order << "!=" ;
			PrintFac() ;
		}
		
		//*************************************************
		
		void PrintFac() {
			// print out
			for ( int i = digit-1 ; i >= 0 ; i-- )
				cout << bNum[i] ;
			cout << endl ;
		}
		
		//*************************************************
		
		void Clear() {
			// clear the result to get new target
			digit = 0 ;
			// bNum[MAX] = {0} ;
			for ( int i = 0 ; i < MAX ; i++ )
				bNum[i] = 0 ;
		}
		
};

int main() {
	int fac ;           // fac is the target of factorial level
	cin >> fac ;
	BigNumber facNum ;  // factorial number
	while ( fac != 0 ) {
		facNum.Factorial( fac ) ;
		// test.PrintFac() ;
		cout << endl ;
		facNum.Clear() ;
		cin >> fac ;
	}
	system("pause") ; 
	return 0 ;
} // main()


 
