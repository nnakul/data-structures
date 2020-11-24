
#include <stdio.h>
#include <stdlib.h>
#define		INF 	10000

typedef struct {
	int capacity ;
	int num_of_keys ;
	int current_node ;
	int** H ;
	int* size ;
} MultiHeap ;

void swap ( int* , int* ) ;
void quickSort ( int* , int , int ) ;
MultiHeap initHeap ( int , int ) ;
void insertMultiHeap ( MultiHeap* , int ) ;
int maxKey ( int* , int ) ;
void heapify ( MultiHeap* , int ) ;
int deleteMultiHeap ( MultiHeap* ) ;
void printMultiHeap ( MultiHeap ) ;

int main ()
{
	int capPerNode , totalCap ;
	printf( "\n\nCAPACITY PER NODE : " ) ;
	scanf( "%d" , &capPerNode ) ;
	printf( "TOTAL DESIRED CAPACITY OF THE MULTIHEAP : " ) ;
	scanf( "%d" , &totalCap ) ;	printf("\n") ;
	MultiHeap H = initHeap( capPerNode , totalCap ) ;
	int choice = 0 , element = -1 ;
	while(true)
	{
		printf("+++ Enter choice: ") ;
		scanf( "%d" , &choice ) ;
		if ( ! choice )	break ;
		if (choice==1)
		{
			scanf( "%d" , &element ) ;
			insertMultiHeap( &H , element ) ;
			printf( "\tINSERTED %d\n" , element ) ;
		}
		if (choice==2)
		{
			element = deleteMultiHeap( &H ) ;
			printf( "\tDELETED %d\n" , element ) ;
		}
		if (choice==3) 	printMultiHeap( H ) ;
	}
	printf("\n\n\n") ;
}

MultiHeap initHeap ( int p , int n )
{
	MultiHeap heap ;
	heap.capacity = p ;
	heap.num_of_keys = 0 ;
	heap.current_node = 0 ;
	int s = (n+p-1)/p ;
	heap.H = ( int** ) calloc ( s , sizeof(int*) ) ;
	heap.size = ( int* ) calloc ( s , sizeof(int) ) ;
	for ( int i=0 ; i<s ; i++ )
	{
		heap.H[i] = ( int* ) calloc ( p , sizeof(int) ) ;
		heap.size[i] = -1 ;
	}
	return heap ;
}

void insertMultiHeap ( MultiHeap* H , int key )
{
	H->num_of_keys ++ ;
	if ( H->size[H->current_node] == H->capacity-1 )
		H->current_node++ ;
	H->size[H->current_node] ++ ;
	H->H[H->current_node][H->size[H->current_node]] = key ;
	
	int node = H->current_node ;
	int parent = (node+1)/2 - 1 ;
	while( node > 0 )
	{
		int m=INF , M=-1 ;
		for ( int i=0 ; i<=H->size[parent] ; i++ )
			if ( m > H->H[parent][i] ) m = H->H[parent][i] ;
		for ( int i=0 ; i<=H->size[node] ; i++ )
			if ( M < H->H[node][i] ) M = H->H[node][i] ;
		if ( m > M ) break ;
		int newSize = H->size[parent]+H->size[node]+2 ;
		int* T = ( int* ) calloc ( newSize , sizeof(int) ) ;
		int k = 0 ;
		for ( int i=0 ; i<=H->size[node] ; i++ )
			T[k++] = H->H[node][i] ;
		for ( int i=0 ; i<=H->size[parent] ; i++ )
			T[k++] = H->H[parent][i] ;
		quickSort( T , 0 , newSize-1 ) ;
		k = 0 ;
		for ( int i=0 ; i<=H->size[node] ; i++ )
			H->H[node][i] = T[k++] ;
		for ( int i=0 ; i<=H->size[parent] ; i++ )
			H->H[parent][i] = T[k++] ;
		free( T ) ;
		node = parent ;
		parent = (node+1)/2 - 1 ;
	}
}

int maxKey ( int* A , int end )
{
	int max = -1 ;
	for ( int i=0 ; i<=end ; i++ )
		if ( max < A[i] )	max = A[i] ;
	return max ;
}

