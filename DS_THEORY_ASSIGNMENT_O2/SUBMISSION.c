
//	DISCRETE STRUCTURES
//	CODING ASSIGNMENT O2
//	NAKUL AGGARWAL		|	19CS10044
//	17 NOVEMBER 2020 	| 	TUESDAY

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	int a , b , c , d ;
} splnum ;

char getSign ( int ) ;
void fixSigns ( splnum* ) ;
void prnspl ( splnum ) ;
splnum reduce ( splnum ) ;
splnum invspl ( splnum ) ;
splnum addspl ( splnum , splnum ) ;
splnum subspl ( splnum , splnum ) ;
splnum mulspl ( splnum , splnum ) ;
splnum divspl ( splnum , splnum ) ;
int areEqual ( splnum , splnum ) ;
void findroots ( int , int , splnum* ) ;
void solvehomogenous ( int , int , int , int , splnum* ) ;
void solvenonhomogeneous ( int , int , int , int , int , splnum , splnum ) ;

int main ()
{
	int r , s , t , a0 , a1 ;
	printf( "\n\nr = " ) ;	scanf( "%d" , &r ) ;
	printf( "s = " ) ;	scanf( "%d" , &s ) ;
	printf( "t = " ) ;	scanf( "%d" , &t ) ;
	printf( "a0 = " ) ;	scanf( "%d" , &a0 ) ;
	printf( "a1 = " ) ;	scanf( "%d" , &a1 ) ;
	splnum ROOTS[2] ;
	solvehomogenous( r , s , a0 , a1 , ROOTS ) ;
	solvenonhomogeneous( r , s , t , a0 , a1 , ROOTS[0] , ROOTS[1] ) ;
	printf( "\n\n" ) ; 
	return 0 ;
}

void solvenonhomogeneous ( int r , int s , int t , int a0 , int a1 , splnum r1 , splnum r2 )
{
	printf( "\n\n+++ Solving the non-homogeneous recurrence\n" ) ;
	printf( "\tCharacteristic equation : " ) ;
	printf( "x^2 + (%d)x + (%d) = 0\n" , -1*r , -1*s ) ;
	printf( "\tROOT 1 : " ) ;	prnspl( r1 ) ;
	printf( "\n\tROOT 2 : " ) ;	prnspl( r2 ) ;
	printf( "\n\tParticular Solution : " ) ;
	if ( r == 2 && s == -1 )
	{
		if ( t % 2 == 0 )	printf( "[%d] n^2\n" , t/2 ) ;
		else	printf( "[%d / 2] n^2\n" , t ) ;
		printf("\tHomogeneous solution :\n\t") ;
		if ( t % 2 == 0 )	printf( "[(%d)n + (%d)]1^n\n" , (a1-a0)-t/2 , a0 ) ;
		else	printf( "[(%d / 2)n + (%d)][1]^n\n" , 2*(a1-a0)-t , a0 ) ;
		return ;
	}
	if ( r + s == 1 )
	{
		if ( r1.a == 1 && r1.c == 1 && (r1.b==0 || r1.d==0) )
			{	splnum tp = r1 ; r1 = r2 ; r2 = tp ;	}
		splnum PS = { t , 0 , 2*s+r , 0 } ;
		printf("[") ; prnspl( reduce(PS) ) ; printf("] n\n") ;
		printf("\tHomogeneous solution :\n\t") ;
		splnum A1 = { a1 , 0 , 1 , 0 } ;
		splnum A0 = { a0 , 0 , 1 , 0 } ;
		splnum C = { t , 0 , r + 2*s , 0 } ;
		splnum UNITY = { 1 , 0 , 1 , 0 } ;
		splnum A = divspl( subspl(subspl(A1,A0),C) , subspl(r1,UNITY) ) ;
		splnum B = subspl( A0 , A ) ;
		printf( "[" ) ;	prnspl( A ) ;	printf( "][" ) ;
		prnspl( r1 ) ;	printf( "]^n + " ) ;	printf( "[" ) ;
		prnspl( B ) ;	printf( "][" ) ;	prnspl( r2 ) ;
		printf( "]^n" ) ;	return ;
	}
	if ( ! ( r*r + 4*s ) )
	{
		splnum PS = { t , 0 , 1-r-s , 0 } ;
		prnspl(reduce(PS)) ; printf("\n") ;
		splnum A1 = { a1 , 0 , 1 , r1.d } ;
		splnum A0 = { a0 , 0 , 1 , r1.d } ;
		splnum C = { t , 0 , 1-r-s , r1.d } ;
		splnum B = subspl(A0,C) ;
		splnum A = subspl( divspl( subspl(A1,C) , r1 ) , B ) ;
		printf("\tHomogeneous solution :\n\t") ;
		printf( "[(" ) ;	prnspl( A ) ;	printf( ")n + (" ) ;
		prnspl( B ) ;	printf( ")][" ) ;	prnspl( r1 ) ;
		printf("]^n\n" ) ;	return ;
	}
	splnum PS = { t , 0 , 1-r-s , 0 } ;
	prnspl(reduce(PS)) ; printf("\n") ;
	splnum A1 = { a1 , 0 , 1 , r1.d } ;
	splnum A0 = { a0 , 0 , 1 , r1.d } ;
	splnum C = { t , 0 , 1-r-s , r1.d } ;
	splnum T1 = mulspl( A0 , r1 ) ;
	splnum T2 = mulspl( C , r1 ) ;
	splnum T3 = subspl( C , A1 ) ;
	splnum T4 = addspl( subspl( T1 , T2 ) , T3 ) ;
	splnum D = subspl( r1 , r2 ) ;
	splnum B = divspl( T4 , D ) ;
	T1 = mulspl( A0 , r2 ) ;
	T2 = mulspl( C , r2 ) ;
	splnum A = divspl( subspl(subspl(T2,T1),T3) , D ) ;
	printf("\tHomogeneous solution :\n\t") ;
	printf( "[" ) ;	prnspl( A ) ;	printf( "][" ) ;
	prnspl( r1 ) ;	printf( "]^n + " ) ;
	printf( "[" ) ;	prnspl( B ) ;	printf( "][" ) ;
	prnspl( r2 ) ;	printf( "]^n" ) ;
	return ;
}

