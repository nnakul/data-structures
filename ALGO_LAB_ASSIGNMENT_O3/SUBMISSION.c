
//	TREES DATA STRUCTURE
//	NAKUL AGGARWAL	|	19CS10044
//	1 OCTOBER 2020	|	THURSDAY
//	ASSIGNMENT O4	|	WEEK O5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 500

typedef struct node {
	char symbol[100] ;
	int frequency ;
	struct node *next ;
	struct node *right ;
	struct node *left ;
} node ;

void updateFreqDist ( char* string , int* freq )
{
	int length = strlen( string ) ;
	for ( int i=0 ; i<length ; i++ )
	{
		if ( string[i] >= '0' && string[i] <= '9' )
			freq[ string[i] - '0' ] ++ ;
		else	freq[ string[i] - 'a' + 10 ] ++ ;
	}
	return ;
}

void printFreqTable ( int* freq , char* C)
{
	for ( int i=0 ; i<10 ; i++ )
	{
		printf("\n%c - %d", C[i] , freq[i]) ;
	}
	for ( int i=10 ; i<36 ; i++ )
	{
		printf("\n%c - %d", C[i] , freq[i]) ;
	}
}

int priority ( char c1 , char c2 )
{
	int p1 , p2 ;
	if ( c1 >= 'a' && c1 <= 'z' )	p1 = c1-'a'+1 ;
	else		p1 = 36+c1-'9' ;
	if ( c2 >= 'a' && c2 <= 'z' )	p2 = c2-'a'+1 ;
	else		p2 = 36+c2-'9' ;
	return p1-p2 ;
}

node* makeLinkedList ( int* freq , char* C )
{
	int i = 0 ;
	node* head = ( node* )	malloc ( sizeof(node) ) ;
	head->right = head->left = NULL ;
	char temp[] = { C[i] , '\0' } ;
	strcpy ( head->symbol , temp ) ;
	head->frequency = freq[i] ;
	head->next = ( node* )	malloc ( sizeof(node) ) ;
	node* p = head->next ;
	i++ ;
	for ( ; i<35 ; i++ )
	{
		p->frequency = freq[i] ;
		char* tempp = ( char* ) calloc ( 2 , sizeof(char) ) ;
		tempp[0] = C[i] ; tempp[1] = '\0' ;
		strcpy ( p->symbol , tempp ) ;
		free(tempp) ;
		p->left = p->right = NULL ;
		p->next = ( node* )	malloc ( sizeof(node) ) ;
		p = p->next ;
	}
	p->left = p->right = p->next = NULL ;
	p->frequency = freq[i] ;
	char temppp[] = { C[i] , '\0' } ;
	strcpy ( p->symbol , temppp ) ;
	return head ;
}

void merge( int* A , int* B , int* C , char* CA , char* CB , char* CC , int s1 , int s2 )
{
	int i = 0 , j = 0 , k = 0 ;
	while ( i<s1 && j<s2 )
	{
		if ( B[i] < C[j] )
		{
			A[k] = B[i] ;
			CA[k] = CB[i] ;
			i ++ ;
		}
		else
		{
			if ( B[i] > C[j] )
			{
				A[k] = C[j] ;
				CA[k] = CC[j] ;
				j ++ ;
			}
			else
			{
				
				if ( priority( CC[j] , CB[i] ) > 0 )
				{
					A[k] = C[j] ;
					CA[k] = CC[j] ;
					j ++ ;
				}
				else
				{
					A[k] = B[i] ;
					CA[k] = CB[i] ;
					i ++ ;
				}
			}
		}
		k ++ ;
	}
	if ( i == s1 )
	{
		for ( int x=j ; x<s2 ; x++ )
		{
			A[k] = C[j] ;
			CA[k] = CC[j] ;
			j++ ;
			k++ ;
		}
	}
	else
	{
		for ( int x=i ; x<s1 ; x++ )
		{
			A[k] = B[i] ;
			CA[k] = CB[i] ;
			i++ ;
			k++ ;
		}
	}
}



void merge_sort( int* A , int n , char* CHAR )
{
	if ( n == 1)	return ;
	int high = n-1 ;
	int low = 0 ;
	int mid = ( high + low ) / 2 ;
	int s1 = mid-low+1 ;
	int s2 = n - s1 ;
	int* B = ( int* ) calloc ( s1 , sizeof(int) ) ;
	int* C = ( int* ) calloc ( s2 , sizeof(int) ) ;
	
	char* D = ( char* ) calloc ( s1 , sizeof(char) ) ;
	char* E = ( char* ) calloc ( s2 , sizeof(char) ) ;
	
	for ( int i=0 ; i<s1 ; i++ )
	{
		B[i] = A[i] ;
		D[i] = CHAR[i] ;
	}
	for ( int i=0 ; i<s2 ; i++ )
	{
		C[i] = A[s1+i] ;
		E[i] = CHAR[s1+i] ;
	}
	merge_sort( B , s1 , D ) ;
	merge_sort( C , s2 , E ) ;
	merge( A , B , C , CHAR , D , E , s1 , s2 ) ;
	free( B ) ;
	free( C ) ;
	free( D ) ;
	free( E ) ;
}

