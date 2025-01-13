#ifndef DOXYGEN_SHOULD_SKIP_THIS

/* lrslong.h      (lrs long integer arithmetic library              */
/* Copyright: David Avis 2000, avis@cs.mcgill.ca                    */
/* Version 4.0, February 17, 2000                                   */

/* This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */
/******************************************************************************/
/*  See http://cgm.cs.mcgill.ca/~avis/C/lrs.html for lrs usage instructions   */
/******************************************************************************/
/* This package contains the extended precision routines used by lrs
   and some other miscellaneous routines. The maximum precision depends on
   the parameter MAX_DIGITS defined below, with usual default of 255L. This
   gives a maximum of 1020 decimal digits on 32 bit machines. The procedure
   lrs_mp_init(dec_digits) may set a smaller number of dec_digits, and this
   is useful if arrays or matrices will be used.
 */


#ifdef PLRS
#include <string>
using namespace std;
#endif


/***********/
/* defines */
/***********/
/*
   this is number of longwords. Increasing this won't cost you that much
   since only variables other than the A matrix are allocated this size.
   Changing affects running time in small but not very predictable ways.
 */

#define MAX_DIGITS 255L

/*
   this is in decimal digits, you pay in memory if you increase this,
   unless you override by a line with
   digits n
   before the begin line of your file.
 */
#define DEFAULT_DIGITS 100L


// 64 bits for windows (long is 32 bits)
#ifdef _MSC_VER
typedef  __int64          int64_t;
typedef unsigned  __int64 uint64_t;
#else
#include <stdint.h>
#endif

/**********MACHINE DEPENDENT CONSTANTS***********/
/* MAXD is 2^(k-1)-1 where k=16,32,64 word size */
/* MAXD must be at least 2*BASE^2               */
/* If BASE is 10^k, use "%k.ku" for FORMAT      */
/* INTSIZE is number of bytes for integer       */
/* 32/64 bit machines                           */
/***********************************************/
#ifdef B32
/*32 bit machines */
#define FORMAT "%4.4u"
#define MAXD 2147483647L
#define BASE 10000L
#define BASE_DIG 4
#define INTSIZE 8L
#define BIT "32bit"
#else
/* 64 bit machines */
#define MAXD 9223372036854775807L
#define BASE 1000000000L
#define FORMAT "%9.9u"
#define BASE_DIG 9
#define INTSIZE 16L
#define BIT "64bit"
#endif

#define MAXINPUT 1000 /*max length of any input rational */

#define POS 1L
#define NEG -1L
#ifndef TRUE
#define TRUE 1L
#endif
#ifndef FALSE
#define FALSE 0L
#endif
#define ONE 1L
#define TWO 2L
#define ZERO 0L

/**********************************/
/*         MACROS                 */
/* dependent on mp implementation */
/**********************************/

#define addint(a, b, c) *(c) = *(a) + *(b)
#define changesign(a) (*(a) = -*(a))
#define copy(a, b) ((a)[0] = (b)[0])
#define decint(a, b) *(a) = *(a) - *(b)
#define divint(a, b, c) \
  *(c) = *(a) / *(b);   \
  *(a) = *(a) % *(b)
#define exactdivint(a, b, c) *(c) = *(a) / *(b);
#define mp_greater(a, b) (*(a) > *(b))
#define itomp(in, a) *(a) = in
#define linint(a, ka, b, kb) *(a) = *(a)*ka + *(b)*kb
#define mulint(a, b, c) *(c) = *(a) * *(b)
#define one(a) (*(a) == 1)
#define negative(a) (*(a) < 0)
#define normalize(a) ()0
#define positive(a) (*(a) > 0)
#define sign(a) (*(a) < 0 ? NEG : POS)
#define storesign(a, sa) (*(a) = labs(*(a)) * sa)
#define subint(a, b, c) *(c) = *(a) - *(b)
#define iszero(a) (*(a) == 0)


/*
 *  convert between decimal and machine (longword digits). Notice lovely
 *  implementation of ceiling function :-)
 */
#define DEC2DIG(d) ((d) % BASE_DIG ? (d) / BASE_DIG + 1 : (d) / BASE_DIG)
#define DIG2DEC(d) ((d)*BASE_DIG)

#ifndef OMIT_SIGNALS
#include <signal.h>
#include <stdlib.h> /* labs */
#include <unistd.h>
#define errcheck(s, e)       \
  if ((int64_t)(e) == -1L) { \
    perror(s);               \
    exit(1);                 \
  }
#endif

#define CALLOC(n, s) xcalloc(n, s,   __LINE__,   __FILE__)

/*************/
/* typedefs  */
/*************/

typedef int64_t    lrs_mp[1]; /* type lrs_mp holds one long integer */
typedef int64_t*   lrs_mp_t;
typedef int64_t**  lrs_mp_vector;
typedef int64_t*** lrs_mp_matrix;

/*********************/
/*global variables   */
/*********************/

extern int64_t lrs_digits;        /* max permitted no. of digits   */
extern int64_t lrs_record_digits; /* this is the biggest acheived so far.     */

extern FILE* lrs_ifp; /* input file pointer       */
extern FILE* lrs_ofp; /* output file pointer      */