void heapify ( MultiHeap* H , int I )
{
	while (true)
	{
      int childL = 2*I + 1 ; 
	  int childR = 2*I + 2 ;
      if ( childL > H->current_node ) return ;
      
      int maxL , maxR ;
      int max ;
	  maxL = maxKey(H->H[childL],H->size[childL]) ;
	  if ( childR <= H->current_node ) maxR = maxKey(H->H[childR],H->size[childR]) ;
	  else	maxR = -1 ;
	  
	  max = ( maxL > maxR ) ? maxL : maxR ;
      int maxRoot = maxKey(H->H[I],H->size[I]) ;
      if ( max <= maxRoot ) return ;
      
	  if ( maxR < 0 )
      {
      	int newSize = H->size[childL] + H->size[I] + 2 ;
      	int* T = ( int* ) calloc ( newSize , sizeof(int) ) ;
		int k = 0 ;
		for ( int i=0 ; i<=H->size[I] ; i++ )
			T[k++] = H->H[I][i] ;
		for ( int i=0 ; i<=H->size[childL] ; i++ )
			T[k++] = H->H[childL][i] ;
		quickSort( T , 0 , newSize-1 ) ;
		k = 0 ;
		for ( int i=0 ; i<=H->size[childL] ; i++ )
			H->H[childL][i] = T[k++] ;
		for ( int i=0 ; i<=H->size[I] ; i++ )
			H->H[I][i] = T[k++] ;
		free( T ) ;
		I = childL ;
		continue ;
	  }
	  
	  int newSize = H->size[childL] + H->size[I] + H->size[childR] + 3 ;
	  int* T = ( int* ) calloc ( newSize , sizeof(int) ) ;
	  int k = 0 ;
	  for ( int i=0 ; i<=H->size[I] ; i++ )
		T[k++] = H->H[I][i] ;
	  for ( int i=0 ; i<=H->size[childL] ; i++ )
		T[k++] = H->H[childL][i] ;
	  for ( int i=0 ; i<=H->size[childR] ; i++ )
		T[k++] = H->H[childR][i] ;
	
	  quickSort( T , 0 , newSize-1 ) ;
	
	  k = 0 ;
	  for ( int i=0 ; i<=H->size[childL] ; i++ )
		  H->H[childL][i] = T[k++] ;
	  for ( int i=0 ; i<=H->size[childR] ; i++ )
		  H->H[childR][i] = T[k++] ;
	  for ( int i=0 ; i<=H->size[I] ; i++ )
		  H->H[I][i] = T[k++] ;
	
	  free( T ) ;
	  heapify( H , childL ) ;
	  heapify( H , childR ) ;
	  return ;
	}
}

int deleteMultiHeap ( MultiHeap* H )
{
	int max = -1 , Mi ;
	int rootSize = H->size[0] ;
	for ( int i=0 ; i<=rootSize ; i++ )
		if ( max < H->H[0][i] )
		{
			max = H->H[0][i] ;
			Mi = i ;
		}
	swap( &(H->H[0][Mi]) , &(H->H[H->current_node][H->size[H->current_node]]) ) ;
	H->size[H->current_node] -- ;
	if ( H->size[H->current_node] == -1 )	H->current_node -- ;
	heapify( H , 0 ) ;
	return max ;
}

void printMultiHeap ( MultiHeap H )
{
	if ( H.size[0] == -1 )
	{
		printf( "\tHEAP IS EMPTY\n" ) ;
		return ;
	}
	for ( int i=0 ; i<=H.current_node ; i++ )
	{
		if ( i > 0 )	printf("\n") ;
		printf("\tNODE %2d : ", i ) ;
		for ( int j=0 ; j<=H.size[i] ; j++ )
			printf("%3d ", H.H[i][j] ) ;
	}
	printf("\n") ;
}

void quickSort ( int* arr , int si , int ei )
{
	if ( si >= ei ) return ;
	int pivot = arr[si] ;
	int i = si ;
	int j = si + 1 ;
	while ( j<=ei )
	{
		if ( arr[j] < pivot )
		{
			i++ ;
			swap( arr+i , arr+j ) ;
		}
		j++ ;
	}
	swap( arr+si , arr+i ) ;
	quickSort( arr , si , i-1 ) ;
	quickSort( arr , i+1 , ei ) ;
}

void swap ( int* x , int* y )
{
	int t = *x ;
	*x = *y ;
	*y = t ;
}
