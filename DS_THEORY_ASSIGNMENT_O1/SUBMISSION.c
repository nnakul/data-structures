#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 10000

/**********************************************************/
/************** Stack Datatype and Operations *************/
/**********************************************************/

// stack structure declaration
typedef struct stackADT {
    char opr[MAX];
    int top;
} Stack;

// initialize stack
void initStack (Stack *stack)
{
    stack->top = -1;
}

// check whether stack is empty
int isEmptyStack (Stack *stack)
{
    return (stack->top == -1);
}

// check whether stack is full
int isFullStack (Stack *stack)
{
    return (stack->top == MAX-1);
}

// push an element into stack
void push (Stack *stack, char x)
{
    if (isFullStack(stack))
        printf("Error: Stack is Full!\n");
    else
        stack->opr[++(stack->top)] = x;
}

// pop an element from stack
char pop (Stack *stack)
{
    char x;
    if (isEmptyStack(stack))
        printf("Error: Stack is Empty!\n");
    else
        x = stack->opr[(stack->top)--];
    return x;
}

/**********************************************************/


/**********************************************************/
/*********** Binary Tree Datatype and Operations **********/
/**********************************************************/

// binary tree structure declaration
typedef struct binTree {
    char element;
    struct binTree *leftChild;
    struct binTree *rightChild;
} BT;

// creating a node in binary tree
BT *createNode (char el)
{
    BT *newNode;
    if ( (newNode=(BT *)malloc(sizeof(BT))) == NULL )
        printf("Error: Malloc Error in Creating Node!\n");
    else {
        newNode->element = el;
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
    }
    return (newNode);
}

// creating an exact replica of the the binary tree
BT *duplicate(BT *orig)
{
    BT *dup = NULL;
    if(orig != NULL) {
        dup = createNode(orig->element);
        dup->leftChild = duplicate(orig->leftChild);
        dup->rightChild = duplicate(orig->rightChild);
    }
    return (dup);
}

/**********************************************************/


/**********************************************************/
/******************** Utility Functions *******************/
/**********************************************************/

// structure holding propositional values
typedef struct PropVal {
    char prop;
    int val; // '0' for False and '1' for 1
} PV;

// scan every propositional values (one by one) from user as input
PV *scanPropValueInput( unsigned int* N )
{
    unsigned int noProp, i;
    PV *pvarr;
    
    printf("Enter Total Number of Propositions: ");
    scanf("%u",&noProp);
    
    pvarr = (PV *)malloc(noProp * sizeof(PV));
    
    for (i = 0; i < noProp; i++) {
        printf("Enter Proposition [%u] (Format: Name <SPACE> Value): ", i+1);
        scanf(" %c %d", &pvarr[i].prop, &pvarr[i].val);
    }
    *N = noProp ;
    return pvarr;
}

// determines whether p is a proposition including 0 or 1
int isProposition (char p)
{
    return ( ((p >= 'a') && (p <= 'z')) || ((p >= 'A') && (p <= 'Z')) || (p == '0') || (p == '1') );
}

// printing the validity and satisfiability flags
void printResult (int valid, int sat)
{
    printf("\nThe Given Formula is: < ");
    valid ? printf("VALID") : printf("INVALID");
    printf(" + ");
    sat ? printf("SATISFIABLE") : printf("UNSATISFIABLE");
    printf(" >\n\n");
}

//display postfix form of propositional formula (from internally represented string)
void displayPfForm(char *pfForm)
{
    int i;
    
    printf("Postfix Representation of Formula:");
    for(i = 0; pfForm[i] != '\0'; i++){
        if ( pfForm[i] == '-' )
            printf(" ->");
        else if (pfForm[i] == '~')
            printf(" <->");
        else
            printf(" %c", pfForm[i]);
    }
    printf("\n");
}

// count number of characters in the formula representing only propositions and operators
int noOfIdsInFormula (char *formula)
{
    int i, len = strlen(formula), count = 0;
    for(i = 0; i < len; i++){
        if ( (formula[i] != '(') && (formula[i] != ')') && (formula[i] != ' ') && (formula[i] != '\t') )
            count++;
    }
    return count;
}

// pre-defined priority of in-stack element
int inStackPriority (char op){
    switch(op){
        case '!': return 3; break;
        
        case '&':
        case '|': return 2; break;
        
        case '~':
        case '-': return 1; break;
        
        case '(': return 0; break;
        
        default : return -1; break;
    }
}

