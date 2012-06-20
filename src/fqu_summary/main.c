#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "options.h"
#include "fgetopt.h"
#include "fqreader.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)              ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)                 ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

static unsigned nseqs;
static unsigned na;
static unsigned nc;
static unsigned ng;
static unsigned nt;                         /* includes t and u */
static unsigned nn;
static unsigned no;

/* add simple kmer count */

static void _update_header_stats( char *x )
{
   /* stub */
}

static void _update_sequence_stats( char *x )
{
}

static void _update_quality_stats( char *x )
{
}

/*** main() ***/

int main( int argc, char *argv[] )
{
   char       *h1, *h2, *s, *q;
   struct options *o = options_new(  );
   struct fqreader *z;

   /* Get the command line options */
   options_cmdline( o, argc, argv );

   z = fqreader_new( o->fname );

   nseqs = 0;
   na = 0;
   nc = 0;
   ng = 0;
   nt = 0;
   nn = 0;
   no = 0;

   while ( fqreader_next( z, &h1, &h2, &s, &q ) ) {
      nseqs += 1;
      _update_header_stats( h1 );
      _update_sequence_stats( s );
      _update_quality_stats( q );
   }

   printf( "nseqs: %d\n", nseqs );

   fqreader_free( z );
   options_free( o );

   return 0;
}

#undef _IS_NULL
#undef _FREE
