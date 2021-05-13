//	DIVIDE AND CONQUER
//	WEEK O3
// 	NAKUL AGGARWAL		|	19CS10044
//	17 SEPTEMBER 2020	|	THURSDAY

#include <stdio.h>
#include <stdlib.h>

typedef struct  {
	// x coordinate of left side
	int left;
	// height
	int ht;
	// x coordinate of right side
	int right;
} Box;

// A Point in Outline
typedef struct  {
	// x coordinate
	int x;
	// height or the y coordinate
	int y;
} Point;

Point* findOutLine(Box boxes[], int size, int *outputsize) ;

void prettyPrint(Point* points, int outputsize) {
	int i;
	printf(" OutLine for given Boxes is \n[");
	for (i = 0; i < outputsize; i++) {
		
		printf(" (%d, %d), ", points[i].x, points[i].y);

	}
	printf("\b\b ]\n");
}

void process() {
	int n ;
	scanf("%d", &n) ;
	Box boxes[n] ;
	int i ;
	for (i = 0; i < n; i++) {
		scanf("%d %d %d", &boxes[i].left , &boxes[i].right , &boxes[i].ht) ;
	}
	int outputsize ;
	Point* ptr = findOutLine(boxes, n, &outputsize) ;

	prettyPrint(ptr, outputsize) ;
}

Point* combine_outlines( Point* l1 , Point* l2 , int* outputSize , int size )
{
	int i=0 , j=0 ;
	int cho_1 = 0 ;
	int cho_2 = 0 ;
	Point* outline = ( Point* ) calloc ( size , sizeof(Point) ) ;
	int k=0 ;
	
	while( l1[i].x != -1 && l2[j].x != -1 ) 
	{
		if( l1[i].x < l2[j].x )
		{
			cho_1 = l1[i].y ;
			Point temp ;
			temp.x = l1[i].x ;
			temp.y = (cho_1>cho_2) ? cho_1 : cho_2 ;
			if ( k>0 && outline[k-1].x == temp.x && outline[k-1].y != temp.y )
			{
				outline[k-1] = temp ;
				i++ ; continue ;
			}
			if ( ! ( outline[k-1].x == temp.x && outline[k-1].y == temp.y ) && outline[k-1].y != temp.y )
				outline[k++] = temp ;
			i++ ;
			continue ;
		}
		if( l1[i].x >= l2[j].x )
		{
			cho_2 = l2[j].y ;
			Point temp ;
			temp.x = l2[j].x ;
			temp.y = (cho_1>cho_2) ? cho_1 : cho_2 ;
			if ( k>0 && outline[k-1].x == temp.x && outline[k-1].y != temp.y )
			{
				outline[k-1] = temp ;
				j++ ; continue ;
			}
			if ( ! ( outline[k-1].x == temp.x && outline[k-1].y == temp.y ) && outline[k-1].y != temp.y )
				outline[k++] = temp ;
			j++ ;
			continue ;
		}
	}
	
	if( l1[i].x == -1 )
	{
		while(l2[j].x != -1)
		{
			if ( k>0 && outline[k-1].x == l2[j].x && outline[k-1].y != l2[j].y )
			{
				outline[k-1] = l2[j] ;
				j++ ; continue ;
			}
			outline[k++] = l2[j++] ;
		}
		Point temp = { -1 , -1 } ;
		outline[k] = temp ;
		*outputSize = k ;
		return outline ;
	}
	
	while(l1[i].x != -1)
	{
		if ( k>0 && outline[k-1].x == l1[i].x && outline[k-1].y != l1[i].y )
		{
			outline[k-1] = l1[i] ;
			i++ ; continue ;
		}
		outline[k++] = l1[i++] ;
	}
	Point temp = { -1 , -1 } ;
	outline[k] = temp ;
	*outputSize = k ;
	return outline ;
}

Point* findOutLine( Box* boxes , int size , int* outputSize )
{
	if ( size==1 )
	{
		Point* outline = ( Point* ) calloc ( 3 , sizeof(Point) ) ;
		Point p1 = { boxes[size-1].left , boxes[size-1].ht } ;
		Point p2 = { boxes[size-1].right , 0 } ;
		Point p3 = { -1 , -1 } ;
		outline[0] = p1 ; outline[1] = p2 ; outline[2] = p3 ;
		*outputSize = 2 ;
		return outline ;
	}
	int s1 = 0 , s2 = 0 ;
	Point* outline1 = findOutLine( boxes , size/2 , &s1 ) ;
	Point* outline2 = findOutLine( boxes+size/2 , size-size/2 , &s2 ) ;

	Point* outline = combine_outlines( outline1 , outline2 , outputSize , s1+s2 ) ;
	
	return outline ;
}

int main()
{
	process() ;
}