// pre-defined priority of in-coming element
int inComingPriority (char op){
    switch(op){
        case '!': return 4; break;
        
        case '&':
        case '|': return 2; break;
        
        case '~':
        case '-': return 1; break;
        
        case '(': return 4; break;
        
        default : return -1; break;
    }
}

// generate postfix formula from the given input formula
char *genPostFixFormula(char *formula)
{
    int noOfIds = noOfIdsInFormula(formula), i, len = strlen(formula), k;
    char *pf = (char *)malloc((noOfIds+1) * sizeof(char));
    char out;
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    initStack(stack); push(stack,'#');
    
    for (i = 0, k = 0; i < len; i++){
        if ( (formula[i] != ' ') && (formula[i] != '\t') ){
            if ( isProposition(formula[i]) )
                pf[k++] = formula[i];
            else if (formula[i] == ')') {
                while ( (out = pop(stack)) != '(')
                    pf[k++] = out;
            }
            else {
                while ( inStackPriority(out = pop(stack)) >= inComingPriority(formula[i]) )
                    pf[k++] = out;
                push(stack, out);
                push(stack, formula[i]);
            }
        }
    }
    while( (out = pop(stack)) != '#' )
        pf[k++] = out;
    pf[k] = '\0';
    
    return pf;
}

/**********************************************************/





/**********************************************************/
/****************** YOUR CODE STARTS HERE *****************/
/**********************************************************/

// expression tree formation from postfix formula string
BT *ETF ( char *pfForm , int start , int end )
{
    if ( start > end )	return NULL ;
    if ( start == end )
    {
    	return createNode( pfForm[start] ) ;
	}
	BT *et = ( BT* ) malloc ( sizeof(BT) ) ;
	char present = pfForm[end] ;
	et->element = present ;
	
	if ( present == '!' )
	{
		et->leftChild = NULL ;
		et->rightChild = ETF( pfForm , start , end-1 ) ;
		return et ;
	}
	
	if ( isProposition(present) )
	{
		et->leftChild = et->rightChild = NULL ;
		return et ;
	}
	
	int counter = 0 ;
	int i = end-1 ;
	while ( counter != -1 )
	{
		if ( isProposition(pfForm[i]) )
		{
			counter-- ; i-- ;
			continue ;
		}
		if ( pfForm[i] != '!' )
		{
			counter++ ; i-- ;
			continue ;
		}
		i-- ;
	}
    et->leftChild = ETF( pfForm , start , i ) ;
    et->rightChild = ETF( pfForm , i+1 , end-1 ) ;
    return et ;
}

int isBinaryOperator ( char c )
{
	if ( c == '|' ) return 1 ;
	if ( c == '&' ) return 1 ;
	if ( c == '-' ) return 1 ;
	if ( c == '~' ) return 1 ;
	return 0 ;
}

// storing the expresion tree in a string using inorder traversal
void ETP ( BT *et )
{
    if ( ! et ) return ;
    if ( isBinaryOperator(et->element) )	printf ( "( " ) ;
    ETP ( et->leftChild ) ;
    if ( et->element == '-' )	printf( "-> " ) ;
    else 
		if ( et->element == '~' )	printf( "<-> " ) ;
    	else	printf( "%c " , et->element ) ;
    ETP ( et->rightChild ) ;
    if ( isBinaryOperator(et->element) )	printf ( ") " ) ;
}

int findValue ( PV* pvarr , char c , int n )
{
	int i = 0 ;
	while ( i<n )
	{
		if ( pvarr[i].prop == c )	return pvarr[i].val ;
		i ++ ;
	}
	printf( "\n\n*** PROPOSITIONS WERE NOT CORRECTLY ENTERED ***\n\n" ) ;
	exit( 0 ) ;
}

