
/*  資訊二甲 
 *  第 10 組 
 *  陳少洋
 *  10527130
 *  林亞吟
 *  10527132 
 */ 

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream> 
#include <vector> 
#include <ctime> 
#include <iomanip>

using namespace std;
fstream fin ;                             // file input
fstream fout ;                            // file output

typedef struct Data {
	
	int jobID ;
	int arrival ;
	int duration ;
	int timeOut ;
	
}Data;

typedef struct AbortData {
	
	int jobID ;
	int abort ;
	int delay ;
	
}AbortD;

typedef struct DoneData {
	
	int jobID ;
	int departure ;
	int delay ;
	
}DoneD;

class Queue{
	
	private :
		
		Data *queue ;
		int head ;                              
		int rear ;
		int size ;
		int count ;
	
	public :
		
		Queue() {
			;
		}
		
		// ----------------------
		
		void Set( int i ) {
			
			head = -1 ;
			rear = -1 ;
			queue = new Data[i] ;
			size = i ;
			count = 0 ;
			
		}
		
		// ----------------------
		
		void EnQueue( Data data ) {                          // add data at the end
		
			if ( IsFull() )
				cout << "full" << endl ;
			else {
				rear = ( rear+1 )%size ;
				queue[rear] = data ;
				count++ ;
			} // end else
			
		} // EnQueue
		
		// ----------------------
		
		Data DeQueue() {                                    // drop data at the first
		
			if ( IsEmpty() ) 
				cout << "empty" << endl ;
			else {
				head = ( head+1 )%size ;
				count-- ;
				return queue[head] ;
			}
			
		} // DeQueue
		
		// ----------------------
		
		bool IsFull() {
			
			return count == size ;
			
		}
		
		// ----------------------
		
		bool IsEmpty() {
			
			return count == 0 ;
			
		}
	
};

class JobList {
	
	private :

		vector<Data> list ;
		vector<AbortD> abort ;
		vector<DoneD> done ;
		// Queue abort ;
		Queue queue ;
  	
	public :
		
		JobList() {
			;
		}
  	
  		// *************************************************
  	
		void SetStart() {
			
			queue.Set(5) ;
			
		}
	
		// *************************************************
	
		void Read() {    
		
			Data temp ;  
			string s ;             
			int i = 0 ;
	  		getline( fin, s ) ;							// first line will not input list
	  		while( fin >> i ) {
	  			temp.jobID = i ;
	  			fin >> temp.arrival ;
	  			fin >> temp.duration ;
	  			fin >> temp.timeOut ;
	  			list.push_back( temp ) ;
			  } // while
	  		
		} // Read()
	
		// *************************************************
	
		void Print() {
			
			printf( "\n*****There are %d jobs in total.*****\n", list.size() ) ;
			printf( "\tJobID\tArrival\tDuration\tTimeOut\n" ) ;
			vector<Data>::iterator iter = list.begin();
			int i = 1 ;
			for( iter, i ; iter != list.end() ; ++iter, i++ ) {
				printf("(%1d)\t%d\t%d\t%d\t%d\t\n", i, iter->jobID, iter->arrival, iter->duration, iter->timeOut ) ;
			//	cout << iter->jobID << '\t' << iter->arrival << '\t' \ 
			//	<< iter->duration << '\t' << iter->timeOut << '\t' << endl ;
			} // for
			

		} // Print 
	
		// *************************************************
	
