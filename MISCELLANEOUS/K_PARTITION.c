
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int* Q ;
	int FLAG , MOVE , EXP , I ;
} CONFIG ;

typedef struct {
	int S ;
	CONFIG* A ;
} HASHTABLE ;

int isPossible ( HASHTABLE* , int* , int* , int , int , int ) ;
void insert ( HASHTABLE* , int* , int , int , int , int ) ;
int equalArrays ( int* , int* , int ) ;
int search ( HASHTABLE , int* , int , int ) ;
int h ( int* , int , int , int ) ;
HASHTABLE initTable ( int ) ;

int main ()
{
	int N , SUM = 0 , K ;
	printf( "\nENTER THE NUMBER OF ELEMENTS IN SET : " ) ; scanf( "%d" , &N ) ;
	int* SET = ( int* ) calloc ( N , sizeof(int) ) ;
	printf( "ENTER %d POSITIVE ELEMENTS : " , N ) ;
	for ( int i=0 ; i<N ; i++ )
		{ scanf( "%d" , SET+i ) ; SUM += SET[i] ; }
	printf( "ENTER NUMBER OF SUBSETS IN THE PARTITION : " ) ; scanf( "%d" , &K ) ;
	if ( SUM % K )	{
		printf( "\n\t+++ PARTTIONING INTO %d SUBSETS WITH EQUAL SUM IS NOT POSSIBLE +++\n\n" , K ) ;
		return 0 ;
	}
	int* SUBSETS = ( int* ) calloc ( K , sizeof(int) ) ;
	for ( int i=0 ; i<K ; i++ )	SUBSETS[i] = SUM/K ;
	HASHTABLE T = initTable(1003) ;
	int result = isPossible(&T , SET , SUBSETS , K , N , 0 ) ;
	if ( result == -1 )	{
		printf( "\n\t+++ PARTTIONING INTO %d SUBSETS WITH EQUAL SUM IS NOT POSSIBLE +++\n\n" , K ) ;
		return 0 ;
	}
	printf( "\n\t+++ THE SET CAN BE PARTITIONED INTO %d SUBSETS WITH EQUAL SUM +++\n\n" , K ) ;
	int** SUB = ( int** ) calloc ( K , sizeof(int*) ) ;
	for ( int i=0 ; i<K ; i++ )
		SUB[i] = ( int* ) calloc ( N-K+1 , sizeof(int) ) ;
	int* I = ( int* ) calloc ( K , sizeof(int) ) ;
	for ( int i=0 ; i<K ; i++ )	I[i] = 0 ;
	for ( int i=0 ; i<N ; i++ )
	{
		int move = search( T , SUBSETS , K , i ) ;
		SUBSETS[move] -= SET[i] ;
		SUB[move][I[move]++] = SET[i] ;
	}
	for ( int i=0 ; i<K ; i++ )
	{
		printf("\n ") ;
		for ( int j=0 ; j<I[i] ; j++ )
			printf("%2d  ", SUB[i][j]) ;
	}
}

int isPossible ( HASHTABLE* T , int* SET , int* SUB , int K , int N , int i )
{
	if ( i == N )
	{
		for( int j=0 ; j<K ; j++ )
			if ( SUB[j] )	return -1 ;
		return N ;
	}
	int result = search( *T , SUB , K , i ) ;
	if ( result != -1 )	return result ;
	CONFIG t ; t.MOVE = -1 ;
	for ( int j=0 ; j<K ; j++ )
	{
		if ( SUB[j] >= SET[i] )
		{
			SUB[j] -= SET[i] ;
			int result = isPossible( T , SET , SUB , K , N , i+1 ) ;
			SUB[j] += SET[i] ;
			if( result != -1 )	{ t.MOVE = j ; break ; }
		}
	}
	if ( t.MOVE == -1 )		{ insert( T , SUB , K , 0 , -1 , i ) ; return -1 ; }
	else	{ insert( T , SUB , K , 1 , t.MOVE , i ) ; return t.MOVE ; }
}

void insert ( HASHTABLE* T , int* A , int n , int f , int move , int i )
{
	int S = T->S , k ;
	int idx = h( A , n , i , S ) ;
	for ( k=0 ; k<S ; k++ )
	{
		if ( ! T->A[idx].EXP )	break ;
		idx = ( idx + 1 ) % S ;
	}
	if ( k == S )	exit(0) ;
	CONFIG t ;
	t.EXP = 1 ; t.FLAG = f ; t.MOVE = move ; t.I = i ;
	t.Q = ( int* ) calloc ( n , sizeof(int) ) ;
	for ( int i=0 ; i<n ; i++ )   t.Q[i] = A[i] ;
	T->A[idx] = t ;
}

int equalArrays ( int* A , int* B , int n )
{
	for ( int i=0 ; i<n ; i++ )
		if ( A[i] != B[i] )	return 0 ;
	return 1 ;
}

int search ( HASHTABLE T , int* A , int n , int i )
{
	int S = T.S , k ;
	int idx = h( A , n , i , S ) ;
	for ( k=0 ; k<S ; k++ )
	{
		if ( ! T.A[idx].EXP )	return -1 ;
		if ( T.A[idx].I == i && equalArrays( A , T.A[idx].Q , n ) )	return T.A[idx].MOVE ;
		idx = ( idx + 1 ) % S ;
	}
	return -1 ;
}

int h ( int* A , int n , int j , int S )
{
	int H = 0 , a = 37 ;
	for ( int i=0 ; i<n ; i++ )
		H = ( a*H + A[i] ) % S ;
	return (H+j*31)%S ;
}

HASHTABLE initTable ( int S )
{
	HASHTABLE T ;
	T.S = S ;
	T.A = ( CONFIG* ) calloc ( S , sizeof(CONFIG) ) ;
	for ( int i=0 ; i<S ; i++ )
		T.A[i].EXP = 0 ;
	return T ;
}
