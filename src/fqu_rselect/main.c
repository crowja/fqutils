#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "options.h"
#include "fqreader.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)              ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)                 ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))


/*** main() ***/

int
main( int argc, char *argv[] )
{
   char       *h1, *h2, *s, *q;
   unsigned    i;
   struct options *o = options_new(  );
   struct fqreader *z;

   /* Get the command line options */
   options_cmdline( o, argc, argv );

   srandom( time( NULL ) );

   if ( o->optind == argc ) {                    /* read from stdin */

      z = fqreader_new( NULL );

      while ( fqreader_next( z, &h1, &h2, &s, &q ) )
         if ( random(  ) < RAND_MAX * o->frac )
            printf( "@%s\n%s\n+%s\n%s\n", h1, s, h2, q );

      fqreader_free( z );
   }

   else {                                        /* read from input files */

      int         i;

      for ( i = o->optind; i < argc; i++ ) {

         z = fqreader_new( argv[i] );

         if ( _IS_NULL( z ) ) {
            fprintf( stderr, "[ERROR] %s: Cannot open input file \"%s\"\n", _I_AM, argv[i] );
            exit( 1 );
         }

         while ( fqreader_next( z, &h1, &h2, &s, &q ) )
            if ( random(  ) < RAND_MAX * o->frac )
               printf( "@%s\n%s\n+%s\n%s\n", h1, s, h2, q );

         fqreader_free( z );
      }
   }

   options_free( o );

   return 0;
}

#undef _IS_NULL
#undef _FREE
