
//	HASHING
//	NAKUL AGGARWAL	 | 19CS10044
//	12 NOVEMBER 2020 | THURSDAY
//	ASSIGNMENT 10

#include <stdio.h>
#include <stdlib.h>

typedef struct _hashing {
	int key;
	struct _hashing *next;
} hash ;

typedef struct {
	int size ;
	hash** A ;
} hashtable ;

hashtable inittable ( int S )
{
	hashtable T ;
	T.size = S ;
	T.A = ( hash** ) calloc ( S , sizeof(hash*) ) ;
	for ( int i=0 ; i<S ; i++ )
	{
		T.A[i] = ( hash* ) calloc ( S , sizeof(hash) ) ;
		T.A[i]->next = NULL ;
		T.A[i]->key = -1 ;
	}
	return T ;
}

int h ( int k , int S )
{
	return k % S ;
}

void searchAndDelete ( hash** A , int idx , int y )
{
	hash* p = A[idx] ;
	while ( p )
	{
		if ( p->next && p->next->key == y )
		{
			hash* t = p->next ;
			p->next = p->next->next ;
			free( t ) ;
			if ( ! (A[idx]->next) )	A[idx]->key = -1 ;
			return ;
		}
		p = p->next ;
	}
	if ( ! (A[idx]->next) )	A[idx]->key = -1 ;
}

void deletion ( hashtable* Ty , hashtable* Tp , int y )
{
	int S = Ty->size ;
	int idx = h( y , S ) ;
	hash* p = Ty->A[idx]->next ;
	while ( p )
	{
		int idxPort = h( p->key , S ) ;
		searchAndDelete( Tp->A , idxPort , y ) ;
		hash* t = p->next ;
		free( p ) ; p = t ;
	}
	Ty->A[idx]->next = NULL ;
	Ty->A[idx]->key = -1 ;
}

void insert ( hashtable* Ty , hashtable* Tp , int y , int p )
{
	int S = Ty->size ;
	int idxY = h( y , S ) ;
	int idxP = h( p , S ) ;
	Ty->A[idxY]->key = y ;
	Tp->A[idxP]->key = p ;
	hash* yn = Ty->A[idxY] ;
	hash* pn = Tp->A[idxP] ;
	
	hash* tempy = yn->next ;
	hash* tempp = pn->next ;
	
	yn->next = ( hash* ) malloc ( sizeof(hash) ) ;
	yn->next->next = tempy ;
	yn->next->key = p ;
	
	pn->next = ( hash* ) malloc ( sizeof(hash) ) ;
	pn->next->next = tempp ;
	pn->next->key = y ;
}

void printHashMap ( hashtable* T , char flag , FILE* fptr )
{
	int S = T->size ;
	for ( int i=0 ; i<S ; i++ )
	{
		hash* p = T->A[i]->next ;
		int key = T->A[i]->key ;
		if ( ! p )
		{
			fprintf( fptr , "%c %2d %2d %2d\n" , flag , i , -1 , -1 ) ;
			continue ;
		}
		while ( p )
		{
			fprintf( fptr , "%c %2d %2d %2d\n" , flag , i , key , p->key ) ;
			p = p->next ;
		}
	}
}

int main ()
{
	FILE* fptr = fopen ( "input.txt" , "r" ) ;
	FILE* fptr_out = fopen ( "output.txt" , "w" ) ;
	int s , c ;
	fscanf( fptr , "%d %d" , &s , &c ) ;
	hashtable Ty = inittable(s) ;
	hashtable Tp = inittable(s) ;
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