		void Write( int type ) {												
			// write down in the file
			// there are three type to be wrote
			if ( type == 1 ) {                                                  // type 1    
				fout << "JobID\tArrival\tDuration\tTimeOut\n" ;
				vector<Data>::iterator iter = list.begin();
				int i = 1 ;
				for( iter, i ; iter != list.end() ; ++iter, i++ ) {
					//printf("(%1d)\t%d\t%d\t%d\t%d\t\n", i, iter->jobID, iter->arrival, iter->duration, iter->timeOut ) ;
					fout << iter->jobID << '\t' << iter->arrival << '\t' \
					<< iter->duration << '\t' << iter->timeOut << '\t' << endl ;
				} // for
			} // end if
			
			else {
				fout << "\t[ Abort Jobs ]\n" ;
				fout << "\tJobID\tAbort\tDelay\n" ;                               // type 2
				vector<AbortD>::iterator iter = abort.begin() ;
				int i = 1 ;
				for ( iter, i ; iter != abort.end() ; ++iter, i++ )
					fout << "[" << i << "]\t" << iter->jobID << '\t' << iter->abort << '\t' << iter->delay << endl ; 
				fout << "\n\t[ Done Jobs ]\n" ;
				fout << "\tJobID\tDeparture\tDelay\n" ;                           // type 3
				vector<DoneD>::iterator iiter = done.begin() ;
				i = 1 ;
				for ( iiter, i ; iiter != done.end() ; ++iiter, i++ )
					fout << "[" << i << "]\t" << iiter->jobID << '\t' << iiter->departure << '\t' << iiter->delay << endl ;
				// printf( "%.2f", AVEdelay() ) ;
				// printf( "%.2f", SuccessRate() ) ;
				fout << std::fixed << std::setprecision(2) << "\n[ Average Delay ]\n" << AVEdelay() << "ms" << endl ;
				fout << std::fixed << std::setprecision(2) << "\n[ Success Rate ]\n" << SuccessRate() << "%" << endl ;
			} // end else
			
		} // Write()
	
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
	
		void WriteOut( std::string num, int type ) {
		
			std::string write ;
			if ( type == 1 )
	  			write = "sort" ;
	  		else
	  			write = "output" ;
				   
	  		write.append( num ) ;
	  		write.append( ".txt") ;
	  		fout.open( write.c_str(), ios::out );               // file open / out & append ( ios::out|ios::app )
      		// fout << "Hello!! success" << endl;               // output data in file
      		Write( type ) ;
      		fout.close() ;
      		cout << "File build : " << fout << endl ;
      		
		} // WriteOut()
	
		// *************************************************
		
		void ShellSort() {
			
			bool done = true ;
			int size = list.size(), gap = 0 , i = 0 ;
			for( gap = size / 2 ; gap >= 1 ; gap /= 2 ) {
				for( i = gap ; i < size ; i += 1 ){
					Data temp = list[i] ;
					int j = 0 ;
					for( j = i ; j >= gap && list[j-gap].arrival >= temp.arrival ; j -= gap) {
						if ( list[j-gap].arrival == temp.arrival && list[j-gap].jobID < temp.jobID )
							done = false ;                                          // compare arrival time  
						else                                                        // if they were the same time
				            swap( list[j], list[j-gap] );                           // compare their jobID
		        	}
            		//  put temp (the original a[i]) in its correct location
            		if ( done )
	          			swap( list[j], temp ) ;
	          		done = true ;
				} // end for
			} // end for
			
		} // ShellSort()
		
		// *************************************************
		
		int GetSize() {
			
			return list.size() ;
			
		}
    
    	// *************************************************
    
    	void VectorClear() {
    		
    		list.clear() ;
    		abort.clear() ;
    		done.clear() ;
    		
		}
		
		// *************************************************
		