void fixSigns ( splnum* x )
{
	if ( x->c < 0 )
	{
		x->a *= -1 ;
		x->b *= -1 ;
		x->c *= -1 ;
		return ;
	}
}

splnum reduce ( splnum x )
{
	if ( x.a==0 && (x.b==0 || x.d==0) ) 	return x ;
	if ( x.d == 0 || x.b == 0 )
	{
		int u = ( abs(x.a) < abs(x.c) ) ? abs(x.a) : abs(x.c) ;
		for ( int i=u ; i>1 ; i-- )
			if ( x.a % i == 0 && x.c % i == 0 )
				{ x.a /= i ;	x.c /= i ;	break ;	}
		fixSigns( &x ) ;	return x ;
	}
	while ( x.d % 4 == 0 && x.d != 0 )
		{	x.d /= 4 ;	x.b *= 2 ;	}
	if ( x.d < 0 )
	{
		double root = sqrt(-1*x.d) ;
		if ( (int)root == root )
		{
			x.d = -1 ;
			x.b *= (int)root ;
		}
		if ( ! x.a )
		{
			int min = abs(x.b) ;
			if ( abs(x.c) < min )	min = abs(x.c) ;
			for ( int i=min ; i>1 ; i-- )
				if ( x.b % i == 0 && x.c % i == 0 )
					{ x.b /= i ;	x.c /= i ;	break ;	}
			fixSigns( &x ) ;	return x ;
		}
		int min = abs(x.a) ;
		if ( abs(x.b) < min )	min = abs(x.b) ;
		if ( abs(x.c) < min )	min = abs(x.c) ;
		for ( int i=min ; i>1 ; i-- )
		{
			if ( x.a % i == 0 && x.b % i == 0 && x.c % i == 0 )
			{
				x.a /= i ;	x.b /= i ;	x.c /= i ;
				break ;
			}
		}
		fixSigns( &x ) ;	return x ;
	}
	double root = sqrt(x.d) ;
	if ( (int)root == root )
	{
		x.a += (x.b)*(int)root ;
		x.b = x.d = 0 ;
		if ( ! x.a )
		{
			int min = abs(x.b) ;
			if ( abs(x.c) < min )	min = abs(x.c) ;
			for ( int i=min ; i>1 ; i-- )
				if ( x.b % i == 0 && x.c % i == 0 )
				{ x.b /= i ;	x.c /= i ;	break ;	}
			fixSigns( &x ) ;	return x ;
		}
		if ( abs(x.a) == abs(x.c) )
		{
			int f = ( (x.a)*(x.c) < 0 )	? -1 : 1 ;
			x.a = f ;	x.c = 1 ;
			return x ;
		}
		int v = ( abs(x.a) < abs(x.c) ) ? abs(x.a) : abs(x.c) ;
		for ( int i=v ; i>1 ; i-- )
			if ( x.a % i == 0 && x.c % i == 0 )
				{ x.a /= i ;	x.c /= i ;	break ;	}
		fixSigns( &x ) ;	return x ;
	}
	if ( ! x.a )
	{
		int min = abs(x.b) ;
		if ( abs(x.c) < min )	min = abs(x.c) ;
		for ( int i=min ; i>1 ; i-- )
			if ( x.b % i == 0 && x.c % i == 0 )
				{ x.b /= i ;	x.c /= i ;	break ;	}
		fixSigns( &x ) ;	return x ;
	}
	int min = abs(x.a) ;
	if ( abs(x.b) < min )	min = abs(x.b) ;
	if ( abs(x.c) < min )	min = abs(x.c) ;
	for ( int i=min ; i>1 ; i-- )
	{
		if ( x.a % i == 0 && x.b % i == 0 && x.c % i == 0 )
		{
			x.a /= i ;	x.b /= i ;	x.c /= i ;
			break ;
		}
	}
	fixSigns( &x ) ;	return x ;
}

