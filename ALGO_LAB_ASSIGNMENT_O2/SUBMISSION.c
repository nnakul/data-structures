
// 	GRAPHS
//	WEEK O4		|	ASSIGNMENT O3
//	24 SEPTEMBER 2020	|	THURSDAY
//	NAKUL AGGARWAL		|	19CS10044

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x ;
	int y ;
} POINT ;

typedef struct stack {
	POINT head ;
	struct stack* next ;
} STACK ;

typedef struct {
	int front ;
	int rear ;
	int queueSize ;
	POINT* arr ;
} QUEUE ;

void initStack ( STACK* ) ;
void push ( STACK* , POINT ) ;
void initQueue ( QUEUE* , int ) ;
void enqueue ( QUEUE* , POINT ) ;
POINT pop ( STACK* ) ;
POINT peek ( STACK ) ;
POINT dequeue ( QUEUE* ) ;
POINT onFront ( QUEUE ) ;
int isStackEmpty ( STACK ) ;
int isQueueEmpty ( QUEUE ) ;
void printGrid ( int a , int b , int grid[][200] ) ;
int strategy1 ( int[][200] , int , int , POINT , POINT ) ;
void strategy2 ( int[][200] , int , int , POINT , POINT ) ;

int main ()
{
	int grid[200][200] ;
	POINT unstable[200] ;
	int a , b , n ;
	POINT J , F ;
	
	scanf ( "%d %d %d" , &a , &b , &n ) ;
	for ( int i=0 ; i<n ; i++ )
		scanf ( "%d" , &unstable[i].x ) ;
	for ( int i=0 ; i<n ; i++ )
		scanf ( "%d" , &unstable[i].y ) ;
	
	scanf ( "%d %d %d %d" , &J.x , &J.y , &F.x , &F.y ) ;
	
	for ( int i=0 ; i<a ; i++ )
		for ( int j=0 ; j<b ; j++ )
			grid[i][j] = 1 ;
	
	for ( int i=0 ; i<n ; i++ )
		grid[unstable[i].x][unstable[i].y] = 0 ;
		
	printGrid ( a , b , grid ) ;
	int result = strategy1 ( grid , a , b , J , F ) ;
	if ( result )	strategy2 ( grid , a , b , J , F ) ;
	return 0 ;
}

void strategy2 ( int grid[][200] , int a , int b , POINT J , POINT F )
{
	char** color = ( char** ) calloc ( a , sizeof(char*) ) ;
	for ( int i=0 ; i<a ; i++ )
		color[i] = ( char* ) calloc ( b , sizeof(char) ) ;
	for ( int i=0 ; i<a ; i++ )
		for ( int j=0 ; j<b ; j++ )
			color[i][j] = 'w' ;
			
	STACK S ;
	initStack( &S ) ;
	color[J.x][J.y] = 'g' ;
	push( &S , J ) ;
	
	while ( ! isStackEmpty(S) )
	{
		POINT P = peek(S) ;
		POINT temp[] = {  { P.x+1 , P.y } ,
						  { P.x , P.y-1 } ,
						  { P.x , P.y+1 } ,
						  { P.x-1 , P.y } } ;
		int i ;
		for ( i=0 ; i<4 ; i++ )
		{
			if ( temp[i].x >= a || temp[i].x < 0 || temp[i].y >= b || temp[i].y < 0 )	continue ;
			if ( grid[temp[i].x][temp[i].y] == 1 )
			{
				if ( color[temp[i].x][temp[i].y] == 'w' )
				{
					if ( temp[i].x == F.x && temp[i].y == F.y )
					{
						POINT* path = ( POINT* ) calloc ( a*b , sizeof(POINT) ) ;
						int k = 0 ;
						POINT now = F ;
						while ( 1 )
						{
							path[k++] = now ;
							if ( now.x == J.x && now.y == J.y ) break ;
							if ( ! isStackEmpty(S) )	now = pop(&S) ;
						}
						for ( int x=k-1 ; x>=0 ; x-- )
							printf ( " ( %d , %d ) " , path[x].x , path[x].y ) ;
						free( path ) ;
						free( color ) ;
						printf ( "\n\n" ) ;
						return ;
					}
					push( &S , temp[i] ) ;
					color[temp[i].x][temp[i].y] = 'g' ;
					break ;
				}
			}
		}
		if ( i == 4 )	pop( &S ) ;
	}
	return ;
}

