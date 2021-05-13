
//	DYNAMIC PROGRAMMING
//	NAKUL AGGARWAL	|	19CS10044
//	ASSIGNMENT O5	|	WEEK O6
//	08 OCTOBER 2020	|	THURSDAY

#include <stdio.h>
#include <stdlib.h>

//	+++	DEFINITIONS	+++
//	Let p(i,c) be the maximum probability of success of all the reactions from
//	'i' to 'n-1' ( assuming the indexing of reactions to start from 0 )
//	using exactly 'c' units of catalyst ( where 0 <= i <= n-1   and   0 <= c <= C )

//	+++	BASE-CASE +++
//	p(i,0) for all i from 0 to n-1 was initialised to 0
//	p(n-1,c) for all c from 1 to C was initialised to e(n-1,c)
//	where e(n-1,c) holds the same definition as in the assignment

//	+++	RECURSIVE FORMULATION +++
//	p(i,j) = MAX( r varies from 0 to j ) [ ( e(i,j-r) * p(i+1,r) ) ]
//	where 0 <= i <= n-2	and	  1 <= j <= C

int main ()
{
	FILE* input = fopen ( "input.txt" , "r" ) ;
	int n , c ;
	fscanf ( input , "%d" , &n ) ;
	fscanf ( input , "%d" , &c ) ;
	float e[10][31] ;
	for ( int i=0 ; i<n ; i++ )
		for ( int j=1 ; j<=c ; j++ )
			fscanf ( input , "%f" , &(e[i][j]) ) ;
	fclose ( input ) ;
	
	for ( int i=0 ; i<n ; i++ )
		e[i][0] = 0 ;

	float p[10][31] ;
	for ( int i=0 ; i<n ; i++ )
		p[i][0] = 0 ;
	for ( int i=1 ; i<=c ; i++ )
		p[n-1][i] = e[n-1][i] ;
		
	for ( int i=n-2 ; i>=0 ; i-- )
		for ( int j=1 ; j<=c ; j++ )
		{
			float max = -1.0 ;
			for ( int k=j ; k>=0 ; k-- )
				if ( max < e[i][j-k] * p[i+1][k] )	max = e[i][j-k] * p[i+1][k] ;
			p[i][j] = max ;
		}

	FILE* output = fopen ( "output.txt" , "w" ) ;
	fprintf ( output , "%f\n" , p[0][c] ) ;
	int residue = c ;
	for ( int i=0 ; i<n-1 ; i++ )
	{
		for ( int j=0 ; j<=residue ; j++ )
			if ( p[i+1][j]*e[i][residue-j] == p[i][residue] )
			{
				fprintf ( output , "reaction %d : %d\n" , i+1 , residue-j ) ;
				residue = j ;
				break ;
			}
	}
	fprintf ( output , "reaction %d : %d\n" , n , residue ) ;
	fclose ( output ) ;
}
