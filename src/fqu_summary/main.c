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
#define  GCTAB_SIZE              20
#define  QUALQUANTS              3               /* 3 for quartiles */

static unsigned *basecounts = NULL;
static unsigned *qualcounts = NULL;
static double *qualquants = NULL;
static unsigned maxpos = 0;
static unsigned nseqs = 0;
static unsigned gctab[GCTAB_SIZE];

static int _resize( unsigned len )
{
   unsigned    i, j;

   basecounts = realloc( basecounts, BASESTATES * len * sizeof ( unsigned ) );
   qualcounts = realloc( qualcounts, QUALSTATES * len * sizeof ( unsigned ) );
   qualquants = realloc( qualquants, QUALQUANTS * len * sizeof ( unsigned ) );

   for ( i = maxpos; i < len; i++ ) {

      for ( j = 0; j < BASESTATES; j++ )
         basecounts[BASESTATES * i + j] = 0;

      for ( j = 0; j < QUALSTATES; j++ )
         qualcounts[QUALSTATES * i + j] = 0;

      for ( j = 0; j < QUALQUANTS; j++ )
         qualquants[QUALQUANTS * i + j] = 0;
   }

   maxpos = len;

   return 0;
}

static void _update_kmer_stats( char *x, unsigned k )
{
   unsigned    i;
   unsigned    len = strlen( x );
   unsigned    hash;

   for ( i = 0; i < len - k; i++ ) {

      if ( kmer_hash( k, &( x[i] ), &hash ) )
         continue;
   }
}

static void _update_header_stats( char *x )
{
   unsigned    i;
   unsigned    len = strlen( x );
   unsigned    skip = 0;
}

static void _update_sequence_stats( char *x )
{
   unsigned    i, j;
   unsigned    len = strlen( x );
   unsigned    at = 0, gc = 0;

   if ( maxpos < len )
      _resize( len );

   for ( i = 0; i < len; i++ ) {
      switch ( x[i] ) {
         case 'A':
         case 'a':
            j = BASESTATES * i;
            at += 1;
            break;
         case 'C':
         case 'c':
            j = BASESTATES * i + 1;
            gc += 1;
            break;
         case 'G':
         case 'g':
            j = BASESTATES * i + 2;
            gc += 1;
            break;
         case 'T':
         case 't':
            j = BASESTATES * i + 3;
            at += 1;
            break;
         case 'U':
         case 'u':
            j = BASESTATES * i + 4;
            at += 1;
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

      if ( gc + at > 0 ) {
         unsigned    k = GCTAB_SIZE * gc / ( double ) ( gc + at );

         k = ( k > GCTAB_SIZE - 1 ? GCTAB_SIZE - 1 : k );       /* special case of 100 percent gc */
         gctab[k] += 1;
      }
   }
}

static void _update_quality_stats( char *x )
{
   unsigned    i, j;
   unsigned    len = strlen( x );

   if ( maxpos < len )
      _resize( len );

   for ( i = 0; i < len; i++ )
      qualcounts[QUALSTATES * i + x[i]] += 1;
}


static void _update_quality_quantiles( void )
{
   unsigned    i, j, k;

   for ( i = 0; i < maxpos; i++ ) {
      unsigned    total;
      unsigned    sum0, sum1;

      /* Compute the total quality counts for this position */
      for ( j = 0, total = 0; j < QUALSTATES; j++ )
         total += qualcounts[QUALSTATES * i + j];

      /* Now compute the quantiles */
      for ( j = 0, k = 0, sum1 = 0; j < QUALSTATES; j++ ) {
         double      target = total * ( k + 1 ) / ( double ) ( QUALQUANTS + 1 );        /* target */

         sum0 = sum1;
         sum1 += qualcounts[QUALSTATES * i + j];
         if ( sum1 > target ) {
            /* sum0 and sum1 straddle the target x */
#if 0
            qualquants[QUALQUANTS * i + k] = j - 1 + ( target - sum0 ) / ( sum1 - sum0 );
#else
            qualquants[QUALQUANTS * i + k] = j;
#endif
            k += 1;
         }
         /* FIXME maybe break when we hit the final one ? */
      }
   }
}

int _guess_qoffset( void )
{
   unsigned    i, j;
   unsigned    count_all = 0;
   unsigned    count_58 = 0;                /* count of qs 0 <= q <= 58 */
   unsigned    offset = 33;                 /* default */

   for ( i = 0; i < maxpos; i++ )
      for ( j = 0; j < QUALSTATES; j++ ) {
         count_all = qualcounts[QUALSTATES * i + j];
         if ( j < 59 )
            count_58 = qualcounts[QUALSTATES * i + j];
      }

   /* Might do something more sophisticated here */

   if ( count_all > 0 && count_58 == 0 )
      offset = 64;

   return offset;
}

/*** main() ***/

int main( int argc, char *argv[] )
{
   unsigned    i, j, k = 10;
   char       *h1, *h2, *s, *q;
   int         qoffset;
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

   printf( "seqcount\t%d\n", nseqs );
   printf( "maxpos\t%d\n", maxpos );

   /* See if we can determine the quality offset */
   qoffset = _guess_qoffset(  );

   printf( "qualities_offset\t%d\n", qoffset );

   /* Basecounts, per positions */
   printf( "basecounts_a" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i] );
   printf( "\n" );

   printf( "basecounts_c" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 1] );
   printf( "\n" );

   printf( "basecounts_g" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 2] );
   printf( "\n" );

   printf( "basecounts_t" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 3] );
   printf( "\n" );

   printf( "basecounts_u" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 4] );
   printf( "\n" );

   printf( "basecounts_n" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 5] );
   printf( "\n" );

   printf( "basecounts_other" );
   for ( i = 0; i < maxpos; i++ )
      printf( "\t%d", basecounts[BASESTATES * i + 6] );
   printf( "\n" );

   /* Per read GC content histogram */
   printf( "histogram_gc_per_read" );
   for ( i = 0; i < GCTAB_SIZE; i++ )
      printf( "\t%d", gctab[i] );
   printf( "\n" );

   /* Quality quantiles, per position */
   _update_quality_quantiles(  );

   for ( j = 0; j < QUALQUANTS; j++ ) {
      printf( "qualquants_%d", j + 1);
      for ( i = 0; i < maxpos; i++ )
         printf( "\t%0.1e", qualquants[QUALQUANTS * i + j] - qoffset );
      printf( "\n" );
   }


   _FREE( basecounts );
   fqreader_free( z );
   options_free( o );

   return 0;
}

#undef _IS_NULL
#undef _FREE