// evaluate the formula from the expression tree from the proposition values provided in varr[] array
int EVAL (BT *et, PV *pvarr , int n )
{
	if ( isProposition(et->element) )
	{
		int value = findValue( pvarr , et->element , n ) ;
		return value ;
	}
    if ( et->element == '!' )
    {
    	int val = EVAL( et->rightChild , pvarr , n ) ;
    	if ( val )	return 0 ;
    	return 1 ;
	}
	if ( et->element == '|' )
    {
    	int u = EVAL( et->rightChild , pvarr , n ) ;
    	int v = EVAL( et->leftChild , pvarr , n ) ;
    	if ( u || v )	return 1 ;
    	return 0 ;
	}
	if ( et->element == '&' )
    {
    	int u = EVAL( et->rightChild , pvarr , n ) ;
    	int v = EVAL( et->leftChild , pvarr , n ) ;
    	if ( u && v )	return 1 ;
    	return 0 ;
	}
	if ( et->element == '-' )
    {
    	int u = EVAL( et->rightChild , pvarr , n ) ;
    	int v = EVAL( et->leftChild , pvarr , n ) ;
    	if ( !u && v )	return 0 ;
    	return 1 ;
	}
	if ( et->element == '~' )
    {
    	int u = EVAL( et->rightChild , pvarr , n ) ;
    	int v = EVAL( et->leftChild , pvarr , n ) ;
    	if ( !u && !v )	return 1 ;
    	if ( u && v )	return 1 ;
    	return 0 ;
	}
}

BT* negateIFF ( BT *et )
{
	if ( ! et )	return NULL ;
	if ( isProposition(et->element) )
	{
		BT* n = createNode('!') ;
		n->rightChild = et ;
		return n ;
	}
	if ( et->element == '!' )
		return et->rightChild ;
	if ( et->element == '&' )
	{
		et->leftChild = negateIFF( et->leftChild ) ;
		et->rightChild = negateIFF( et->rightChild ) ;
		et->element = '|' ;
		return et ;
	}
	if ( et->element == '|' )
	{
		et->leftChild = negateIFF( et->leftChild ) ;
		et->rightChild = negateIFF( et->rightChild ) ;
		et->element = '&' ;
		return et ;
	}
}

BT* addNegation ( BT* root )
{
	BT* n = createNode('!') ;
	n->rightChild = root ;
	return n ;
}

// convert expression tree to IFF expression tree
BT *IFF (BT *et)
{
	if ( ! et )	return NULL ;
    if ( et->element == '!' )
    {
    	et->rightChild = IFF(et->rightChild) ;
    	return et ;
	}
	if ( et->element == '|' || et->element == '&' )
    {
    	IFF(et->rightChild) ;
    	IFF(et->leftChild) ;
    	return et ;
	}
	if ( et->element == '-' )
    {
    	et->leftChild = addNegation( IFF(et->leftChild) ) ;
    	et->rightChild = IFF(et->rightChild) ;
    	et->element = '|' ;
    	return et ;
	}
	if ( et->element == '~' )
    {
    	BT* tempTree1 = createNode('-') ;
    	tempTree1->leftChild = duplicate( et->leftChild ) ;
    	tempTree1->rightChild = duplicate( et->rightChild ) ;
    	BT* tempTree2 = createNode('-') ;
    	tempTree2->leftChild = duplicate( et->rightChild ) ;
    	tempTree2->rightChild = duplicate( et->leftChild ) ;
    	free ( et->leftChild ) ; free ( et->rightChild ) ;
    	et->leftChild = IFF( tempTree1 ) ;
    	et->rightChild = IFF( tempTree2 ) ;
    	et->element = '&' ;
    	return et ;
	}
	return et ;
}

// convert IFF expression tree to NNF expression tree
BT *NNF (BT *etI)
{
	if ( ! etI )	return NULL ;
    if ( etI->element == '!' )
    {
    	char c = etI->rightChild->element ;
    	if ( c == '!' )
    		return NNF( etI->rightChild->rightChild ) ;
    	if ( c == '&' )
    	{
    		etI->rightChild->element = '|' ;
    		etI->rightChild->leftChild = negateIFF( NNF(etI->rightChild->leftChild) ) ;
    		etI->rightChild->rightChild = negateIFF( NNF(etI->rightChild->rightChild) ) ;
    		return etI->rightChild ;
		}
		if ( c == '|' )
    	{
    		etI->rightChild->element = '&' ;
    		etI->rightChild->leftChild = negateIFF( NNF(etI->rightChild->leftChild) ) ;
    		etI->rightChild->rightChild = negateIFF( NNF(etI->rightChild->rightChild) ) ;
    		return etI->rightChild ;
		}
		return etI ;
	}
	etI->leftChild = NNF( etI->leftChild ) ;
	etI->rightChild = NNF( etI->rightChild ) ;
	return etI ;
}

