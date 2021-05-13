#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char att[101] ; 
	int nassoc ;
	int assoc[500] ;
} htnode ;

typedef struct {
	int S ;
	htnode *A , *B ;
} hashtable ;

hashtable insertpair ( hashtable T , char* x , char* y ) ;
int h ( char* str , int S ) ;
hashtable inittable ( int S ) ;
hashtable deletepair ( hashtable T , char* x , char* y ) ;
void searchattr ( hashtable T , char* str , int a ) ;

int main ()
{
	hashtable H = inittable( 29989 ) ;
	char x[101], y[101] ;
	int choice ;
	printf("\n\n") ;
	while(1)
	{
		printf("+++ Enter choice: ") ;
		scanf( "%d" , &choice ) ;
		if ( ! choice )	break ;
		if ( choice < 3 )
			scanf( " %s %s" , x , y ) ;
		else
			scanf( " %s" , x ) ;
		if (choice==1) 	H = insertpair(H,x,y) ;
		if (choice==2)	H = deletepair(H,x,y) ;
		if (choice==3) 	searchattr(H,x,1) ;
		if (choice==4) 	searchattr(H,x,2) ;
	}
	printf( "\n\nGOODBYE!" ) ;
}

int h ( char* str , int S )
{
	int H = 0 , a = 37 , l = strlen(str) ;
	for ( int i=0 ; i<l ; i++ )
		H = ( a*H + str[i] ) % S ;
	return H ;
}

hashtable inittable ( int S )
{
	hashtable T ;
	T.S = S ;
	T.A = ( htnode* ) calloc ( S , sizeof(htnode) ) ;
	T.B = ( htnode* ) calloc ( S , sizeof(htnode) ) ;
	for ( int i=0 ; i<S ; i++ )
	{
		T.A[i].nassoc = T.B[i].nassoc = 0 ;
		strcpy( T.A[i].att , "EMPTY" ) ;
		strcpy( T.B[i].att , "EMPTY" ) ;
	}
	return T ;
}

void searchattr ( hashtable T , char* str , int a )
{
	int S = T.S ;
	if ( a == 1 )
	{
		printf( "\t( %s , - ) is associated with: " , str ) ;
		int I = h(str,S) ;
		int i = I ;
		if ( strcmp(str,T.A[I].att) )
		{
			i = ( I + 1 ) % S ;
			while ( 1 )
			{
				if ( i == I )
					{ printf("\n") ; return ; }
				if ( ! strcmp(str,T.A[i].att) )	break ;
				i = ( i + 1 ) % S ;
			}
		}
		int SIZE = T.A[i].nassoc ;
		for ( int k=0 ; k<SIZE ; k++ )
			printf( "%s " , T.B[T.A[i].assoc[k]].att ) ;
		printf("\n") ;
		return ;
	}
	if ( a == 2 )
	{
		printf( "\t( - , %s ) is associated with: " , str ) ;
		int I = h(str,S) ;
		int i = I ;
		if ( strcmp(str,T.B[I].att) )
		{
			i = ( I + 1 ) % S ;
			while ( 1 )
			{
				if ( i == I )
					{ printf("\n") ; return ; }
				if ( ! strcmp(str,T.B[i].att) )	break ;
				i = ( i + 1 ) % S ;
			}
		}
		int SIZE = T.B[i].nassoc ;
		for ( int k=0 ; k<SIZE ; k++ )
			printf( "%s " , T.A[T.B[i].assoc[k]].att ) ;
		printf("\n") ;
		return ;
	}
}

hashtable deletepair ( hashtable T , char* x , char* y )
{
	int S = T.S ;
	int I1 = h(x,S) ;
	int I2 = h(y,S) ;
	int i1 = I1 , i2 = I2 ;
	if ( strcmp(x,T.A[I1].att) )
	{
		i1 = ( I1 + 1 ) % S ;
		while ( 1 )
		{
			if ( i1 == I1 )
			{
				printf( "\tRELATION NOT FOUND\n" ) ;
				return T ;
			}
			if ( ! strcmp(x,T.A[i1].att) )	break ;
			i1 = ( i1 + 1 ) % S ;
		}
	}
	if ( strcmp(y,T.B[I2].att) )
	{
		i2 = ( I2 + 1 ) % S ;
		while ( 1 )
		{
			if ( i2 == I2 )
			{
				printf( "\tRELATION NOT FOUND\n" ) ;
				return T ;
			}
			if ( ! strcmp(y,T.B[i2].att) )	break ;
			i2 = ( i2 + 1 ) % S ;
		}
	}
	int k , SIZE = T.A[i1].nassoc ;
	for ( k=0 ; k<SIZE ; k++ )
		if ( T.A[i1].assoc[k] == i2 )
		{
			T.A[i1].assoc[k] = T.A[i1].assoc[T.A[i1].nassoc-1] ;
			T.A[i1].nassoc-- ;
			break ;
		}
	if ( k == SIZE )
	{
		printf( "\tRELATION NOT FOUND\n" ) ;
		return T ;
	}
	for ( k=0 ; k<T.B[i2].nassoc ; k++ )
		if ( T.B[i2].assoc[k] == i1 )
		{
			T.B[i2].assoc[k] = T.B[i2].assoc[T.B[i2].nassoc-1] ;
			T.B[i2].nassoc-- ;
			break ;
		}
	printf( "\thash = (%d,%d), deletion at (%d,%d)\n" , I1 , I2 , i1 , i2 ) ;
	if ( ! T.B[i2].nassoc )	strcpy( T.B[i2].att , "DELETED" ) ;
	if ( ! T.A[i1].nassoc )	strcpy( T.A[i1].att , "DELETED" ) ;
	return T ;
}

hashtable insertpair ( hashtable T , char* x , char* y )
{
	int S = T.S ;
	int I1 = h(x,S) ;
	int I2 = h(y,S) ;
	int i1 = I1 , i2 = I2 ;
	int found = 0 ;
	if ( ! strcmp(x,T.A[i1].att) )	found = 1 ;
	if ( ! found )
	{
		i1++ ;
		while ( i1 != I1 )
		{
			if ( ! strcmp(x,T.A[i1].att) )
			{
				found = 1 ;
				break ;
			}
			i1 = ( i1 + 1 ) % S ;
		}
	}
	if ( ! found )
	{
		i1 = I1 ;
		while ( T.A[i1].nassoc )
			i1 = ( i1 + 1 ) % S ;
	}

	found = 0 ;
	if ( ! strcmp(y,T.B[i2].att) )	found = 1 ;
	if ( ! found )
	{
		i2++ ;
		while ( i2 != I2 )
		{
			if ( ! strcmp(y,T.B[i2].att) )
			{
				found = 1 ;
				break ;
			}
			i2 = ( i2 + 1 ) % S ;
		}
	}
	if ( ! found )
	{
		i2 = I2 ;
		while ( T.B[i2].nassoc )
			i2 = ( i2 + 1 ) % S ;
	}
	printf( "\thash = (%d,%d), insertion at (%d,%d)\n" , I1 , I2 , i1 , i2 ) ;
	if ( ! T.A[i1].nassoc )
		strcpy( T.A[i1].att , x ) ;
	T.A[i1].assoc[T.A[i1].nassoc] = i2 ;
	T.A[i1].nassoc ++ ;
	if ( ! T.B[i2].nassoc )
		strcpy( T.B[i2].att , y ) ;
	T.B[i2].assoc[T.B[i2].nassoc] = i1 ;
	T.B[i2].nassoc ++ ;
	return T ;
}
