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
	int cpu ;
	int abort ;
	int delay ;
	
}AbortD;

typedef struct DoneData {
	
	int jobID ;
	int cpu ;
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
		
		int GetLength() {
			
			return count ;
			
		}
	
		Data getFront() {
			return queue[head%size] ;
		}
};

class JobList {
	
	private :

		vector<Data> list ;
		vector<AbortD> abort ;
		vector<DoneD> done ;
		// Queue abort ;
		Queue queue1 ;
		Queue queue2 ;
  		
	public :
		
		JobList() {
			;
		}
  	
  		// *************************************************
  	
		void SetStart() {
			
			queue1.Set(3) ;
			queue2.Set(3) ;
			
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
			} // for
			

		} // Print 
	
		// *************************************************
	
		void Write( int type ) {												
			// write down in the file
			// there are three type to be wrote
			if ( type == 1 ) {                                                  // type 1    
				cout << "JobID\tArrival\tDuration\tTimeOut\n" ;
				vector<Data>::iterator iter = list.begin();
				int i = 1 ;
				for( iter, i ; iter != list.end() ; ++iter, i++ ) {
					cout << iter->jobID << '\t' << iter->arrival << '\t' \
					<< iter->duration << '\t' << iter->timeOut << '\t' << endl ;
				} // for
			} // end if
			
			else {
				fout << "\t[ Abort Jobs ]\n" ;
				fout << "\tJobID\tCPU\tAbort\tDelay\n" ;                               // type 2
				vector<AbortD>::iterator iter = abort.begin() ;
				int i = 1 ;
				for ( iter, i ; iter != abort.end() ; ++iter, i++ )
					fout << "[" << i << "]\t" << iter->jobID << '\t' << iter->cpu << '\t' << iter->abort << '\t' << iter->delay << endl ; 
				fout << "\n\t[ Done Jobs ]\n" ;
				fout << "\tJobID\tCPU\tDeparture\tDelay\n" ;                           // type 3
				vector<DoneD>::iterator iiter = done.begin() ;
				i = 1 ;
				for ( iiter, i ; iiter != done.end() ; ++iiter, i++ )
					fout << "[" << i << "]\t" << iiter->jobID << '\t' << iiter->cpu << '\t' << iiter->departure << '\t' << iiter->delay << endl ;
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
	  		else if ( type == 2 )
	  			write = "SQF" ; //""write = "output" ;
	  		else
	  			write = "EQF" ;
				   
	  		write.append( num ) ;
	  		write.append( ".txt") ;
	  		fout.open( write.c_str(), ios::out );               // file open / out & append ( ios::out|ios::app )
      		// fout << "Hello!! success" << endl;               // output data in file
      		Write( type ) ;
      		fout.close() ;
      		cout << "\nFile build : " << fout << endl ;
      		
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
		

		void StoreDone( Data job, int cpu, int & clock, bool UpClockWithArrival ) {
			
			DoneD doneData ;
			if( UpClockWithArrival )
				clock = job.arrival + job.duration ;  
			else
				clock = clock + job.duration ;
			doneData.jobID = job.jobID ;
			doneData.cpu = cpu ;
			doneData.departure = clock ;
			doneData.delay = clock - job.arrival - job.duration ;
			done.push_back( doneData ) ;
			
		}	
		// *************************************************
		
		void StoreAbort( int jobID, int cpu, int abortTime, int delayTime ) {
			
			AbortD abortData ;
			abortData.jobID = jobID ;
			abortData.cpu = cpu ;
			abortData.abort = abortTime ;
			abortData.delay = delayTime ; 
			abort.push_back( abortData ) ;
			
		}
		
		// *************************************************
		
		void Simulate() {
   
			int i = 2 ;
			int clock1 = 0, clock2 = 0 ;
			Data process1 ;
			Data process2 ;
			process1 = list[0] ;  
			process2 = list[1] ;               
			// first item and second item can be processed immediately                            
			StoreDone( process1, 1, clock1, true ) ;
			StoreDone( process2, 2, clock2, true ) ;
			// first item and second item can be processed immediately
			
			while ( !queue1.IsEmpty() || !queue2.IsEmpty() || i < list.size() ) {
				if ( clock1 > list[i].arrival && clock2 > list[i].arrival && i < list.size() ) {       // anyone waiting to be dealed
					if ( !queue1.IsFull() || !queue2.IsFull() ) {         							   // queue maximum is 3
						if ( queue1.GetLength() <= queue2.GetLength() ) 							   // enqueue to the shortest queue
							queue1.EnQueue( list[i] ) ;
						else
							queue2.EnQueue( list[i] ) ;
					} // end if
					else 																			   // if there are any data exceed three things then abort it
						StoreAbort( list[i].jobID, 0, list[i].arrival, 0 ) ;
					i++ ;																			   // next data
				} // end if
				else if ( clock1 == list[i].arrival && i < list.size() ) {							   // if the data and the time of cpu1 is exactly the same
					while ( !queue1.IsEmpty() && clock1 == list[i].arrival ) {						   // clear cpu1 until the time has been changed
						process1 = queue1.DeQueue() ;
						if ( clock1+process1.duration <= process1.timeOut )    						   // if clock + dealing time less than timeout
							StoreDone( process1, 1, clock1, false ) ;
						else 
							StoreAbort( process1.jobID, 1, clock1, clock1-process1.arrival ) ;
					} // end while
					if ( clock2 <= list[i].arrival ) {												   // if cpu2's process time is less than the current time( means it must be done )
						while ( !queue2.IsEmpty() && clock2 <= list[i].arrival ) {  				   // clear cpu2 blablabla
							process2 = queue2.DeQueue() ;
							if ( clock2+process2.duration <= process2.timeOut )    				   	   // if clock + dealing time less than timeout
								StoreDone( process2, 2, clock2, false ) ;
							else 
								StoreAbort( process2.jobID, 2, clock2, clock2-process2.arrival ) ;

						} // end while
					} // end if
					if ( clock1 <= list[i].arrival && queue1.IsEmpty() ) 
						StoreDone( list[i], 1, clock1, true ) ;           							   // regard this data as first one to be dealed
						// i++; 
					else if ( clock2 <= list[i].arrival && queue2.IsEmpty() ) 
						StoreDone( list[i], 2, clock2, true ) ;	            						   // regard this data as first one to be dealed
						// i++ ;
					else if ( queue1.GetLength() <= queue2.GetLength() ) 							   // choose the shortest one
						queue1.EnQueue( list[i] ) ;
					else
						queue2.EnQueue( list[i] ) ;
					i++; 
				}
				else if ( clock2 == list[i].arrival && i < list.size() ) {							   // if the data and the time of cpu2 is exactly the same
					while ( !queue2.IsEmpty() && clock2 == list[i].arrival ) {                         // clear cpu2 first blablabla
						process2 = queue2.DeQueue() ;
						if ( clock2+process2.duration <= process2.timeOut )      					   // if clock + dealing time less than timeout
							StoreDone( process2, 2, clock2, false ) ;  
						else 
							StoreAbort( process2.jobID, 2, clock2, clock2-process2.arrival ) ;
					} // end while
					if ( clock1 <= list[i].arrival ) {												   // if cpu1's process time is less than the current time( means it must be done )
						while ( !queue1.IsEmpty() && clock1 <= list[i].arrival ) {
							process1 = queue1.DeQueue() ;
							if ( clock1+process1.duration <= process1.timeOut )     				   // if clock + dealing time less than timeout
								StoreDone( process1, 1, clock1, false ) ; 
							else 
								StoreAbort( process1.jobID, 1, clock1, clock1-process1.arrival ) ;

						} // end while
					} // end if
					if ( clock1 <= list[i].arrival && queue1.IsEmpty() ) 
						StoreDone( list[i], 1, clock1, true ) ;		           						   // regard this data as first one to be dealed
					else if ( clock2 <= list[i].arrival && queue2.IsEmpty() ) 
						StoreDone( list[i], 2, clock2, true ) ;	            						   // regard this data as first one to be dealed
					else if ( queue1.GetLength() <= queue2.GetLength() ) 							   // choose the shortest one
						queue1.EnQueue( list[i] ) ;
					else
						queue2.EnQueue( list[i] ) ;
					i++; 
				}
				else if ( list[i].arrival > clock1 && list[i].arrival > clock2 && ( !queue1.IsEmpty() || !queue2.IsEmpty() ) ) {  
					if ( clock1 <= clock2 ) {														   // both cpu is unusedddd
				 		if ( !queue1.IsEmpty() ) {
							process1 = queue1.DeQueue() ;
							if ( clock1+process1.duration <= process1.timeOut )     				   // if clock + dealing time less than timeout
								StoreDone( process1, 1, clock1, false ) ;
							else 
								StoreAbort( process1.jobID, 1, clock1, clock1-process1.arrival ) ;
						} // end if
						else {
							process2 = queue2.DeQueue() ;
							if ( clock2+process2.duration <= process2.timeOut )      				   // if clock + dealing time less than timeout
								StoreDone( process2, 2, clock2, false ) ;
							else 
								StoreAbort( process2.jobID, 2, clock2, clock2-process2.arrival ) ;
						}
					} // end if
					else {
						if ( !queue2.IsEmpty() ) {
							process2 = queue2.DeQueue() ;
							if ( clock2+process2.duration <= process2.timeOut )      				   // if clock + dealing time less than timeout
								StoreDone( process2, 2, clock2, false ) ;
							else 
								StoreAbort( process2.jobID, 2, clock2, clock2-process2.arrival ) ;

						} // end if
						else {
							process1 = queue1.DeQueue() ;
							if ( clock1+process1.duration <= process1.timeOut )     				   // if clock + dealing time less than timeout
								StoreDone( process1, 1, clock1, false ) ;
							else 
								StoreAbort( process1.jobID, 1, clock1, clock1-process1.arrival ) ;

						} // end else
					} // end else
				} // end else if
				else if ( clock1 < list[i].arrival && queue1.IsEmpty() && i < list.size() ) { 		   // if there are no data line up in the queue
					StoreDone( list[i], 1, clock1, true ) ;		            						   // regard this data as first one to be dealed
					i++;				
				}
				else if ( clock2 < list[i].arrival && queue2.IsEmpty() && i < list.size() ) {		   // if there are no data line up in the queue
					StoreDone( list[i], 2, clock2, true ) ;	 	            						   // regard this data as first one to be dealed
					i++;
				}
				
				else if ( ( clock1 <= clock2 && !queue1.IsEmpty() ) || ( clock1 > clock2 && !queue1.IsEmpty() && queue2.IsEmpty() ) ) {
					process1 = queue1.DeQueue() ;													   // start to process the next data in queue
					if ( clock1+process1.duration <= process1.timeOut )      						   // if clock + dealing time less than timeout
						StoreDone( process1, 1, clock1, false ) ;
					else 
						StoreAbort( process1.jobID, 1, clock1, clock1-process1.arrival ) ;
				}
				else {
					process2 = queue2.DeQueue() ;
					if ( clock2+process2.duration <= process2.timeOut )      						   // if clock + dealing time less than timeout
						StoreDone( process2, 2, clock2, false ) ;
					else 
						StoreAbort( process2.jobID, 2, clock2, clock2-process2.arrival ) ;
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
		
		void Simulate2() {
			
			int i = 2 ;
			int clock1 = 0, clock2 = 0 ;
			Data process1 ;
			Data process2 ;
			process1 = list[0] ;  
			process2 = list[1] ;               
			// first item and second item can be processed immediately                            
			StoreDone( process1, 1, clock1, true ) ;
			StoreDone( process2, 2, clock2, true ) ;
			// first item and second item can be processed immediately
			
			
			while ( !queue1.IsEmpty() || !queue2.IsEmpty() || i < list.size() ) {
				if ( clock1 > list[i].arrival && clock2 > list[i].arrival && i < list.size() ) {       // anyone waiting to be dealed
					if ( clock1 <= clock2 ) {         // queue maximum is five
						if ( !queue1.IsFull() ) 
							queue1.EnQueue( list[i] ) ;
						else 
							StoreAbort( list[i].jobID, 1, list[i].arrival, 0 ) ;
					} // end if
					else {                                                // abort it
						if ( !queue2.IsFull() ) 
							queue2.EnQueue( list[i] ) ;
						else 
							StoreAbort( list[i].jobID, 2, list[i].arrival, 0 ) ;
					} // end else
					i++ ;
				} // end if
				else if ( clock1 == list[i].arrival && i < list.size() ) {							   // if the data and the time of cpu1 is exactly the same
					while ( !queue1.IsEmpty() && clock1 == list[i].arrival ) {						   // clear cpu1 until the time has been changed
						process1 = queue1.DeQueue() ;
						if ( clock1+process1.duration <= process1.timeOut )    						   // if clock + dealing time less than timeout
							StoreDone( process1, 1, clock1, false ) ;
						else 
							StoreAbort( process1.jobID, 1, clock1, clock1-process1.arrival ) ;
					} // end while
					if ( clock2 <= list[i].arrival ) {												   // if cpu2's process time is less than the current time( means it must be done )
						while ( !queue2.IsEmpty() && clock2 <= list[i].arrival ) {  				   // clear cpu2 blablabla
							process2 = queue2.DeQueue() ;
							if ( clock2+process2.duration <= process2.timeOut )    				   	   // if clock + dealing time less than timeout
								StoreDone( process2, 2, clock2, false ) ;
							else 
								StoreAbort( process2.jobID, 2, clock2, clock2-process2.arrival ) ;

						} // end while
					} // end if
					if ( clock1 <= list[i].arrival && queue1.IsEmpty() ) 
						StoreDone( list[i], 1, clock1, true ) ;           							   // regard this data as first one to be dealed
						// i++; 
					else if ( clock2 <= list[i].arrival && queue2.IsEmpty() ) 
						StoreDone( list[i], 2, clock2, true ) ;	            						   // regard this data as first one to be dealed
						// i++ ;
					else if ( queue1.GetLength() <= queue2.GetLength() ) 							   // choose the shortest one
						queue1.EnQueue( list[i] ) ;
					else
						queue2.EnQueue( list[i] ) ;
					i++; 
				}
				else if ( clock2 == list[i].arrival && i < list.size() ) {							   // if the data and the time of cpu2 is exactly the same
					while ( !queue2.IsEmpty() && clock2 == list[i].arrival ) {                         // clear cpu2 first blablabla
						process2 = queue2.DeQueue() ;
						if ( clock2+process2.duration <= process2.timeOut )      					   // if clock + dealing time less than timeout
							StoreDone( process2, 2, clock2, false ) ;  
						else 
							StoreAbort( process2.jobID, 2, clock2, clock2-process2.arrival ) ;
					} // end while
					if ( clock1 <= list[i].arrival ) {												   // if cpu1's process time is less than the current time( means it must be done )
						while ( !queue1.IsEmpty() && clock1 <= list[i].arrival ) {
							process1 = queue1.DeQueue() ;
							if ( clock1+process1.duration <= process1.timeOut )     				   // if clock + dealing time less than timeout
								StoreDone( process1, 1, clock1, false ) ; 
							else 
								StoreAbort( process1.jobID, 1, clock1, clock1-process1.arrival ) ;

						} // end while
					} // end if
					if ( clock1 <= list[i].arrival && queue1.IsEmpty() ) 
						StoreDone( list[i], 1, clock1, true ) ;		           						   // regard this data as first one to be dealed
					else if ( clock2 <= list[i].arrival && queue2.IsEmpty() ) 
						StoreDone( list[i], 2, clock2, true ) ;	            						   // regard this data as first one to be dealed
					else if ( queue1.GetLength() <= queue2.GetLength() ) 							   // choose the shortest one
						queue1.EnQueue( list[i] ) ;
					else
						queue2.EnQueue( list[i] ) ;
					i++; 
				}
				else if ( list[i].arrival > clock1 && list[i].arrival > clock2 && ( !queue1.IsEmpty() || !queue2.IsEmpty() ) ) {  
					if ( clock1 <= clock2 ) {														   // both cpu is unusedddd
				 		if ( !queue1.IsEmpty() ) {
							process1 = queue1.DeQueue() ;
							if ( clock1+process1.duration <= process1.timeOut )     				   // if clock + dealing time less than timeout
								StoreDone( process1, 1, clock1, false ) ;
							else 
								StoreAbort( process1.jobID, 1, clock1, clock1-process1.arrival ) ;
						} // end if
						else {
							process2 = queue2.DeQueue() ;
							if ( clock2+process2.duration <= process2.timeOut )      				   // if clock + dealing time less than timeout
								StoreDone( process2, 2, clock2, false ) ;
							else 
								StoreAbort( process2.jobID, 2, clock2, clock2-process2.arrival ) ;
						}
					} // end if
					else {
						if ( !queue2.IsEmpty() ) {
							process2 = queue2.DeQueue() ;
							if ( clock2+process2.duration <= process2.timeOut )      				   // if clock + dealing time less than timeout
								StoreDone( process2, 2, clock2, false ) ;
							else 
								StoreAbort( process2.jobID, 2, clock2, clock2-process2.arrival ) ;

						} // end if
						else {
							process1 = queue1.DeQueue() ;
							if ( clock1+process1.duration <= process1.timeOut )     				   // if clock + dealing time less than timeout
								StoreDone( process1, 1, clock1, false ) ;
							else 
								StoreAbort( process1.jobID, 1, clock1, clock1-process1.arrival ) ;

						} // end else
					} // end else
				} // end else if
				else if ( clock1 < list[i].arrival && queue1.IsEmpty() && i < list.size() ) { 		   // if there are no data line up in the queue
					StoreDone( list[i], 1, clock1, true ) ;		            						   // regard this data as first one to be dealed
					i++;				
				}
				else if ( clock2 < list[i].arrival && queue2.IsEmpty() && i < list.size() ) {		   // if there are no data line up in the queue
					StoreDone( list[i], 2, clock2, true ) ;	 	            						   // regard this data as first one to be dealed
					i++;
				}
				
				else if ( ( clock1 <= clock2 && !queue1.IsEmpty() ) || ( clock1 > clock2 && !queue1.IsEmpty() && queue2.IsEmpty() ) ) {
					process1 = queue1.DeQueue() ;													   // start to process the next data in queue
					if ( clock1+process1.duration <= process1.timeOut )      						   // if clock + dealing time less than timeout
						StoreDone( process1, 1, clock1, false ) ;
					else 
						StoreAbort( process1.jobID, 1, clock1, clock1-process1.arrival ) ;
				}
				else {
					process2 = queue2.DeQueue() ;
					if ( clock2+process2.duration <= process2.timeOut )      						   // if clock + dealing time less than timeout
						StoreDone( process2, 2, clock2, false ) ;
					else 
						StoreAbort( process2.jobID, 2, clock2, clock2-process2.arrival ) ;
				} // end else
			} // end while 
		}
		
};


	
int main() {
	
	JobList jobList ;                          	
	std::string num ;
	int command ;        
	clock_t timeR, timeS, timeW  ;
	cout << "\n*** Simulate FIFO Queues for dual CPUs ***\n\
* 0. Quit                                *\n\
* 1. Shortest Queue First (SQF) strategy *\n\
* 2. Earliest Queue First (EQF) strategy *\n\
------------------------------------------\n\
Input a command(0, 1, 2) : " ;
	cin >> command ;
	while ( command != 0 ) {
		if ( command == 1 ) {
			cout << "Input a file number :" ;	
			cin >> num ;
			timeR = clock() ;
	    	if ( !jobList.LoadIn( num ) )
				cout << "Input file does not exist, please try again!" << endl ;
			else  {
        		jobList.ShellSort() ;
        		jobList.Write( 1 ) ;
        		jobList.SetStart();
				jobList.Simulate() ;
				jobList.WriteOut( num , 2 ) ;
        	}
        } // end if
		
		else if ( command == 2 ) {
			cout << "Input a file number :" ;	
			cin >> num ;
			timeR = clock() ;
	    	if ( !jobList.LoadIn( num ) )
				cout << "Input file does not exist, please try again!" << endl ;
			else  {
        		jobList.ShellSort() ;
        		jobList.SetStart();
				jobList.Simulate2() ;
				jobList.WriteOut( num , 3 ) ;
        	}
		} // end else if
    
		else
			cout << "Couldn't find command, please try again!" << endl ;
			
		cout << "\n*** Simulate FIFO Queues for dual CPUs ***\n\
* 0. Quit                                *\n\
* 1. Shortest Queue First (SQF) strategy *\n\
* 2. Earliest Queue First (EQF) strategy *\n\
------------------------------------------\n\
Input a command(0, 1, 2) : " ;
		cin >> command ;
		num.clear() ;                                    // content clear
		jobList.VectorClear() ;
	} // end while
  
} // main()





