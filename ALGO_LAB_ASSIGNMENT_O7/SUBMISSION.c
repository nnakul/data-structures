
//	GRAPH ALGORITHMS (GREEDY APPROACH)
//	NAKUL AGGARWAL	|	19CS10044
//	ASSIGNMENT O8	|	WEEK O9
//	29 OCTOBER 2020	|	THURSDAY

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define		INF	21474836

typedef struct {
	int i , j ;
} POINT ;

int isValidNg ( int , int , int ) ;
int more ( int , int ) ;
void findPath ( int** , int , POINT* , int* , int* , int** , int , int , int , int ) ;

int main ()
{
	int n ;
	scanf ( "%d" , &n ) ;
	int** grid = ( int** ) calloc ( n , sizeof(int*) ) ;
	for ( int i=0 ; i<n ; i++ )
	{
		grid[i] = ( int* ) calloc ( n , sizeof(int) ) ;
		for ( int j=0 ; j<n ; j++ )
			scanf( "%d" , &(grid[i][j]) ) ;
	}
	
	int sx , sy , fx , fy ;
	scanf ( "%d %d %d %d" , &sx , &sy , &fx , &fy ) ;
	
	int TIME = 0 , INDEX = 0 ;
	POINT* onPath = ( POINT* ) calloc ( n*n , sizeof(POINT) ) ;
	
	int** visited = ( int** ) calloc ( n , sizeof(int*) ) ;
	for ( int i=0 ; i<n ; i++ )
	{
		visited[i] = ( int* ) calloc ( n , sizeof(int) ) ;
		for ( int j=0 ; j<n ; j++ )
			visited[i][j] = 0 ;
	}
	visited[sx][sy] = 1 ;
	
	findPath ( grid , n , onPath , &TIME , &INDEX , visited , sx , sy , fx , fy ) ;
	printf("Minimum time taken is: %d\nThe Path to reach from (%d,%d) to (%d,%d) is:\n  (%d,%d)", TIME,sx,sy,fx,fy,sx,sy) ;
	for ( int i=0 ; i<INDEX ; i++ )
		printf("  (%d,%d)", onPath[i].i , onPath[i].j) ;
	printf("\nThe Number of Blocks traversed are: %d\n\n", INDEX+1) ;
}

int isValidNg ( int i , int j , int n )
{
	if ( i < 0 || i >= n )	return 0 ;
	if ( j < 0 || j >= n )	return 0 ;
	return 1 ;
}

int more ( int a , int b )
{
	if ( a > b )	return a ;
	return b ;
}

void findPath ( int** grid , int n , POINT* path , int* TIME , int* INDEX , int** visited , int sx , int sy , int fx , int fy )
{
	if ( sx == fx && sy == fy )	return ;
	
	int si = sx , sj = sy ;
	POINT p1 , p2 , p3 , p4 ;
	p1.i = si-1 ; p1.j = sj ;
	p2.i = si ; p2.j = sj+1 ;
	p3.i = si+1 ; p3.j = sj ;
	p4.i = si ; p4.j = sj-1 ;
	POINT ng[] = { p1 , p2 , p3 , p4 } ;
	
	int min = INF ;
	POINT near ;
	int now = more( *TIME , grid[si][sj] ) ;
	int elng , count = 4 ;
	for ( int i=0 ; i<count ; i++ )
	{
		int ngi = ng[i].i , ngj = ng[i].j ;
		if ( ! isValidNg(ngi,ngj,n) )	continue ;
		int current = more( *TIME , grid[ngi][ngj] ) ;
		if ( ! visited[ngi][ngj] && fabs(current-now) <= min )
		{
			if ( si == count && !sj )
			{
				visited[ngi][ngj] = 1 ;
				near = p2 ;
				min = fabs(current-now) ;
				elng = current ;
				break ;
			}
			if ( si == 2*count-1 && ngj < sj )	continue ;
			visited[ngi][ngj] = 1 ;
			min = fabs(current-now) ;
			elng = current ;
			near = ng[i] ;
			continue ;
		}
	}
	if(min)	(*TIME) = more(elng,now) ;
	path[(*INDEX)++] = near ;
	findPath ( grid , n , path , TIME , INDEX , visited , near.i , near.j , fx , fy ) ;
}