int strategy1 ( int grid[][200] , int a , int b , POINT J , POINT F )
{
	char** color = ( char** ) calloc ( a , sizeof(char*) ) ;
	for ( int i=0 ; i<a ; i++ )
		color[i] = ( char* ) calloc ( b , sizeof(char) ) ;
	for ( int i=0 ; i<a ; i++ )
		for ( int j=0 ; j<b ; j++ )
			color[i][j] = 'w' ;
			
	QUEUE Q ;
	initQueue( &Q , a*b ) ;
	color[J.x][J.y] = 'g' ;
	enqueue( &Q , J ) ;
	
	while ( ! isQueueEmpty(Q) )
	{
		POINT P = onFront(Q) ;
		POINT temp[] = {  { P.x+1 , P.y } ,
						  { P.x , P.y-1 } ,
						  { P.x , P.y+1 } ,
						  { P.x-1 , P.y } } ;
						  
		for ( int i=0 ; i<4 ; i++ )
		{
			if ( temp[i].x >= a || temp[i].x < 0 || temp[i].y >= b || temp[i].y < 0 )	continue ;
			if ( grid[temp[i].x][temp[i].y] == 1 )
			{
				if ( color[temp[i].x][temp[i].y] == 'w' )
				{
					if ( temp[i].x == F.x && temp[i].y == F.y )
					{
						free ( color ) ;
						printf ( "\n\nPath Exists\n" ) ;
						return 1 ;
					}
					enqueue( &Q , temp[i] ) ;
					color[temp[i].x][temp[i].y] = 'g' ;
				}
			}
		}
		dequeue( &Q ) ;
	}
	free ( color ) ;
	printf ( "\n\nPath Does Not Exist\n" ) ;
	return 0 ;
}

void printGrid ( int a , int b , int grid[][200] )
{
	printf ( "\nGrid of Stones is : " ) ;
	for ( int i=0 ; i<a ; i++ )
	{
		printf ( "\n" ) ;
		for ( int j=0 ; j<b ; j++ )
		{
			if ( grid[i][j] == 0 )
				printf ( " - " ) ;
			else printf ( " * " ) ;
		}
	}
	return ;
}

void initStack ( STACK* S )
{
	S->head.x = S->head.y = -1 ;
	S->next = NULL ;
	return ;
}

POINT pop ( STACK* S )
{
	if ( S->next == NULL )	exit(1) ;
	POINT p = S->next->head ;
	STACK* t = S->next ;
	S->next = S->next->next ;
	free(t) ;
	return p ;
}

void push ( STACK* S , POINT p )
{
	STACK* s = ( STACK* ) malloc ( sizeof(STACK) ) ;
	s->head = p ;
	s->next = S->next ;
	S->next = s ;
	return ;
}

int isStackEmpty ( STACK S )
{
	if ( S.next == NULL )	return 1 ;
	return 0 ;
}

POINT peek ( STACK S )
{
	if ( S.next == NULL )	exit(2) ;
	return S.next->head ;
}

void initQueue ( QUEUE* Q , int size )
{
	Q->front = 0 ;
	Q->rear = -1 ;
	Q->queueSize = size ;
	Q->arr = ( POINT* ) calloc ( size , sizeof(POINT) ) ;
	return ;
}

void enqueue ( QUEUE* Q , POINT p )
{
	if ( Q->rear == Q->queueSize-1 )	exit(3) ;
	Q->arr[++Q->rear] = p ;
}

POINT dequeue ( QUEUE* Q )
{
	if ( Q->front > Q->rear ) exit(4) ;
	POINT p = Q->arr[Q->front++] ;
	return p ;
}

int isQueueEmpty ( QUEUE Q )
{
	if ( Q.front > Q.rear )	return 1 ;
	return 0 ;
}

POINT onFront ( QUEUE Q )
{
	if ( Q.front > Q.rear )	exit(5) ;
	return Q.arr[Q.front] ;
}

