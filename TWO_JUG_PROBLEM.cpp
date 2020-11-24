
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int m , n , f , v ;
} CONFIG ;

typedef struct {
	int S ;
	CONFIG* A ;
} HASH ;

int h ( int , int , int ) ;
HASH initTable ( int ) ;
int searchTable ( HASH , int , int ) ;
void insert ( HASH* , CONFIG ) ;
int findMoves ( HASH* , int , int , int , int , int , int ) ;

int main ()
{
	int m , n , d ;
	printf("\nCAPACITY OF GLASS O1 ( < 500 ) : ") ; scanf("%d", &m) ;
	printf("CAPACITY OF GLASS O2 ( < 500 ) : ") ; scanf("%d", &n) ;
	printf("VOLUME TO BE MEASURED : ") ; scanf("%d", &d) ;
	HASH T = initTable( 1009 ) ;
	int result = findMoves(&T,m,n,0,0,d,0) ;
	if ( result )
		printf("\nTHE GIVEN VOLUME CAN BE MEASURED BY TAKING THE FOLLOWING STEPS :-\n") ;
	else
		{	printf("\nTHE GIVEN VOLUME CANNOT BE MEASURED.\n") ; return 0 ;	}
	int i = 0 , j = 0 ;
	int step = 1 ;
	while ( result )
	{
		if ( i == 0 && j == d )	break ;
		if ( i == d && j == 0 )	break ;
		int move = T.A[searchTable(T,i,j)].v ;
		if ( move == 1 )
		{
			printf ("\nSTEP %3d : ( %3d , %3d ) - REFILL THE FIRST GLASS" , step++ , m , j ) ;
			i = m ;
			continue ;
		}
		if ( move == 2 )
		{
			printf ("\nSTEP %3d : ( %3d , %3d ) - REFILL THE SECOND GLASS" , step++ , i , n ) ;
			j = n ;
			continue ;
		}
		if ( move == 3 )
		{
			printf ("\nSTEP %3d : ( %3d , %3d ) - EMPTY THE SECOND GLASS" , step++ , i , 0 ) ;
			j = 0 ;
			continue ;
		}
		if ( move == 4 )
		{
			printf ("\nSTEP %3d : ( %3d , %3d ) - EMPTY THE FIRST GLASS" , step++ , 0 , j ) ;
			i = 0 ;
			continue ;
		}
		if ( move == 5 )
		{
			int it = i , jt = j ;
			while ( jt > 0 && it < m )
			{
				jt-- ; it++ ;
			}
			printf ("\nSTEP %3d : ( %3d , %3d ) - TRANSFER FROM SECOND TO FIRST GLASS" , step++ , it , jt ) ;
			i = it ; j = jt ;
			continue ;
		}
		if ( move == 6 )
		{
			int it = i , jt = j ;
			while ( jt < n && it > 0 )
			{
				jt++ ; it-- ;
			}
			printf ("\nSTEP %3d : ( %3d , %3d ) - TRANSFER FROM FIRST TO SECOND GLASS" , step++ , it , jt ) ;
			i = it ; j = jt ;
			continue ;
		}
	}
	printf("\n\n") ; return 0 ;
}

int h ( int m , int n , int S )
{
	int x = (100003*m) % S ;
	x += (103*n) % S ;
	return (x % S) ;
}

int searchTable ( HASH T , int i , int j )
{
	int S = T.S ;
	int I = h( i , j , S ) ;
	for ( int k=0 ; k<S ; k++ )
	{
		if ( T.A[I].m == -1 )	return -1 ;
		if ( T.A[I].m == i && T.A[I].n == j )
		{
			return I ;
		}
		I = ( I + 1 ) % ( S ) ;
	}
	return -1 ;
}

HASH initTable ( int S )
{
	HASH T ;
	T.S = S ;
	T.A = ( CONFIG* ) calloc ( S , sizeof(CONFIG) ) ;
	for ( int i=0 ; i<S ; i++ )
	{
		T.A[i].m = -1 ;
		T.A[i].n = -1 ;
		T.A[i].v = -1 ;
		T.A[i].f = -1 ;
	}
	return T ;
}

void insert ( HASH* T , CONFIG c )
{
	int I = h( c.m , c.n , T->S ) ;
	while ( ! ( T->A[I].m < 0 ) )
		I = ( I + 1 ) % ( T->S ) ;
	T->A[I] = c ;
	return ;
}

int findMoves ( HASH* T , int m , int n , int i , int j , int k , int last_move )
{
	if ( i == 0 && j == k )	return 1 ;
	if ( j == 0 && i == k )	return 1 ;
	int idx = searchTable( *T , i , j ) ;
	if ( idx >= 0 )
		return T->A[idx].f ;
	
	CONFIG c = { i , j , 0 , 0 } ;
	insert( T , c ) ;
	idx = searchTable( *T , i , j ) ;
	int move ;
	
	if ( i > 0 && last_move != 1 )
	{
		move = findMoves ( T , m , n , 0 , j , k , 4 ) ;
		if ( move )
		{
			T->A[idx].f = 1 ;
			T->A[idx].v = 4 ;
			return 1 ;
		}
	}
	if ( j > 0 && last_move != 2 )
	{
		move = findMoves ( T , m , n , i , 0 , k , 3 ) ;
		if ( move )
		{
			T->A[idx].f = 1 ;
			T->A[idx].v = 3 ;
			return 1 ;
		}
	}
	if ( i < m && last_move != 4 )
	{
		move = findMoves ( T , m , n , m , j , k , 1 ) ;
		if ( move )
		{
			T->A[idx].f = 1 ;
			T->A[idx].v = 1 ;
			return 1 ;
		}
	}
	if ( j < n && last_move != 3 )
	{
		move = findMoves ( T , m , n , i , n , k , 2 ) ;
		if ( move )
		{
			T->A[idx].f = 1 ;
			T->A[idx].v = 2 ;
			return 1 ;
		}
	}
	if ( i < m && j > 0 && last_move != 6 )
	{
		int it = i , jt = j ;
		while ( jt > 0 && it < m )
		{
			jt-- ; it++ ;
		}
		move = findMoves ( T , m , n , it , jt , k , 5 ) ;
		if ( move )
		{
			T->A[idx].f = 1 ;
			T->A[idx].v = 5 ;
			return 1 ;
		}
	}
	if ( j < n && i > 0 && last_move != 5 )
	{
		int it = i , jt = j ;
		while ( jt < n && it > 0 )
		{
			jt++ ; it-- ;
		}
		move = findMoves ( T , m , n , it , jt , k , 6 ) ;
		if ( move )
		{
			T->A[idx].f = 1 ;
			T->A[idx].v = 6 ;
			return 1 ;
		}
	}
	return 0 ;
}
