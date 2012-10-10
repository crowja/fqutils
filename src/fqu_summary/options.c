#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "options.h"
#include "getopt.h"
#include "main.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)    ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)       ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

/*
 *  Structure is defined in options.h since it needs to be visible.
 */

/*** options_new() ***/

struct options *
options_new( void )
{
   struct options *tp;

   tp = ( struct options * ) malloc( sizeof ( struct options ) );
   if ( _IS_NULL( tp ) )
      return NULL;

   tp->fname = NULL;
   tp->max_threads = 1;
   tp->verbosity = 0;

   return tp;
}


/*** options_free() ***/

void
options_free( struct options *p )
{
   if ( _IS_NULL( p ) )
      return;

   _FREE( p->fname );
   _FREE( p );
}


/*** options_helpmsg() ***/

void
options_helpmsg( FILE *out )
{
   char        indent[] = "      ";

   /*            "------------------------------------------------------------------------------80" */
   fprintf( out, "USAGE\n" );
   fprintf( out, "%s [options] [<infile>]\n", _I_AM );
   fprintf( out, "Reads <infile>, assumed to be nucleotide sequences, and writes a simple summary.\n" );
   fprintf( out, "Input is from <infile> if present, otherwise stdin. See REPORT STATISTICS below.\n" );

   fprintf( out, "\nOPTIONS\n" );
   fprintf( out, "%s\n", "-h, --help" );
   fprintf( out, "%s%s\n", indent, "Print this help message and exit." );
   fprintf( out, "%s\n", "-q, --quiet" );
   fprintf( out, "%s%s\n", indent, "Run quietly." );
   fprintf( out, "%s\n", "-V, --verbosity" );
   fprintf( out, "%s%s\n", indent, "Increase the level of reporting, multiples accumulate." );
   fprintf( out, "%s\n", "-v, --version" );
   fprintf( out, "%s%s\n", indent, "Print the version information and exit." );

   fprintf( out, "\nREPORT STATISTICS\n" );
   fprintf( out, "Summary statistics are reported in a simple tab-delimited key-value format, designed\n" );
   fprintf( out, "to be easily machine-readable. For multiattribute values, for example the counts per\n" );
   fprintf( out, "position reported for basecounts_a, individual attributes are likewise tab-delimited.\n\n" );
   fprintf( out, "seqcount\n" );
   fprintf( out, "%sTotal number of sequences in the collection.\n", indent );
   fprintf( out, "maxpos\n" );
   fprintf( out, "%sMaximum position observed, a.k.a., length of longest sequence.\n", indent );
   fprintf( out, "qualities_offset\n" );
   fprintf( out, "%sEstimated quality offset (33 or 64).\n", indent );
   fprintf( out, "basecounts_a\n" );
   fprintf( out, "%sTotal counts observed for A in each position.\n", indent );
   fprintf( out, "basecounts_c\n" );
   fprintf( out, "%sTotal counts observed for C in each position.\n", indent );
   fprintf( out, "basecounts_g\n" );
   fprintf( out, "%sTotal counts observed for G in each position.\n", indent );
   fprintf( out, "basecounts_t\n" );
   fprintf( out, "%sTotal counts observed for T in each position.\n", indent );
   fprintf( out, "basecounts_u\n" );
   fprintf( out, "%sTotal counts observed for U in each position.\n", indent );
   fprintf( out, "basecounts_n\n" );
   fprintf( out, "%sTotal counts observed for N in each position.\n", indent );
   fprintf( out, "basecounts_other\n" );
   fprintf( out, "%sTotal counts observed for anything besides A, C, G, T, U, N  in each position.\n", indent );
   fprintf( out, "histogram_gc_per_sequence\n" );
   fprintf( out, "%sCounts for each of twenty equally sized cells representing the GC intervals\n", indent );
   fprintf( out, "%sGC <= 0.05, ..., 0.95 < GC <= 1.0. This is a histogram of per-sequence GC.\n", indent );
   fprintf( out, "qualquants_1\n" );
   fprintf( out, "%sFirst quartile of quality in each position.\n", indent );
   fprintf( out, "qualquants_2\n" );
   fprintf( out, "%sSecond quartile (median) of quality in each position.\n", indent );
   fprintf( out, "qualquants_3\n" );
   fprintf( out, "%sThird quartile of quality in each position.\n", indent );
}


/*** options_cmdline() ***/

void
options_cmdline( struct options *p, int argc, char *argv[] )
{
   int         c;
   static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"quiet", no_argument, 0, 'q'},
      {"max-threads", required_argument, 0, 'T'},
      {"verbose", no_argument, 0, 'V'},
      {"version", no_argument, 0, 'v'},
      {0, 0, 0, 0}
   };

   while ( 1 ) {

      /* getopt_long stores the option index here. */
      int         option_index = 0;

      c = getopt_long( argc, argv, "hqT:Vv", long_options, &option_index );

      /* Detect the end of the options. */
      if ( c == -1 )
         break;

      switch ( c ) {

         case 'h':
            options_helpmsg( stdout );
            exit( 0 );

         case 'q':
            p->verbosity = 0;
            break;

         case 'T':
            p->max_threads = atol( optarg );
            printf( "[WARNING] %s: you specified %d threads, but this option currently is unavailable\n", _I_AM, p->max_threads );
            break;

         case 'V':
            /* printf( " --verbose\n" ); */
            p->verbosity += 1;
            break;

         case 'v':
            printf( "%s-%s\n", _I_AM, PACKAGE_VERSION );
            exit( 0 );

         case '?':
            /* getopt_long already printed an error message. */
            exit( 1 );

         default:
            abort(  );
      }
   }

   p->optind = optind;
}

#undef _IS_NULL
#undef _FREE