/*********************************************************/
/* Initialization and allocation procedures - must use!  */
/******************************************************* */

int64_t lrs_mp_init(int64_t dec_digits,
                    FILE*   lrs_ifp,
                    FILE*   lrs_ofp); /* max number of decimal digits, fps   */

#define lrs_alloc_mp(a)
#define lrs_clear_mp(a)

lrs_mp_t lrs_alloc_mp_t(); /* dynamic allocation of lrs_mp                  */
lrs_mp_vector
lrs_alloc_mp_vector(int64_t n); /* allocate lrs_mp_vector for n+1 lrs_mp numbers */
lrs_mp_matrix
lrs_alloc_mp_matrix(int64_t m,
                    int64_t n); /* allocate lrs_mp_matrix for m+1 x n+1 lrs_mp */

void lrs_clear_mp_vector(lrs_mp_vector a, int64_t n);
void lrs_clear_mp_matrix(lrs_mp_matrix a, int64_t m, int64_t n);


/*********************************************************/
/* Core library functions - depend on mp implementation  */
/******************************************************* */
void atomp(const char s[], lrs_mp a); /* convert string to lrs_mp integer */
int64_t compare(lrs_mp a, lrs_mp b);  /* a ? b and returns -1,0,1 for <,=,> */
void gcd(lrs_mp u, lrs_mp v);         /* returns u=gcd(u,v) destroying v */
void mptodouble(lrs_mp a, double* x); /* convert lrs_mp to double */
int64_t mptoi(lrs_mp a);              /* convert lrs_mp to long integer */
#ifdef PLRS
string pmp(char name[], lrs_mp a); /* print the long precision integer a */
string prat(char name[], lrs_mp Nt, lrs_mp Dt); /* reduce and print  Nt/Dt */
char* cprat(char name[], lrs_mp Nt, lrs_mp Dt); /* C version of prat */
int64_t
plrs_readrat(lrs_mp      Na,
             lrs_mp      Da,
             const char* rat); /* take a rational number and convert to lrs_mp */
#else
void pmp(char name[], lrs_mp a); /* print the long precision integer a */
void prat(char name[], lrs_mp Nt, lrs_mp Dt); /* reduce and print  Nt/Dt */
#endif
void readmp(lrs_mp a); /* read an integer and convert to lrs_mp          */
int64_t readrat(lrs_mp Na,
                lrs_mp Da); /* read a rational or int and convert to lrs_mp */
void reduce(lrs_mp Na, lrs_mp Da); /* reduces Na Da by gcd(Na,Da) */

/*********************************************************/
/* Standard arithmetic & misc. functions                 */
/* should be independent of mp implementation            */
/******************************************************* */

void atoaa(const char in[],
           char       num[],
           char       den[]); /* convert rational string in to num/den strings  */
int64_t atos(char s[]);       /* convert s to integer                           */
int64_t comprod(lrs_mp Na,
                lrs_mp Nb,
                lrs_mp Nc,
                lrs_mp Nd); /* +1 if Na*Nb > Nc*Nd,-1 if Na*Nb > Nc*Nd else 0 */
void divrat(lrs_mp Na, lrs_mp Da, lrs_mp Nb, lrs_mp Db, lrs_mp Nc, lrs_mp Dc);
/* computes Nc/Dc = (Na/Da) /( Nb/Db ) and reduce */
void getfactorial(lrs_mp factorial, int64_t k); /* compute k factorial in lrs_mp */
void linrat(lrs_mp  Na,
            lrs_mp  Da,
            int64_t ka,
            lrs_mp  Nb,
            lrs_mp  Db,
            int64_t kb,
            lrs_mp  Nc,
            lrs_mp  Dc);
void lcm(lrs_mp a, lrs_mp b); /* a = least common multiple of a, b; b is saved */
void mulrat(lrs_mp Na, lrs_mp Da, lrs_mp Nb, lrs_mp Db, lrs_mp Nc, lrs_mp Dc);
/* computes Nc/Dc=(Na/Da)*(Nb/Db) and reduce      */
int64_t myrandom(int64_t num,
                 int64_t nrange); /* return a random number in range 0..nrange-1 */
void notimpl(char s[]); /* bail out - help!                               */
void rattodouble(lrs_mp  a,
                 lrs_mp  b,
                 double* x);          /* convert lrs_mp rational to double */
void reduceint(lrs_mp Na, lrs_mp Da); /* divide Na by Da and return it */
void reducearray(lrs_mp_vector p,
                 int64_t n); /* find gcd of p[0]..p[n-1] and divide through by */
void scalerat(lrs_mp Na, lrs_mp Da, int64_t ka); /* scales rational by ka */

/**********************************/
/* Miscellaneous functions        */
/******************************** */

void lrs_getdigits(int64_t* a, int64_t* b); /* send digit information to user */

void stringcpy(char* s, char* t); /* copy t to s pointer version */

void* calloc();
void* malloc();
void* xcalloc(int64_t n, int64_t s, int64_t l, char* f);

void lrs_default_digits_overflow();

/* end of  lrs_mp.h (vertex enumeration using lexicographic reverse search) */

#endif  // DOXYGEN_SHOULD_SKIP_THIS
