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
   tp->squash_flag = 0;
   tp->tabs_flag = 0;
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
   fprintf( out, "%s [options] [<infile1> ...]\n", _I_AM );
   fprintf( out, "Streams the contents of <infile1> ... to stdout as text; uses stdin otherwise. \n" );
   fprintf( out, "For well-formed input, the output is guaranteed to be in lazy-FASTQ format (i.e.,\n" );
   fprintf( out, "four line records) even if the input contains multiline sequence or quality text.\n" );
   fprintf( out, "\nOPTIONS\n" );
   fprintf( out, "%s\n", "-h, --help" );
   fprintf( out, "%s%s\n", indent, "Print this help message and exit." );
   fprintf( out, "%s\n", "-q, --quiet" );
   fprintf( out, "%s%s\n", indent, "Run quietly." );
   fprintf( out, "%s\n", "-s, --squash" );
   fprintf( out, "%s%s\n", indent, "Attempt to reduce the size of each record. Currently this" );
   fprintf( out, "%s%s\n", indent, "simply replaces the second header in each record with a blank." );
   fprintf( out, "%s\n", "-t, --tab-delimited" );
   /*            "------------------------------------------------------------------------------80" */
   fprintf( out, "%s%s\n", indent, "Write the output as four tab-delimited columns. Format is" );
   fprintf( out, "%s%s\n", indent, "header_1[tab]sequence_string[tab]header_2[tab]quality_string." );
   fprintf( out, "%s\n", "-V, --verbosity" );
   fprintf( out, "%s%s\n", indent, "Increase the level of reporting, multiples accumulate." );
   fprintf( out, "%s\n", "-v, --version" );
   fprintf( out, "%s%s\n", indent, "Print the version information and exit." );
   fprintf( out, "\nEXAMPLES\n" );
   fprintf( out, "# Standard text file in\n" );
   fprintf( out, "%s in.fastq > out.fastq\n\n", _I_AM );
   fprintf( out, "# Gzip compressed file input\n" );
   fprintf( out, "%s in.fastq.gz > out.fastq\n\n", _I_AM );
   fprintf( out, "# Standard text on stdin\n" );
   fprintf( out, "gunzip -c in.fastq.gz | %s > out.fastq\n\n", _I_AM );
   fprintf( out, "# Compressed stream on stdin\n" );
   fprintf( out, "cat in.fastq.gz | %s > out.fastq\n\n", _I_AM );
   fprintf( out, "# Mixed input\n" );
   fprintf( out, "%s in1.fq in2.fq.gz in3.fq > out.fastq\n", _I_AM );
}


/*** options_cmdline() ***/

void
options_cmdline( struct options *p, int argc, char *argv[] )
{
   int         c;
   static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"quiet", no_argument, 0, 'q'},
      {"squash", no_argument, 0, 's'},
      {"max-threads", required_argument, 0, 'T'},
      {"tab-delimited", no_argument, 0, 't'},
      {"verbose", no_argument, 0, 'V'},
      {"version", no_argument, 0, 'v'},
      {0, 0, 0, 0}
   };

   while ( 1 ) {

      /* getopt_long stores the option index here. */
      int         option_index = 0;

      c = getopt_long( argc, argv, "hqsT:tVv", long_options, &option_index );

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

         case 's':
            p->squash_flag = 1;
            break;

         case 'T':
            p->max_threads = atol( optarg );
            if ( p->max_threads == 0 ) {
               fprintf( stderr, "[WARNING] %s: You really want to run with no threads? Ok, ... done!\n", _I_AM );
               exit( 0 );
            }
            printf( "[WARNING] %s: you specified %d threads, but this option currently is unavailable\n", _I_AM,
             p->max_threads );
            break;

         case 't':
            p->tabs_flag = 1;
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
