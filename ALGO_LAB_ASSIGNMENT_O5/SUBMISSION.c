
//	GREEDY ALGORITHMS
//	NAKUL AGGARWAL	|	19CS10044
//	15 OCTOBER 2020	|	THURSDAY
//	ASSIGNMENT O6	|	WEEK O7

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int s , e , id ;
} interval ;

void swap ( interval* , interval* ) ;
float max ( float , float ) ;
int checkWindow ( interval* , int , float , float , int ) ;
float checkOrdering ( interval* , int , float ) ;
int findMaxWindow ( interval* , int ) ;
void updateOptimalOrdering ( interval* , interval* , int ) ;
void schedule_visits ( interval* , int , int , float* , float , interval* ) ;
float roundFloat ( float ) ;

int main()
{
	int n ;
	interval T[8] ;
	interval OPT[8] ;
	FILE* input = fopen ( "input1.txt" , "r" ) ;
	fscanf ( input , "%d" , &n ) ;
	for ( int i=0 ; i<n ; i++ )
	{
		fscanf ( input , "%d %d" , &(T[i].s) , &(T[i].e) ) ;
		T[i].id = i ;
	}
	fclose ( input ) ;
	
	float maxGap = (float) findMaxWindow( T , n ) ;
	float optimalGap = 0.0 ;
	schedule_visits ( T , n , 0 , &optimalGap , maxGap , OPT ) ;
	optimalGap = roundFloat( optimalGap ) ;
	
	FILE* output = fopen ( "output1.txt" , "w" ) ;
	int min = ( int ) optimalGap ;
	int sec = ( int ) ( (optimalGap - min*1.0)*60.0 ) ;
	
	fprintf( output , "%02d:%02d\n" , min , sec ) ;
	for ( int i=0 ; i<n ; i++ )
		fprintf( output , "%d ", OPT[i].id ) ;
	fclose ( output ) ;
	return 0 ;
}

void swap ( interval* p , interval* q )
{
	interval temp = *p ;
	*p = *q ;
	*q = temp ;
	return ;
}

float max ( float a , float b )
{
	if ( a > b ) return a ;
	return b ;
}

int checkWindow ( interval* A , int i , float t , float w , int n )
{
	if ( i == n ) return 1 ;
	float time = max ( A[i].s , t ) ;
	if ( (float)A[i].e < time ) return 0 ;
	return checkWindow ( A , i+1 , time+w , w , n ) ;
}

float checkOrdering ( interval* A , int n , float maxGap )
{
	float g = maxGap ;
	int isPossible = checkWindow ( A , 0 , A[0].s , g , n ) ;
	while ( ! isPossible )
	{
		g -= 0.0001 ;
		if ( g < 0.0 ) return 0.0 ;
		isPossible = checkWindow ( A , 0 , A[0].s , g , n ) ;
	}
	return g ;
}

int findMaxWindow ( interval* T , int n )
{
	int low = T[0].s ;
	int high = T[0].e ;
	for ( int i=1 ; i<n ; i++ )
	{
		if ( low > T[i].s ) low = T[i].s ;
		if ( high < T[i].e ) high = T[i].e ;
	}
	return high-low ;
}

void updateOptimalOrdering ( interval* A , interval* T , int n )
{
	for ( int i=0 ; i<n ; i++ )
		A[i] = T[i] ;
	return ;
}

void schedule_visits ( interval* T , int n , int i , float* optimalGap , float maxGap , interval* A )
{
	if ( i == n )
	{
		float v = checkOrdering( T , n , maxGap ) ;
		if ( v > *optimalGap )
		{
			*optimalGap = v ;
			updateOptimalOrdering( A , T , n ) ;
		}
		return ;
	}
	schedule_visits( T , n , i+1 , optimalGap , maxGap , A ) ;
	for ( int j=i+1 ; j<n ; j++ )
	{
		swap( T+i , T+j ) ;
		schedule_visits( T , n , i+1 , optimalGap , maxGap , A ) ;
		swap( T+i , T+j ) ;
	}
	return ;
}

float roundFloat ( float f )
{
	float f_ = f*1000 ;
	f_ += 0.5 ;
	int i = (int)f_ ;
	return i/1000.0 ;
}
