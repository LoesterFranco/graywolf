/* ----------------------------------------------------------------- 
FILE:	    rand.c                                       
DESCRIPTION:mimimum standard random number generator function.  This
	    random generator replaces the poor Berkeley 4.2 random
	    generator using generators discussed in the Communications
	    of the ACM.  See articles by L'Ecuyer and Park/Miller in
	    June 1988 and October 1988 resp.
CONTENTS:   
	    INT acm_random()
	    set_random_seed(int)
DATE:	    Oct 27, 1988 
REVISIONS:  Mar 21, 1989 - added get current value of random variable.
		Now we can restart TimberWolf with same seed.
	    Tue Apr  7 09:37:53 EDT 1992 - now you don't need to initialize
		random number generator if you don't care.
----------------------------------------------------------------- */
#ifndef lint
static char SccsId[] = "@(#) rand.c version 3.8 4/7/92" ;
#endif

#include <yalecad/base.h>
#include <yalecad/debug.h>

static INT randVarS = 1 ;                 /* random number */

#define A_RAND 16807                /* good generator multiplier */
#define M_RAND 2147483647                 /* 2 ** 31 - 1 */
#define Q_RAND 127773                     /* m / a */
#define R_RAND 2836                       /* m mod a */

/* returns a random number in [0..2**31 - 1] */
INT Yacm_random() 
{
    register INT k_rand ;

    k_rand = randVarS / Q_RAND ;
    randVarS = A_RAND * (randVarS - k_rand * Q_RAND) - (k_rand * R_RAND) ;
    if( randVarS < 0 ){
	randVarS += M_RAND ;
    } 
    return( randVarS ) ;

} /* end acm_random */

Yset_random_seed( seed )
INT seed ;
{
    seed = ABS(seed) ;
    if( seed == 0 ){
	seed++ ;
    }
    randVarS = seed ;
} /* end set_random_seed */

INT Yget_random_var()
{
    return( randVarS ) ;
} /* end get_random_var */


#ifdef TEST

/* test whether generator works correctly. */

main()
{
    INT n, randnum ;
    Yset_random_seed( 1 ) ;
    for( n = 1; n <= 10000; n++ ){
	randnum = Yacm_random() ;
    }
    printf( "The final value is randnum:%d\n", randnum ) ;
    printf( "It should be 1043618065 if everything is correct.\n" ) ;
    printf( "See article.\n\n" ) ;
}

#endif /* TEST */
    
