
// NAKUL AGGARWAL | 19CS10044

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct _job {
int jobId;
int startTime;
int jobLength;
int remLength;
} job;

typedef struct _jobPair {
int jobid_from;
int jobid_to;
} jobpair;

typedef struct _heap {
job list[MAX_SIZE];
int numJobs;
} heap;


void initHeap ( heap* H )
{
	H->numJobs = 0 ;
	return ;
}

void insertJob ( heap* H , job j )
{
	H->numJobs ++ ;
	H->list[H->numJobs] = j ;
	
	int child = H->numJobs ;
	int parent = child / 2 ;
	
	while ( child > 1 )
	{
		if ( H->list[parent].remLength < H->list[child].remLength )	break ;
		if ( H->list[parent].remLength == H->list[child].remLength )
			if ( H->list[parent].jobId < H->list[child].jobId ) break ;
		job temp = H->list[parent] ;
		H->list[parent] = H->list[child] ;
		H->list[child] = temp ;
		child = parent ;
		parent = child / 2 ;
	}
}

void minHeapify ( job* A , int i , int n )
{
	while ( 1 )
	{
		int childL = 2*i ;
		int childR = 2*i + 1 ;
		if ( childL > n )	return ;
		int m = ( (childR > n) || (A[childL].remLength <= A[childR].remLength) ) ? childL : childR ;
		if ( A[m].remLength > A[i].remLength )	return ;
		if ( A[m].remLength == A[i].remLength )
			if ( A[m].jobId < A[i].jobId ) return ;
		job temp = A[i] ;
		A[i] = A[m] ;
		A[m] = temp ;
		i = m ;
	}
}

int extractMinJob ( heap* H , job* j )
{
	if ( H->numJobs == 0 )	return -1 ;
	if ( H->numJobs == 1 )
	{
		*j = H->list[1] ;
		H->numJobs = 0 ;
		return 0 ;
	}
	job min = H->list[1] ;
	job temp = H->list[1] ;
	H->list[1] = H->list[H->numJobs] ;
	H->list[H->numJobs] = temp ;
	H->numJobs -- ;
	if ( H->numJobs > 1 ) minHeapify( H->list , 1 , H->numJobs ) ;
	*j = min ;
	return 0 ;
}

int notStarted ( int id , heap H )
{
	int s = H.numJobs ;
	for ( int i=1 ; i<=s ; i++ )
	{
		if ( H.list[i].jobId == id )
		{
			if ( H.list[i].remLength == H.list[i].jobLength )	return 1 ;
			return 0 ;
		}
	}
	return 1 ;
}

void decreaseKey ( heap* H , int jid )
{
	for ( int k=1 ; k<=H->numJobs ; k++ )
	{
		if ( H->list[k].jobId == jid )
		{
			H->list[k].remLength /= 2 ;
		    H->list[k].jobLength /= 2 ;
			int child = k ;
			int parent = child / 2 ;
			while ( child > 1 )
			{
				if ( H->list[parent].remLength < H->list[child].remLength )	break ;
				if ( H->list[parent].remLength == H->list[child].remLength )
					if ( H->list[parent].jobId < H->list[child].jobId ) break ;
				job temp = H->list[parent] ;
				H->list[parent] = H->list[child] ;
				H->list[child] = temp ;
				child = parent ;
				parent = child / 2 ;
			}
			break ;
		}
	}
}

void checkDependency ( jobpair* P , int jobId , int m , job* jl , int n , heap* H , int TIME )
{
	for ( int i=0 ; i<m ; i++ )
	{
		if ( P[i].jobid_from == jobId && notStarted(P[i].jobid_to, *H) )
		{
			int id = P[i].jobid_to ;
			for ( int j=0 ; j<n ; j++ )
			{
				if ( jl[j].jobId == id )
				{
					jl[j].remLength /= 2 ;
					jl[j].jobLength /= 2 ;
					if ( TIME < jl[j].startTime ) break ;
					decreaseKey( H , id ) ;
					break ;
				}
			}
		}	
	}
}