splnum addspl ( splnum u, splnum v )
{
	if ( u.d != v.d )
	{
		printf("\nUNLIKE SPECIAL NUMBERS CANNOT BE ADDED") ;
		exit(4) ;
	}
	splnum sum ;
	sum.d = u.d ;
	sum.a = (u.a)*(v.c) + (v.a)*(u.c) ;
	sum.b = (u.b)*(v.c) + (v.b)*(u.c) ;
	sum.c = (u.c)*(v.c) ;
	return reduce( sum ) ;
}

splnum subspl ( splnum u, splnum v )
{
	if ( u.d != v.d )
	{
		printf("\nUNLIKE SPECIAL NUMBERS CANNOT BE SUBTRACTED") ;
		printf("\n") ; prnspl(u) ; printf("\n") ; prnspl(v) ;
		exit(3) ;
	}
	splnum sub ;
	sub.d = u.d ;
	sub.a = (u.a)*(v.c) - (v.a)*(u.c) ;
	sub.b = (u.b)*(v.c) - (v.b)*(u.c) ;
	sub.c = (u.c)*(v.c) ;
	return reduce( sub ) ;
}

char getSign ( int x )
{
	if ( x < 0 )	return '-' ;
	return '+' ;
}

void prnspl ( splnum x )
{
	if ( x.d == 0 || x.b == 0 )
	{
		if ( x.a == 0 ) {  printf( "0" ) ; return ;  }
		printf( "%d" , x.a ) ;
		if ( x.c != 1 )	 printf( " / %d" , x.c ) ;
		return ;
	}
	if ( x.a == 0 )
	{
		printf( "(" ) ;
		if ( x.b != 1 && x.b != -1 ) printf( "%d*" , x.b ) ;
		else if (x.b < 0)	printf( "%c" , getSign(x.b) ) ;	
		printf( "sqrt(%d))" , x.d ) ;
		if ( x.c != 1 )	printf( " / %d" , x.c ) ;
		return ;
	}
	char c ;
	if ( x.b < 0 )	c = '-' ;
	else	c = '+' ;
	printf( "(%d %c " , x.a , c ) ;
	if ( x.b != 1 && x.b != -1 ) printf( "%d*" , abs(x.b) ) ;
	printf( "sqrt(%d))" , x.d ) ;
	if ( x.c != 1 )	printf( " / %d" , x.c ) ;
}