// convert NNF expression tree to CNF expression tree
BT *CNF (BT *etN)
{
    if ( ! etN )	return NULL ;
    if ( etN->element == '&' )
    {
    	etN->leftChild = CNF( etN->leftChild ) ;
    	etN->rightChild = CNF( etN->rightChild ) ;
    	return etN ;
	}
	if ( etN->element == '|' )
    {
    	etN->leftChild = CNF( etN->leftChild ) ;
    	etN->rightChild = CNF( etN->rightChild ) ;
    	if ( etN->leftChild->element == '&' )
    	{
    		BT* newTreeL = createNode('|') ;
    		newTreeL->leftChild = duplicate(etN->leftChild->leftChild) ;
    		newTreeL->rightChild = duplicate(etN->rightChild) ;
    		
    		BT* newTreeR = createNode('|') ;
    		newTreeR->leftChild = duplicate(etN->leftChild->rightChild) ;
    		newTreeR->rightChild = duplicate(etN->rightChild) ;
    		
    		free( etN->leftChild ) ; free( etN->rightChild ) ;
    		etN->leftChild = CNF( newTreeL ) ;
    		etN->rightChild = CNF( newTreeR ) ;
    		etN->element = '&' ;
    		return etN ;
		}
		if ( etN->rightChild->element == '&' )
    	{
    		BT* newTreeL = createNode('|') ;
    		newTreeL->rightChild = duplicate(etN->rightChild->leftChild) ;
    		newTreeL->leftChild = duplicate(etN->leftChild) ;
    		
    		BT* newTreeR = createNode('|') ;
    		newTreeR->rightChild = duplicate(etN->rightChild->rightChild) ;
    		newTreeR->leftChild = duplicate(etN->leftChild) ;
    		
    		free( etN->leftChild ) ; free( etN->rightChild ) ;
    		etN->leftChild = CNF( newTreeL ) ;
    		etN->rightChild = CNF( newTreeR ) ;
    		etN->element = '&' ;
    		return etN ;
		}
	}
	return etN ;
}

// convert NNF expression tree to DNF expression tree
BT *DNF (BT *etN)
{
    if ( ! etN )	return NULL ;
    if ( etN->element == '|' )
    {
    	etN->leftChild = DNF( etN->leftChild ) ;
    	etN->rightChild = DNF( etN->rightChild ) ;
    	return etN ;
	}
	if ( etN->element == '&' )
    {
    	etN->leftChild = DNF( etN->leftChild ) ;
		etN->rightChild = DNF( etN->rightChild ) ;
    	if ( etN->leftChild && etN->leftChild->element == '|' )
    	{
    		BT* newTreeL = createNode('&') ;
    		newTreeL->leftChild = duplicate(etN->leftChild->leftChild) ;
    		newTreeL->rightChild = duplicate(etN->rightChild) ;
    		
    		BT* newTreeR = createNode('&') ;
    		newTreeR->leftChild = duplicate(etN->leftChild->rightChild) ;
    		newTreeR->rightChild = duplicate(etN->rightChild) ;
    		
    		free( etN->leftChild ) ; free( etN->rightChild ) ;
    		etN->leftChild = DNF( newTreeL ) ;
    		etN->rightChild = DNF( newTreeR ) ;
    		etN->element = '|' ;
    		return etN ;
		}
		if ( etN->rightChild && etN->rightChild->element == '|' )
    	{
    		BT* newTreeL = createNode('&') ;
    		newTreeL->rightChild = duplicate(etN->rightChild->leftChild) ;
    		newTreeL->leftChild = duplicate(etN->leftChild) ;
    		
    		BT* newTreeR = createNode('&') ;
    		newTreeR->rightChild = duplicate(etN->rightChild->rightChild) ;
    		newTreeR->leftChild = duplicate(etN->leftChild) ;
    		
    		free( etN->leftChild ) ; free( etN->rightChild ) ;
    		etN->leftChild = DNF( newTreeL ) ;
    		etN->rightChild = DNF( newTreeR ) ;
    		etN->element = '|' ;
    		return etN ;
		}
	}
	return etN ;
}

void exhaustiveSearch ( BT* et , PV* p , int s , int n , int* valid , int* sat )
{
	if ( s == n )
	{
		printf(" {") ;
		for ( int i=0 ; i<n ; i++ )
			printf( " (%c = %d)" , p[i].prop , p[i].val ) ;
		int result = EVAL( et , p , n ) ;
		if ( result )	*sat = 1 ;
		else	*valid = 0 ;
		printf(" } : %d\n" , result ) ;
		return ;
	}
	p[s].val = 0 ;
	exhaustiveSearch( et , p , s+1 , n , valid , sat ) ;
	p[s].val = 1 ;
	exhaustiveSearch( et , p , s+1 , n , valid , sat ) ;
}

