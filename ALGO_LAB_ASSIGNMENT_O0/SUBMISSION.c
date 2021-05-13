
//	USING DOUBLY LINKED LISTS
//	NAME : NAKUL AGGARWAL	|	ROLL NO : 19CS10044
//	ASSIGNMENT-O1			|	03 SEPTEMBER 2020


#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data ;
	struct _node* add ;
} node ;

void traverse_from_front_to_end(node*) ; 
void traverse_from_end_to_front(node*) ;
void reverse(node**, node**) ;
void alternate(node**, node**) ;


int main()
{
	int n ;
	printf ("n = ") ;
	scanf ("%d", &n) ;
	
	node* head = ( node* ) malloc ( sizeof(node) ) ;
	node* prev = NULL ;
	node* current = head ;
	
	node* tail ;
	printf("Enter the 10 integers between -100 to 100: ") ;
	
	for ( int i=1 ; i<=n ; i++ )
	{
		scanf(" %d,", &(current->data)) ;
		node* next ;
		if ( i != n )
			next = ( node* ) malloc ( sizeof(node) ) ;
		else
			next = NULL ;
			tail = current ;
		
		current->add =  (node*) ( (unsigned long long)prev ^ (unsigned long long)next ) ;
		prev = current ;
		current = next ;
	}
	
	printf("Doubly linked list traversed from front to end:") ;
	traverse_from_front_to_end(head) ;
	
	printf("\nDoubly linked list traversed from end to front:") ;
	traverse_from_end_to_front(tail) ;
	
	reverse(&head, &tail) ;
	
	printf("\nReversed doubly linked list traversed from front to end: ") ;
	traverse_from_front_to_end(head) ;
	
	alternate(&head, &tail) ;
	
	printf("\nAlternated doubly linked list traversed from front to end: ") ;
	traverse_from_front_to_end(head) ;
}


void traverse_from_front_to_end(node* head)
{
	node* previous = NULL ;
	node* curr = head ;
	while ( curr != NULL )
	{
		printf(" %d ,", curr->data) ;
		node* temp = curr ;
		curr = (node*) ( (unsigned long long)previous ^ (unsigned long long)(curr->add) ) ;
		previous = temp ;
	}
}

void traverse_from_end_to_front(node* tail)
{
	node* previous = NULL ;
	node* curr = tail ;
	while ( curr != NULL )
	{
		printf(" %d ,", curr->data) ;
		node* temp = curr ;
		curr = (node*) ( (unsigned long long)previous ^ (unsigned long long)(curr->add) ) ;
		previous = temp ;
	}
}

void reverse(node **head, node **tail)
{
	node* temp = *head ;
	*head = *tail ;
	*tail = temp ;
}


void alternate(node** head, node** tail)
{
	int n = 0 ;
	
	node* previous = NULL ;
	node* curr = *head ;
	while ( curr != NULL )
	{
		node* temp = curr ;
		curr = (node*) ( (unsigned long long)previous ^ (unsigned long long)(curr->add) ) ;
		previous = temp ;
		n++ ;
	}
	
	node** addresses = ( node** ) calloc ( n, sizeof(node*)) ;
	int i=0 ;
	previous = NULL ;
	curr = *head ;
	while ( curr != NULL )
	{
		addresses[i] = curr ;
		node* temp = curr ;
		curr = (node*) ( (unsigned long long)previous ^ (unsigned long long)(curr->add) ) ;
		previous = temp ;
		i++ ;
	}
	
	previous = NULL ;
	curr = *head ;
	curr->add = (node*) ( (unsigned long long)NULL ^ (unsigned long long)addresses[n-1] ) ;
	for(int k=1; k<n; k++)
		addresses[k]->add = (node*) ( (unsigned long long)addresses[n-k] ^ (unsigned long long)addresses[n-k-1] ) ;
	
	free(addresses) ;
	
	previous = NULL ;
	curr = *head ;
	int c = 0 ;
	while(1)
	{
		node* temp = curr ;
		curr = (node*) ( (unsigned long long)previous ^ (unsigned long long)(curr->add) ) ;
		previous = temp ;
		c++ ;
		if (c==n-1)
		{
			*tail = curr ;
			curr->add = (node*) ( (unsigned long long)previous ^ (unsigned long long)NULL ) ;
			break;
		}
	}
}