splnum mulspl ( splnum x , splnum y )
{
	if ( x.d != y.d )
	{
		printf("\nUNLIKE SPECIAL NUMBERS CANNOT BE MULTIPLIED") ;
		exit(2) ;
	}
	splnum z ;
	z.c = x.c * y.c ;
	z.a = x.a*y.a + x.b*y.b*x.d ;
	z.b = x.b*y.a + x.a*y.b ;
	z.d = x.d ;
	return reduce(z) ;
}

splnum invspl ( splnum x )
{
	if ( x.b == 0 || x.d == 0 )
		if ( x.a == 0 )
		{
			printf( "\nINVERSE DOES NOT EXIST FOR ZERO" ) ;
			exit(1) ;
		}
	splnum z ;
	z.c = x.a*x.a - x.b*x.b*x.d ;
	z.a = x.a * x.c ;
	z.b = -1 * x.c * x.b ;
	z.d = x.d ;
	return z ;
}

splnum divspl ( splnum x , splnum y )
{
	if ( x.d != y.d )
	{
		printf("\nUNLIKE SPECIAL NUMBERS CANNOT BE DIVIDED") ;
		exit(0) ;
	}
	return mulspl( x , invspl(y) ) ;
}

void findroots ( int r , int s , splnum roots[] )
{
	splnum r1 = { r , 1 , 2 , r*r + 4*s } ;
	if ( r1.a % 2 == 0 && r1.d % 4 == 0 )
	{
		r1.a /= 2 ;
		r1.c = 1 ;
		r1.d /= 4 ;
	}
	splnum r2 = { r , -1 , 2 , r*r + 4*s } ;
	if ( r2.a % 2 == 0 && r2.d % 4 == 0 )
	{
		r2.a /= 2 ;
		r2.c = 1 ;
		r2.d /= 4 ;
	}
	roots[0] = reduce( r1 ) ;
	roots[1] = reduce( r2 ) ;
	return ;
}

int areEqual ( splnum x , splnum y )
{
	if ( x.a != y.a )	return 0 ;
	if ( x.b != y.b && x.d != 0 )	return 0 ;
	if ( x.c != y.c )	return 0 ;
	if ( x.d != y.d && x.b != 0 )	return 0 ;
	return 1 ;
}

void solvehomogenous ( int r , int s , int a0 , int a1 , splnum* ROOTS )
{
	printf( "\n+++ Solving the homogeneous recurrence\n" ) ;
	printf( "\tCharacteristic equation : " ) ;
	printf( "x^2 + (%d)x + (%d) = 0\n" , -1*r , -1*s ) ;
	findroots( r , s , ROOTS ) ;
	splnum A1 = { a1 , 0 , 1 , 0 } ;
	splnum A0 = { a0 , 0 , 1 , 0 } ;
	if ( ! ( r*r + 4*s ) )
	{
		splnum V = A0 ;
		A1.d = ROOTS[0].d ;
		splnum U = subspl( divspl(A1,ROOTS[0]) , V ) ;
		printf( "\tROOT 1 : " ) ;	prnspl( ROOTS[0] ) ;
		printf( "\n\tROOT 2 : " ) ;	prnspl( ROOTS[0] ) ;
		printf("\n\tHomogeneous solution :\n\t") ;
		printf( "[(" ) ;	prnspl( U ) ;	printf( ")n + (" ) ;
		prnspl( V ) ;	printf( ")][" ) ;	prnspl( ROOTS[0] ) ;
		printf("]^n\n" ) ;	return ;
	}
	splnum r1 = ROOTS[0] ;
	splnum r2 = ROOTS[1] ;
	printf( "\tROOT 1 : " ) ;	prnspl( r1 ) ;
	printf( "\n\tROOT 2 : " ) ;	prnspl( r2 ) ;
	printf("\n\tHomogeneous solution :\n\t") ;
	A1.d = A0.d = r1.d ;
	splnum U , V ;
	U = divspl( subspl(A1,mulspl(A0,r2)) , subspl(r1,r2) ) ;
	V = divspl( subspl(mulspl(A0,r1),A1) , subspl(r1,r2) ) ;
	printf( "[" ) ;	prnspl( U ) ;	printf( "][" ) ;
	prnspl( ROOTS[0] ) ;	printf( "]^n + " ) ;	printf( "[" ) ;
	prnspl( V ) ;	printf( "][" ) ;	prnspl( ROOTS[1] ) ;
	printf( "]^n" ) ;	return ;
}
