#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
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

   tp->check_initial = UINT_MAX;
   tp->fname = NULL;
   tp->max_threads = 1;
   tp->min_count = 1;
   tp->verbosity = 0;
   tp->word_size = 5;

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
   fprintf( out, "Generate word counts for the sequences in <infile1> ...; uses stdin otherwise.\n" );
   fprintf( out, "\nOPTIONS\n" );
   fprintf( out, "%s\n", "-c, --check-initial <num>" );
   fprintf( out, "%s%s\n", indent, "Check at most the first <num> words per record, from 5' [default is all]." );
   fprintf( out, "%s\n", "-h, --help" );
   fprintf( out, "%s%s\n", indent, "Print this help message and exit." );
   fprintf( out, "%s\n", "-m, --min-count <min>" );
   fprintf( out, "%s%s\n", indent, "Do not report word counts smaller than <min> [default: 1]." );
   fprintf( out, "%s\n", "-q, --quiet" );
   fprintf( out, "%s%s\n", indent, "Run quietly." );
   fprintf( out, "%s\n", "-s, -w, --word-size <size>" );
   fprintf( out, "%s%s\n", indent, "Use word size <size> [default: 5]." );
   fprintf( out, "%s\n", "-V, --verbosity" );
   fprintf( out, "%s%s\n", indent, "Increase the level of reporting, multiples accumulate." );
   fprintf( out, "%s\n", "-v, --version" );
   fprintf( out, "%s%s\n", indent, "Print the version information and exit." );
}


/*** options_cmdline() ***/

void
options_cmdline( struct options *p, int argc, char *argv[] )
{
   int         c;
   static struct option long_options[] = {
      {"check-initial", required_argument, 0, 'c'},
      {"help", no_argument, 0, 'h'},
      {"min-count", required_argument, 0, 'm'},
      {"max-threads", required_argument, 0, 'T'},
      {"quiet", no_argument, 0, 'q'},
      {"word-size", required_argument, 0, 's'},
      {"verbose", no_argument, 0, 'V'},
      {"version", no_argument, 0, 'v'},
      {0, 0, 0, 0}
   };

   while ( 1 ) {

      /* getopt_long stores the option index here. */
      int         option_index = 0;

      c = getopt_long( argc, argv, "c:hm:qs:T:Vvw:", long_options, &option_index );

      /* Detect the end of the options. */
      if ( c == -1 )
         break;

      switch ( c ) {

         case 'c':
            p->check_initial = atol( optarg );
            break;

         case 'h':
            options_helpmsg( stdout );
            exit( 0 );

         case 'm':
            p->min_count = atol( optarg );;
            break;

         case 'q':
            p->verbosity = 0;
            break;

         case 's':
         case 'w':
            p->word_size = atol( optarg );;
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
