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

struct options *options_new( void )
{
   struct options *tp;

   tp = ( struct options * ) malloc( sizeof ( struct options ) );
   if ( _IS_NULL( tp ) )
      return NULL;

   tp->fname = NULL;
   tp->outname = NULL;
   tp->quiet_flag = 0;
   tp->verbosity = 0;

   return tp;
}


/*** options_free() ***/

void options_free( struct options *p )
{
   if ( _IS_NULL( p ) )
      return;

   _FREE( p->fname );
   _FREE( p->outname );
   _FREE( p );
}


/*** options_helpmsg() ***/

void options_helpmsg( FILE *out )
{
   char        indent[] = "        ";

   /*            "------------------------------------------------------------------------------80" */
   fprintf( out, "USAGE: cat in.fq | %s [options] <id_file1> ...\n", _I_AM );
   fprintf( out, "Splits a file in fastq file into two fastq files based on a collection of\n" );
   fprintf( out, "read identifiers specified in <id_file1> ...\n\n" );
   fprintf( out, "Two files are written: <out>_A.fq and <out>_B.fq. Reads specified in any of the\n" );
   fprintf( out, "id_files are written to the former, and the remainder to the latter. Note that\n" );
   fprintf( out, "the relative order of the reads in the input is preserved in the output files.\n" );
   fprintf( out, "\nOPTIONS:\n" );
   fprintf( out, "%s\n", "-h, --help" );
   fprintf( out, "%s%s\n", indent, "Print this help message and exit." );
   fprintf( out, "%s\n", "-o, --out <outname>" );
   fprintf( out, "%s%s\n", indent, "Write output to <outname>_A.fq and <outname>_B.fq; default: ./FQU." );
   fprintf( out, "%s\n", "-q, --quiet" );
   fprintf( out, "%s%s\n", indent, "Run quietly." );
   fprintf( out, "%s\n", "-V, --verbosity" );
   fprintf( out, "%s%s\n", indent, "Increase the level of reporting, multiples accumulate." );
   fprintf( out, "%s\n", "-v, --version" );
   fprintf( out, "%s%s\n", indent, "Print the version information and exit." );
}


/*** options_cmdline() ***/

void options_cmdline( struct options *p, int argc, char *argv[] )
{
   int         c;
   static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"out", required_argument, 0, 'o'},
      {"verbose", no_argument, 0, 'V'},
      {"version", no_argument, 0, 'v'},
      {0, 0, 0, 0}
   };

   while ( 1 ) {

      /* getopt_long stores the option index here. */
      int         option_index = 0;

      c = getopt_long( argc, argv, "ho:stVv", long_options, &option_index );

      /* Detect the end of the options. */
      if ( c == -1 )
         break;

      switch ( c ) {

         case 'h':
            options_helpmsg( stdout );
            exit( 0 );

         case 'o':
            p->outname = realloc( p->outname, ( 1 + strlen( optarg ) ) * sizeof ( char ) );
            strcpy( p->outname, optarg );
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
            break;

         default:
            abort(  );
      }
   }

   p->optind = optind;
}

#undef _IS_NULL
#undef _FREE
