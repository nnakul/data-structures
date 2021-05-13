
//	DISJOINT SETS DATA STRUCTURE
//	NAKUL AGGARWAL	|	19CS10044
//	ASSIGNMENT O7	|	WEEK O8
//	22 OCTOBER 2020	|	THURSDAY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	struct node *parent ;
	int rank ;
} node ;

node* makeSet ( int ) ;
node* findSet ( node* ) ;
void mergeSets ( node* , node* ) ;
void findTreasure ( node*** , int** , int** , int , int ) ;
void printGrid ( int** , int** , int , int ) ;

int main ( int argc , char** argv )
{
	int m = 10 , n = 10 ;
	if ( argc > 1 )	m = atoi( argv[1] ) ;
	if ( argc > 2 )	n = atoi( argv[2] ) ;
	printf( "\n\n%d %d\n" , m , n ) ;
	
	node*** C = ( node*** ) calloc ( m , sizeof(node**) ) ;
	
	for ( int i=0 ; i<m ; i++ )
		C[i] = ( node** ) calloc ( n , sizeof(node*) ) ;
	
	for ( int i=0 ; i<m ; i++ )
		for ( int j=0 ; j<n ; j++ )
			C[i][j] = makeSet(0) ;
	
	int** H = ( int** ) calloc ( m-1 , sizeof(int*) ) ;
	for ( int i=0 ; i<m-1 ; i++ )
		H[i] = ( int* ) calloc ( n , sizeof(int) ) ;
		
	int** V = ( int** ) calloc ( m , sizeof(int*) ) ;
	for ( int i=0 ; i<m ; i++ )
		V[i] = ( int* ) calloc ( n-1 , sizeof(int) ) ;
		
	int** H_COPY = ( int** ) calloc ( m-1 , sizeof(int*) ) ;
	for ( int i=0 ; i<m-1 ; i++ )
		H_COPY[i] = ( int* ) calloc ( n , sizeof(int) ) ;
		
	int** V_COPY = ( int** ) calloc ( m , sizeof(int*) ) ;
	for ( int i=0 ; i<m ; i++ )
		V_COPY[i] = ( int* ) calloc ( n-1 , sizeof(int) ) ;
		
	for ( int i=0 ; i<m-1 ; i++ )
		for ( int j=0 ; j<n ; j++ )
			H[i][j] = H_COPY[i][j] = 1 ;
	for ( int i=0 ; i<m ; i++ )
		for ( int j=0 ; j<n-1 ; j++ )
			V[i][j] = V_COPY[i][j] = 1 ;

	findTreasure( C , H , V , m , n ) ;
	printf( "\n\t+++ INITIAL GRID +++\n\n" ) ;
	printGrid( V_COPY , H_COPY , m , n ) ;
	free( V_COPY ) ; free( H_COPY ) ; 
	printf( "\n\t+++ FINAL GRID +++\n\n" ) ;
	printGrid( V , H , m , n ) ;
	printf( "\n\n" ) ;
}

node* makeSet ( int rank )
{
	node* n = ( node* ) malloc ( sizeof(node) ) ;
	n->parent = n ;
	n->rank = rank ;
	return n ;
}

node* findSet ( node* n )
{
	node* p = n->parent ;
	node* c = n ;
	while ( c != p )
	{
		c = p ;
		p = p->parent ;
	}
	node* root = c ;
	c = n ;
	while ( c->parent != root )
	{
		node* t = c->parent ;
		c->parent = root ;
		c = t ;
	}
	return root ;
}

void mergeSets ( node* p , node* q )
{
	if ( p->rank < q->rank )
	{
		p->parent = q ;
		return ;
	}
	if ( p->rank > q->rank )
	{
		q->parent = p ;
		return ;
	}
	q->parent = p ;
	p->rank += 1 ;
	return ;
}

void findTreasure ( node*** C , int** H , int** V , int m , int n )
{
	srand( time(NULL) ) ;
	int count = m*n - 1 ;
	while ( count > 0 )
	{
		int decision = rand()%2 ;
		if ( m == 1 )	decision = 0 ;
		if ( n == 1 )	decision = 1 ;
		if ( decision )
		{
			int I = rand() % (m-1) ;
			int J = rand() % n ;
			if ( ! H[I][J] )	continue ;
			node* root1 = findSet( C[I][J] ) ;
			node* root2 = findSet( C[I+1][J] ) ;
			if ( root1 != root2 )
			{
				H[I][J] = 0 ;
				count -- ;
				mergeSets( root1 , root2 ) ;
			}
		}
		else
		{
			int I = rand() % m ;
			int J = rand() % (n-1) ;
			if ( ! V[I][J] )	continue ;
			node* root1 = findSet( C[I][J] ) ;
			node* root2 = findSet( C[I][J+1] ) ;
			if ( root1 != root2 )
			{
				V[I][J] = 0 ;
				count -- ;
				mergeSets( root1 , root2 ) ;
			}
		}
	}
	if ( findSet(C[0][0]) == findSet(C[m-1][n-1]) )
		printf ( "\nThe final chamber can be reached from the start chamber.\n" ) ;
}

void printGrid ( int** V , int** H , int m , int n )
{
	printf( "+   " ) ;
	for ( int i=1 ; i<n ; i++ )
		printf( "+---" ) ;
	printf( "+\n" ) ;
	for ( int i=0 ; i<m-1 ; i++ )
	{
		printf( "|   " ) ;
		for ( int j=0 ; j<n-1 ; j++ )
			if ( V[i][j] )	printf( "|   " ) ;
			else	printf( "    " ) ;
		printf( "|\n" ) ;
		for ( int j=0 ; j<n ; j++ )
			if ( H[i][j] )	printf( "+---" ) ;
			else	printf( "+   " ) ;
		printf( "+\n" ) ;
	}
	printf( "|   " ) ;
	for ( int j=0 ; j<n-1 ; j++ )
		if ( V[m-1][j] )	printf( "|   " ) ;
		else	printf( "    " ) ;
	printf( " \n" ) ;
	for ( int i=0 ; i<n ; i++ )
		printf( "+---" ) ;
	printf( "+\n" ) ;
}
