#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "options.h"
#include "fqreader.h"
#include "kmer.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)              ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)                 ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

#define  BASESTATES              7
#define  QUALSTATES              128

static unsigned *basecounts = NULL;
static unsigned *qualcounts = NULL;
static unsigned maxpos = 0;
static unsigned nseqs = 0;

static int
_resize( unsigned len )
{
   unsigned    i, j;

   basecounts = realloc( basecounts, BASESTATES * len * sizeof ( unsigned ) );
   qualcounts = realloc( qualcounts, QUALSTATES * len * sizeof ( unsigned ) );

   for ( i = maxpos; i < len; i++ ) {

      for ( j = 0; j < BASESTATES; j++ )
         basecounts[BASESTATES * i + j] = 0;

      for ( j = 0; j < QUALSTATES; j++ )
         qualcounts[QUALSTATES * i + j] = 0;
   }

   maxpos = len;

   return 0;
}

static void
_update_kmer_stats( char *x, unsigned k )
{
   unsigned    i;
   unsigned    len = strlen( x );
   unsigned    hash;

   for ( i = 0; i < len - k; i++ ) {

      if ( kmer_hash( k, &( x[i] ), &hash ) )
         continue;


   }
}

static void
_update_header_stats( char *x )
{
   unsigned    i;
   unsigned    len = strlen( x );
   unsigned    skip = 0;
}

static void
_update_sequence_stats( char *x )
{
   unsigned    i, j;
   unsigned    len = strlen( x );

   if ( maxpos < len )
      _resize( len );

   for ( i = 0; i < len; i++ ) {
      switch ( x[i] ) {
         case 'A':
         case 'a':
            j = BASESTATES * i;
            break;
         case 'C':
         case 'c':
            j = BASESTATES * i + 1;
            break;
         case 'G':
         case 'g':
            j = BASESTATES * i + 2;
            break;
         case 'T':
         case 't':
            j = BASESTATES * i + 3;
            break;
         case 'U':
         case 'u':
            j = BASESTATES * i + 4;
            break;
         case 'N':
         case 'n':
            j = BASESTATES * i + 5;
            break;
         default:
            j = BASESTATES * i + 6;
            break;
      }

      basecounts[j] += 1;
   }
}

static void
_update_quality_stats( char *x )
{
   unsigned    i, j;
   unsigned    len = strlen( x );

   if ( maxpos < len )
      _resize( len );

   for ( i = 0; i < len; i++ )
      qualcounts[QUALSTATES * i + x[i]] += 1;
}

/*** main() ***/

int
main( int argc, char *argv[] )
{
   unsigned    i, j, k = 10;
   char       *h1, *h2, *s, *q;
   struct options *o = options_new(  );
   struct fqreader *z;

   /* Get the command line options */
   options_cmdline( o, argc, argv );

   if ( o->optind == argc )
      z = fqreader_new( NULL );

   else
      z = fqreader_new( argv[o->optind] );

   if ( _IS_NULL( z ) ) {
      fprintf( stderr, "[ERROR] %s: Cannot open input stream\n", _I_AM );
      exit( 1 );
   }

   while ( fqreader_next( z, &h1, &h2, &s, &q ) ) {
      nseqs += 1;
      _update_header_stats( h1 );
      _update_sequence_stats( s );
      /* _update_kmer_stats( s, k ); */
      _update_quality_stats( q );
   }

   printf( "nseqs\t%d\n", nseqs );
   printf( "maxpos\t%d\n", maxpos );

   printf( "a_counts" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i] );
   printf( "\n" );

   printf( "c_counts" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 1] );
   printf( "\n" );

   printf( "g_counts" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 2] );
   printf( "\n" );

   printf( "t_counts" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 3] );
   printf( "\n" );

   printf( "u_counts" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 4] );
   printf( "\n" );

   printf( "n_counts" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 5] );
   printf( "\n" );

   printf( "other_counts" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 6] );
   printf( "\n" );



   _FREE( basecounts );
   fqreader_free( z );
   options_free( o );

   return 0;
}

#undef _IS_NULL
#undef _FREE