int allFinished ( int* b , int e )
{
	for ( int i=1 ; i<=e ; i++ )
		if ( ! b[i] )	return 0 ;
	return 1 ;
}

void scheduler ( job* jl , int n , jobpair* P , int m )
{
	printf( "Jobs scheduled at each timestep are :\n" ) ;
	int K = 0 ;
	int TIME = 0 ;
	while( TIME < jl[K].startTime )
	{
		printf( "-1 " ) ;
		TIME ++ ;
	}
	heap H ;
	initHeap( &H ) ;
	int taSum = 0 ;
	
	int totalT = 0 ;
	for ( int i=0 ; i<n ; i++ )
	{
		totalT += jl[i].jobLength ;
	}
	
	int* isFinished = ( int* ) calloc ( n+1 , sizeof(int) ) ;
	for ( int i=1 ; i<=n ; i++ )
		isFinished[i] = 0 ;
	
	while ( 1 )
	{
		if ( K < n && jl[K].startTime == TIME )
		{
			while ( jl[K].startTime == TIME )
			{
				insertJob( &H , jl[K++] ) ;
			}
		}
		if ( allFinished(isFinished, n) )	break ;
		if ( H.numJobs == 0 )
		{
			printf("-1 ") ;
			TIME ++ ;
			continue ;
		}
		int minR = H.list[1].remLength ;
		printf( "%d " , H.list[1].jobId ) ;
		if ( minR == H.list[1].jobLength )	
			taSum += (TIME-H.list[1].startTime) ;
		if ( minR == 1 )
		{
			job d ;
			extractMinJob( &H , &d ) ;
			isFinished[d.jobId] = 1 ;
			checkDependency( P , d.jobId , m , jl , n , &H , TIME+1 ) ;
		}
		else	H.list[1].remLength -- ;
		TIME ++ ;
	}
	printf("\nAverage Turnaround Time is %f\n", 1.0*(float)taSum/n ) ;
	
}

void stableCountingSort ( job* J , int n )
{
	int MAX_KEY = n ;
	int* COUNT = ( int* ) calloc ( MAX_KEY+1 , sizeof(int) ) ;
	for ( int i=0 ; i<=MAX_KEY ; i++ )
		COUNT[i] = 0 ;
	for ( int i=0 ; i<n ; i++ )
		COUNT[J[i].startTime] ++ ;
	for ( int i=MAX_KEY ; i>0 ; i-- )
		COUNT[i] = COUNT[i-1] ;
	COUNT[0] = 0 ;
	for ( int i=1 ; i<=MAX_KEY ; i++ )
		COUNT[i] += COUNT[i-1] ;
		
	job* sorted = ( job* ) calloc ( n , sizeof(job) ) ;
	
	for ( int i=0 ; i<n ; i++ )
		sorted[COUNT[J[i].startTime]++] = J[i] ;
		
	for ( int i=0 ; i<n ; i++ )
		J[i] = sorted[i] ;
}


int main ()
{
	int n , m ;
	printf( "Enter number of jobs n : " ) ;
	scanf ( "%d" , &n ) ;
	job* J = ( job* ) calloc ( n , sizeof(job) ) ;
	printf( "Enter the jobs\n" ) ;
	for ( int i=0 ; i<n ; i++ )
	{
		scanf( "%d %d %d" , &(J[i].jobId) , &(J[i].startTime) , &(J[i].jobLength) ) ;
		J[i].remLength = J[i].jobLength ;
	}
	printf( "Enter number of dependency pairs m : " ) ;
	scanf ( "%d" , &m ) ;
	
	jobpair* P = ( jobpair* ) calloc ( m , sizeof(jobpair) ) ;
	
	printf( "Enter the dependency pairs\n" ) ;
	for ( int i=0 ; i<m ; i++ )
	{
		scanf( "%d %d" , &(P[i].jobid_from) , &(P[i].jobid_to) ) ;
	}
	
	stableCountingSort( J , n ) ;
	scheduler( J , n , P , m ) ;
}
