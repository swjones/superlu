
/*  -- translated by f2c (version 19940927).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/
#include <string.h>
#include "f2c.h"

/* Subroutine */ void strsv_(char *uplo, char *trans, char *diag, integer *n, 
	real *a, integer *lda, real *x, integer *incx)
{


    /* System generated locals */

    /* Local variables */
    integer info;
    real temp;
    integer i, j;
    integer ix, jx, kx;
    logical nounit;

    extern int input_error(char *, int *);

/*  Purpose   
    =======   

    STRSV  solves one of the systems of equations   

       A*x = b,   or   A'*x = b,   

    where b and x are n element vectors and A is an n by n unit, or   
    non-unit, upper or lower triangular matrix.   

    No test for singularity or near-singularity is included in this   
    routine. Such tests must be performed before calling this routine.   

    Parameters   
    ==========   

    UPLO   - CHARACTER*1.   
             On entry, UPLO specifies whether the matrix is an upper or   
             lower triangular matrix as follows:   

                UPLO = 'U' or 'u'   A is an upper triangular matrix.   

                UPLO = 'L' or 'l'   A is a lower triangular matrix.   

             Unchanged on exit.   

    TRANS  - CHARACTER*1.   
             On entry, TRANS specifies the equations to be solved as   
             follows:   

                TRANS = 'N' or 'n'   A*x = b.   

                TRANS = 'T' or 't'   A'*x = b.   

                TRANS = 'C' or 'c'   A'*x = b.   

             Unchanged on exit.   

    DIAG   - CHARACTER*1.   
             On entry, DIAG specifies whether or not A is unit   
             triangular as follows:   

                DIAG = 'U' or 'u'   A is assumed to be unit triangular.   

                DIAG = 'N' or 'n'   A is not assumed to be unit   
                                    triangular.   

             Unchanged on exit.   

    N      - INTEGER.   
             On entry, N specifies the order of the matrix A.   
             N must be at least zero.   
             Unchanged on exit.   

    A      - REAL             array of DIMENSION ( LDA, n ).   
             Before entry with  UPLO = 'U' or 'u', the leading n by n   
             upper triangular part of the array A must contain the upper 
  
             triangular matrix and the strictly lower triangular part of 
  
             A is not referenced.   
             Before entry with UPLO = 'L' or 'l', the leading n by n   
             lower triangular part of the array A must contain the lower 
  
             triangular matrix and the strictly upper triangular part of 
  
             A is not referenced.   
             Note that when  DIAG = 'U' or 'u', the diagonal elements of 
  
             A are not referenced either, but are assumed to be unity.   
             Unchanged on exit.   

    LDA    - INTEGER.   
             On entry, LDA specifies the first dimension of A as declared 
  
             in the calling (sub) program. LDA must be at least   
             max( 1, n ).   
             Unchanged on exit.   

    X      - REAL             array of dimension at least   
             ( 1 + ( n - 1 )*abs( INCX ) ).   
             Before entry, the incremented array X must contain the n   
             element right-hand side vector b. On exit, X is overwritten 
  
             with the solution vector x.   

    INCX   - INTEGER.   
             On entry, INCX specifies the increment for the elements of   
             X. INCX must not be zero.   
             Unchanged on exit.   


    Level 2 Blas routine.   

    -- Written on 22-October-1986.   
       Jack Dongarra, Argonne National Lab.   
       Jeremy Du Croz, Nag Central Office.   
       Sven Hammarling, Nag Central Office.   
       Richard Hanson, Sandia National Labs.   

       Test the input parameters.   
    
   Parameter adjustments   
       Function Body */
#define X(I) x[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    info = 0;
    if ( strncmp(uplo, "U", 1)!=0 && strncmp(uplo, "L", 1)!=0 ) {
	info = 1;
    } else if ( strncmp(trans, "N", 1)!=0 && strncmp(trans, "T", 1)!=0 &&
		strncmp(trans, "C", 1)!=0 ) {
	info = 2;
    } else if ( strncmp(diag, "U", 1)!=0 && strncmp(diag, "N", 1)!=0 ) {
	info = 3;
    } else if (*n < 0) {
	info = 4;
    } else if (*lda < max(1,*n)) {
	info = 6;
    } else if (*incx == 0) {
	info = 8;
    }
    if (info != 0) {
	input_error("STRSV ", &info);
	return;
    }

/*     Quick return if possible. */

    if (*n == 0) {
	return;
    }

    nounit = (strncmp(diag, "N", 1)==0);

/*     Set up the start point in X if the increment is not unity. This   
       will be  ( N - 1 )*INCX  too small for descending loops. */

    if (*incx <= 0) {
	kx = 1 - (*n - 1) * *incx;
    } else if (*incx != 1) {
	kx = 1;
    }

/*     Start the operations. In this version the elements of A are   
       accessed sequentially with one pass through A. */

    if (strncmp(trans, "N", 1)==0) {

/*        Form  x := inv( A )*x. */

	if (strncmp(uplo, "U", 1)==0) {
	    if (*incx == 1) {
		for (j = *n; j >= 1; --j) {
		    if (X(j) != 0.f) {
			if (nounit) {
			    X(j) /= A(j,j);
			}
			temp = X(j);
			for (i = j - 1; i >= 1; --i) {
			    X(i) -= temp * A(i,j);
/* L10: */
			}
		    }
/* L20: */
		}
	    } else {
		jx = kx + (*n - 1) * *incx;
		for (j = *n; j >= 1; --j) {
		    if (X(jx) != 0.f) {
			if (nounit) {
			    X(jx) /= A(j,j);
			}
			temp = X(jx);
			ix = jx;
			for (i = j - 1; i >= 1; --i) {
			    ix -= *incx;
			    X(ix) -= temp * A(i,j);
/* L30: */
			}
		    }
		    jx -= *incx;
/* L40: */
		}
	    }
	} else {
	    if (*incx == 1) {
		for (j = 1; j <= *n; ++j) {
		    if (X(j) != 0.f) {
			if (nounit) {
			    X(j) /= A(j,j);
			}
			temp = X(j);
			for (i = j + 1; i <= *n; ++i) {
			    X(i) -= temp * A(i,j);
/* L50: */
			}
		    }
/* L60: */
		}
	    } else {
		jx = kx;
		for (j = 1; j <= *n; ++j) {
		    if (X(jx) != 0.f) {
			if (nounit) {
			    X(jx) /= A(j,j);
			}
			temp = X(jx);
			ix = jx;
			for (i = j + 1; i <= *n; ++i) {
			    ix += *incx;
			    X(ix) -= temp * A(i,j);
/* L70: */
			}
		    }
		    jx += *incx;
/* L80: */
		}
	    }
	}
    } else {

/*        Form  x := inv( A' )*x. */

	if (strncmp(uplo, "U", 1)==0) {
	    if (*incx == 1) {
		for (j = 1; j <= *n; ++j) {
		    temp = X(j);
		    for (i = 1; i <= j-1; ++i) {
			temp -= A(i,j) * X(i);
/* L90: */
		    }
		    if (nounit) {
			temp /= A(j,j);
		    }
		    X(j) = temp;
/* L100: */
		}
	    } else {
		jx = kx;
		for (j = 1; j <= *n; ++j) {
		    temp = X(jx);
		    ix = kx;
		    for (i = 1; i <= j-1; ++i) {
			temp -= A(i,j) * X(ix);
			ix += *incx;
/* L110: */
		    }
		    if (nounit) {
			temp /= A(j,j);
		    }
		    X(jx) = temp;
		    jx += *incx;
/* L120: */
		}
	    }
	} else {
	    if (*incx == 1) {
		for (j = *n; j >= 1; --j) {
		    temp = X(j);
		    for (i = *n; i >= j+1; --i) {
			temp -= A(i,j) * X(i);
/* L130: */
		    }
		    if (nounit) {
			temp /= A(j,j);
		    }
		    X(j) = temp;
/* L140: */
		}
	    } else {
		kx += (*n - 1) * *incx;
		jx = kx;
		for (j = *n; j >= 1; --j) {
		    temp = X(jx);
		    ix = kx;
		    for (i = *n; i >= j+1; --i) {
			temp -= A(i,j) * X(ix);
			ix -= *incx;
/* L150: */
		    }
		    if (nounit) {
			temp /= A(j,j);
		    }
		    X(jx) = temp;
		    jx -= *incx;
/* L160: */
		}
	    }
	}
    }

    return;

/*     End of STRSV . */

} /* strsv_ */