// exhaustive search for checking validity / satisfiability
void CHECK (BT *et)
{
    int valid = 1, sat = 0;
    int n ;
    printf( "\nEnter Number of Propositions: " ) ;
	scanf( "%d" , &n ) ;
	PV p[n] ;
	printf( "Enter Proposition Names (<SPACE> Separated): " ) ;
	for ( int i=0 ; i<n ; i++ )
		scanf( " %c" , &(p[i].prop) ) ;
	printf( "Evaluations of the Formula: \n" ) ;
	exhaustiveSearch( et , p , 0 , n , &valid , &sat ) ;
    printResult(valid,sat);
}

/**********************************************************/
/******************* YOUR CODE ENDS HERE ******************/
/**********************************************************/





// main routine
int main ()
{
    char formula[10000], *pfForm;
    int len, i;
    
    BT *et, *etI, *etN, *etDup, *etC, *etD, *duplicateOriginal ;
    int *varr;
    PV *pvarr;
    int result;
    
    // scan propositional formula from user input
    printf("\nEnter Propositional Logic Formula: ");
    scanf( "%[^\n]s " , formula );
     
    // internal formula string with operators as, AND (&), OR (|), NOT (!), IMPLY (-) and IFF (~)
    len = strlen(formula);
    for(i = 0; i < len; i++){
    	if(formula[i] == '<'){ // denoting iff operator (<->) using ~
            formula[i] = ' ';
            formula[i+1] = '~';
        }
        if(formula[i] == '>'){ // denoting imply operator (->) using -
            formula[i] = ' ';
        }
    }

    // postfix form generation from represented formula string
    pfForm = genPostFixFormula(formula);
    
    // display postfix form of the internally represented formula
    displayPfForm(pfForm);
    
    // internal postfix formula string with operators as, AND (&), OR (|), NOT (!), IMPLY (-) and IFF (~)
    printf("\n++++ PostFix Format of the Propositional Formula ++++\n('-' used for '->' and '~' used for '<->')\n");
    printf("YOUR INPUT STRING: %s\n", pfForm);
    
    
    
    /**********************************************************/
    /********** YOUR CODE ENABLES THE FOLLOWING PARTS *********/
    /**********************************************************/
    
    printf("\n++++ Expression Tree Generation ++++");
    et = ETF(pfForm, 0, strlen(pfForm)-1);
    printf("\nOriginal Formula (from Expression Tree): ");
    ETP(et);
    printf("\n");
    duplicateOriginal = duplicate( et ) ;
    
    printf("\n++++ Expression Tree Evaluation ++++\n");
    unsigned int N = 0 ;
    pvarr = scanPropValueInput(&N) ;
    result = EVAL(et, pvarr, N);
    printf("\nThe Formula is Evaluated as: ");
    (result) ? printf("1\n") : printf("False\n");
    
    printf("\n++++ IFF Expression Tree Conversion ++++");
    etI = IFF(et);
    printf("\nFormula in Implication Free Form (IFF from Expression Tree):\n");
    ETP(etI);
    printf("\n");
    
    printf("\n++++ NNF Expression Tree Conversion ++++");
    etN = NNF(etI);
    printf("\nFormula in Negation Normal Form (NNF from Expression Tree):\n");
    ETP(etN);
    printf("\n");
    
    etDup = duplicate(etN); // keeping a duplicate copy for DNF conversion
    
    printf("\n++++ CNF Expression Tree Conversion ++++");
    etC = CNF(etN);
    printf("\nFormula in Conjunctive Normal Form (CNF from Expression Tree):\n");
    ETP(etC);
    printf("\n");
    
    printf("\n++++ DNF Expression Tree Conversion ++++");
    etD = DNF(etDup);
    printf("\nFormula in Disjunctive Normal Form (DNF from Expression Tree):\n");
    ETP(etD);
    printf("\n");
    
    printf("\n++++ Exhaustive Search from Expression Tree for Validity / Satisfiability Checking ++++");
    CHECK(duplicateOriginal);
    
    /**********************************************************/
    
    
    
    return 0;
}