int priorityStrings ( char* s1 , char* s2 )
{
	if ( strlen(s1) == 1 && strlen(s2) == 1 )
		return priority( s1[0] , s2[0] ) ;
	if ( strlen(s1) == 2 && strlen(s2) == 2 )
		return strcmp( s2 , s1 ) ;
	if ( strlen(s2) < strlen(s1) )	return -1 ;
	return 1 ;
}

node* makeTree ( node* head , int count )
{
	if ( head->next == NULL )	return head ;
	node* super = ( node* ) malloc ( sizeof(node) ) ;
	node* p1 = head ;
	node* p2 = head->next ;
	super->left = p1 ;
	super->right = p2 ;
	super->frequency = p1->frequency + p2->frequency ;
	head = p2->next ;
	char temp[] = { 'N' , '\0' } ;
	char snum[5] ;
	itoa(count, snum, 10);
	strcat( temp , snum ) ;
	strcpy ( super->symbol , temp ) ;
	p1->next = p2->next = NULL ;
	
	node* p = head ;
	if (p==NULL)	return super ;
	if ( p->frequency > super->frequency )
	{
		head = super ;
		super->next = p ;
		return head ;
	}
	
	while ( p->next != NULL )
	{
	
		if ( p->frequency < super->frequency && p->next->frequency > super->frequency )
		{
			
			node* temp = p->next ;
			p->next = super ;
			super->next = temp ;
			return head ;
		}
		if ( p->frequency == super->frequency )
		{
		
			if ( priorityStrings( p->symbol , super->symbol ) > 0 && priorityStrings( p->next->symbol , super->symbol ) < 0 )
			{
				node* temp = p->next ;
				p->next = super ;
				super->next = temp ;
				return head ;
			}
		}
		
		p = p->next ;
		
	}
	p->next = super ;
	super->next = NULL ;
	return head ;
}

void treeTraversal ( node* root , int* count , char* chars , char* curr , char** code )
{
	if ( root == NULL )	return ;
	
	if ( root->left == NULL && root->right == NULL )
	{
		chars[*count] = root->symbol[0] ;
		
		strcpy( code[*count] , curr ) ;
		*count ++ ;
		return ;
	}
	char temp[] = "" ;
	strcat ( temp , curr ) ;
	strcat ( temp , "0" ) ;
	treeTraversal( root->left , count , chars , temp , code ) ;
	char tempp[] = "" ;
	strcat ( tempp , curr ) ;
	strcat ( tempp , "1" ) ;
	treeTraversal( root->right , count , chars , tempp , code ) ;
}

void preOrderTraversal ( node* root )
{
	if ( root == NULL )	return ;
	printf ( " %s (%d) " , root->symbol , root->frequency ) ;
	preOrderTraversal ( root->left ) ;
	preOrderTraversal ( root->right ) ;
}


void quick_sort( char** codes , char* chars , int si , int ei )
{
	if ( si >= ei ) return ;
	char pivot = chars[si] ;
	int i = si ;
	int j = si + 1 ;
	while ( j<=ei )
	{
		if ( chars[j] < pivot )
		{
			i++ ;
			char temp = chars[i] ;
			chars[i] = chars[j] ;
			chars[j] = temp ;
			char* t = codes[i] ;
			codes[i] = codes[j] ;
			codes[j] = t ;
		}
		j++ ;
	}
	
	
	char temp = chars[i] ;
	chars[i] = chars[si] ;
	chars[si] = temp ;
	char* t = codes[i] ;
	codes[i] = codes[si] ;
	codes[si] = t ;
	
	quick_sort( codes , chars , si , i-1 ) ;
	quick_sort( codes , chars , i+1 , ei ) ;
}


int main ()
{
	FILE* fptr = fopen ( "log.txt" , "r" ) ;
	int n ;
	int frequency[36] = { 0 } ;
	char characters[36] ;
	for ( int i=0 ; i<10 ; i++ )	characters[i] = i + '0' ;
	for ( int i=10 ; i<36 ; i++ )	characters[i] = i + 'a' - 10 ;
	fscanf ( fptr , " %d " , &n ) ;
	for ( int i=0 ; i<n ; i++ )
	{
		char temp[MAXLEN] ;
		fscanf ( fptr , " %s " , temp ) ;
		updateFreqDist ( temp , frequency ) ;
	}
	fclose( fptr ) ;
	
	for ( int i=10 ; i<36 ; i++ )
		printf ( " %c = %d , " , characters[i] , frequency[i] ) ;
	for ( int i=0 ; i<10 ; i++ )
		printf ( " %c = %d , " , characters[i] , frequency[i] ) ;
	
	merge_sort ( frequency , 36 , characters ) ;
	printf("\n\n") ;
	
	node* head = makeLinkedList( frequency , characters ) ;
	int count = 1 ;
	while ( head->next != NULL )
	{
		head = makeTree( head , count ) ;
		if ( head->next == NULL )	break ;
		count ++ ;
	}
	char** codes = ( char** ) calloc ( 36 , sizeof(char*) ) ;
	for ( int i=0 ; i<36 ; i++ )
		codes[i] = ( char* ) calloc ( MAXLEN+1 , sizeof(char) ) ;

	int m = 0 ;
	char initial[] = "" ;
	treeTraversal( head , &m , characters , initial , codes ) ;
	
	preOrderTraversal ( head ) ;
	
	quick_sort( codes , characters , 0 , 35 ) ;
	for ( int i=0 ; i<36 ; i++ )
		printf("\n%c %s", characters[i] , codes[i]) ;
}