		void Simulate() {
   
			int clock = 0 ;
			int i = 0 ;
			Data process ;
			AbortD abortData ;
			DoneD doneData ;
			process = list[0] ;  
			i++ ;                                            // first item
			clock = process.arrival+process.duration ;       // first item always be dealed
			doneData.jobID = process.jobID ;
			doneData.departure = clock ;
			doneData.delay = 0 ;
			done.push_back( doneData ) ;
			while (  !queue.IsEmpty() || i < list.size() ) {
				if ( clock > list[i].arrival && i < list.size() ) {       // anyone waiting to be dealed
					if ( !queue.IsFull() )                                // queue maximum is five
						queue.EnQueue( list[i] ) ;                        // if there are any data exceed five things then 
					else {                                                // abort it
						abortData.jobID = list[i].jobID ;
						abortData.abort = list[i].arrival ;
						abortData.delay = 0 ; 
						abort.push_back( abortData ) ;
					} // end else
					i++ ;
				} // end if
				else if ( clock == list[i].arrival && !queue.IsFull() ) { // if the clock and arrival time is exactly the same
					queue.EnQueue( list[i] ) ;                            // and the queue is not full then enter data to queue
					i++ ;
				} // end else if
				else if ( clock < list[i].arrival && queue.IsEmpty() ) {  // if there are no one line up in the queue
					clock = list[i].arrival+list[i].duration ;            // regard this data as first one to be dealed
					doneData.jobID = list[i].jobID ;
					doneData.departure = clock ;
					doneData.delay = 0 ;
					done.push_back( doneData ) ;
					i++;				
					}
				else {
					process = queue.DeQueue() ;
					if ( clock+process.duration <= process.timeOut ) {    // if clock + dealing time less than timeout
						doneData.jobID = process.jobID ;                  // the data will be dealed
						doneData.departure = clock+process.duration ;
						doneData.delay = clock-process.arrival ;
						clock = clock+process.duration ;
						done.push_back( doneData ) ;
					} // end if
					else {
						abortData.jobID = process.jobID ;                 // or it will be aborted
						abortData.abort = clock ;
						abortData.delay = clock-process.arrival ;
						abort.push_back( abortData ) ;
					} // end else
				} // end else
			} // end while 
		}
		
		// *************************************************
		
		float AVEdelay() {
			int i ;
			float time = 0 ;
			for ( i = 0 ; i < abort.size() ; i++ ) 
				time += abort[i].delay ;
			for ( i = 0 ; i < done.size() ; i ++ )
				time += done[i].delay ;
			i = abort.size()+done.size() ;
			return time/=i ;
		}
		
		// *************************************************
		
		float SuccessRate() {
			
			float i = done.size() ;
			return i/(done.size()+abort.size())*100;
			
		}
		
};


	
int main() {
	
	JobList jobList ;                          	
	std::string num ;
	int command ;        
	bool done = false ;
	clock_t timeR, timeS, timeW  ;
	cout << "******** Shell Sort & FIFO Queue ********\n\
* 0. Quit				*\n\
* 1. Sort a file by Shell Sort		*\n\
* 2. Simulate one FIFO queue		*\n\
-----------------------------------------\n\
Input a command(0, 1, 2) : " ;
	cin >> command ;
	while ( command != 0 ) {
		if ( command == 1 ) {
			if ( done ) {                                           // to avoid idiot
				num.clear() ;
				jobList.VectorClear() ;
			} // end if
			done = true ;	
			cout << "Input a file number :" ;	
			cin >> num ;
			timeR = clock() ;
	    	if ( !jobList.LoadIn( num ) )
				cout << "Input file does not exist, please try again!" << endl ;
			else  {
				timeR = clock() - timeR ;
        		jobList.Print() ;
        		timeS = clock() ;
        		jobList.ShellSort() ;
        		timeS = clock() - timeS ;
        		timeW = clock() ;
        		jobList.WriteOut( num, 1 ) ;
        		timeW = clock() - timeW ;
        		cout << endl ;
        		cout << "Reading data : " << timeR << "ms" << endl ;          // time Read
        		cout << "Sorting data : " << timeS << "ms" << endl ;          // time Sort
        		cout << "Writing data : " << timeW << "ms" << endl ;          // time Write
        	}
        } // end if
		
		else if ( command == 2 ) {
			if ( done ) {
				jobList.SetStart();
				jobList.Simulate() ;
				jobList.WriteOut( num , 2 ) ;
				num.clear() ;                                    // content clear
				jobList.VectorClear() ;
				done = false ;
			} // end eif
			else
				cout << "Please sort the data first." ;
		} // end else if
    
		else
			cout << "Couldn't find command, please try again!" << endl ;
			
		cout << "\n******** Shell Sort & FIFO Queue ********\n\
* 0. Quit				*\n\
* 1. Sort a file by Shell Sort		*\n\
* 2. Simulate one FIFO queue		*\n\
-----------------------------------------\n\
Input a command(0, 1, 2) : " ;
		cin >> command ;
	} // end while
  
} // main()




