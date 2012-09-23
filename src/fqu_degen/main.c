#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "options.h"
#include "fqreader.h"
#include "strutils.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)              ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)                 ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

static void
_to_ry( char *str )
{
   unsigned    i;

   for ( i = 0; i < strlen( str ); i++ ) {

      switch ( str[i] ) {
         case 'A':
         case 'a':
         case 'G':
         case 'g':
            str[i] = 'R';
            break;

         case 'C':
         case 'c':
         case 'T':
         case 't':
         case 'U':
         case 'u':
            str[i] = 'Y';
            break;

         default:
            break;
      }
   }
}

static void
_to_sw( char *str )
{
   unsigned    i;

   for ( i = 0; i < strlen( str ); i++ ) {

      switch ( str[i] ) {
         case 'C':
         case 'c':
         case 'G':
         case 'g':
            str[i] = 'S';
            break;

         case 'A':
         case 'a':
         case 'T':
         case 't':
         case 'U':
         case 'u':
            str[i] = 'W';
            break;

         default:
            break;
      }
   }
}

/*** main() ***/

int
main( int argc, char *argv[] )
{
   char       *h1, *h2, *s, *q;
   unsigned    i;
   unsigned    n;
   struct options *o = options_new(  );
   struct fqreader *z;

   /* Get the command line options */
   options_cmdline( o, argc, argv );

   if ( o->conversion_type > 2 ) {
      fprintf( stderr, "[ERROR] %s: Invalid conversion type specified: %d. See %s --help for details.\n", _I_AM, o->conversion_type, _I_AM );
      exit( 1 );
   }

   if ( o->optind == argc ) {                    /* read from stdin */

      z = fqreader_new( NULL );

      while ( fqreader_next( z, &h1, &h2, &s, &q ) ) {

         switch ( o->conversion_type ) {

            case 0:
               break;

            case 1:
               _to_ry( s );
               break;

            case 2:
               _to_sw( s );
               break;

            default:
               break;
         }

         printf( "@%s\n%s\n+%s\n%s\n", h1, s, h2, q );
      }

      fqreader_free( z );
   }

   else {                                        /* read from input files */
      int         k;

      for ( k = o->optind; k < argc; k++ ) {

         z = fqreader_new( argv[k] );

         if ( _IS_NULL( z ) ) {
            fprintf( stderr, "[ERROR] %s: Cannot open input file \"%s\"\n", _I_AM, argv[k] );
            exit( 1 );
         }

         while ( fqreader_next( z, &h1, &h2, &s, &q ) ) {

            switch ( o->conversion_type ) {

               case 0:
                  break;

               case 1:
                  _to_ry( s );
                  break;

               case 2:
                  _to_sw( s );
                  break;

               default:
                  break;
            }

            printf( "@%s\n%s\n+%s\n%s\n", h1, s, h2, q );
         }

         fqreader_free( z );
      }
   }

   options_free( o );

   return 0;
}

#undef _IS_NULL
#undef _FREE
