
//	HASHING
//	NAKUL AGGARWAL	 | 19CS10044
//	12 NOVEMBER 2020 | THURSDAY
//	ASSIGNMENT 10

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int size ;
	int* K ;
	int n ;
} HTL2 ;	// SECOND LEVEL HASHTABLE

typedef struct {
	int key ;
	HTL2 T ;
} htnode ;

typedef struct {
	int size ;
	htnode* t ;
} HTL1 ;	// FIRST LEVEL HASHTABLE

HTL1 inittable ( int S )
{
	HTL1 tab ;
	tab.size = S ;
	tab.t = ( htnode* ) calloc ( S , sizeof(htnode) ) ;
	for ( int i=0 ; i<S ; i++ )
	{
		tab.t[i].key = -1 ;
		HTL2 W ;
		W.size = S ; W.n = 0 ;
		W.K = ( int* ) calloc ( S , sizeof(int) ) ;
		for ( int j=0 ; j<S ; j++ )
			W.K[j] = -1 ;
		tab.t[i].T = W ;
	}
	return tab ;
}

int h ( int k , int S )
{
	return k % S ;
}


void deletion ( HTL1* Ty , HTL1* Tp , int y )
{
	int S = Ty->size ;
	int idxY = h( y , S ) ;
	int* secLevelHash = Ty->t[idxY].T.K ;
	if ( Ty->t[idxY].key < 0 )	return ;
	for ( int k=0 ; k<S ; k++ )
	{
		if ( secLevelHash[k] < 0 )	continue ;
		int idxP = h( secLevelHash[k] , S ) ;
		Tp->t[idxP].T.K[idxY] = -1 ;
		( Tp->t[idxP].T.n ) -- ;
		if ( ! (Tp->t[idxP].T.n) )
			Tp->t[idxP].key = -1 ;
		secLevelHash[k] = -1 ;
		( Ty->t[idxY].T.n ) -- ;
	}
	Ty->t[idxY].key = -1 ;
}

void insert ( HTL1* Ty , HTL1* Tp , int y , int p )
{
	int S = Ty->size ;
	int idxY = h( y , S ) ;
	int idxP = h( p , S ) ;
	Ty->t[idxY].key = y ;
	Ty->t[idxY].T.K[idxP] = p ;
	( Ty->t[idxY].T.n ) ++ ;
	
	Tp->t[idxP].key = p ;
	Tp->t[idxP].T.K[idxY] = y ;
	( Tp->t[idxP].T.n ) ++ ;
}

void printHashMap ( HTL1* T , char flag , FILE* fptr )
{
	int S = T->size ;
	for ( int i=0 ; i<S ; i++ )
	{
		int key = T->t[i].key ;
		if ( key < 0 )
		{
			fprintf( fptr , "%c %2d %2d %2d\n" , flag , i , -1 , -1 ) ;
			continue ;
		}
		for ( int j=0 ; j<S ; j++ )
		{
			if ( T->t[i].T.K[j] >= 0 )
				fprintf( fptr , "%c %2d %2d %2d\n" , flag , i , key , T->t[i].T.K[j] ) ;
		}
	}
}

int main ()
{
	FILE* fptr = fopen ( "input.txt" , "r" ) ;
	FILE* fptr_out = fopen ( "output.txt" , "w" ) ;
	int s , c ;
	fscanf( fptr , "%d %d" , &s , &c ) ;
	HTL1 Ty = inittable(s) ;
	HTL1 Tp = inittable(s) ;
	int y , p ;
	for ( int I=0 ; I<c ; I++ )
	{
		char choice ;
		fscanf( fptr , " %c" , &choice ) ;
		if ( choice == '+' )
		{
			fscanf( fptr , "%d %d" , &y , &p ) ;
			insert( &Ty , &Tp , y , p ) ;
			continue ;
		}
		fscanf( fptr , "%d" , &y ) ;
		deletion( &Ty , &Tp , y ) ;
	}
	fclose( fptr ) ;
	printHashMap( &Tp , 'p' , fptr_out ) ;
	printHashMap( &Ty , 'c' , fptr_out ) ;
}
