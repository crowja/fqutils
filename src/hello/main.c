#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "options.h"

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
   struct options *o = options_new(  );

   /* Get the command line options */
   options_cmdline( o, argc, argv );

   if ( o->optind == argc ) {                    /* read from stdin */
      printf( "Hello world!\n" );
   }

   else {                                        /* read from input files */

      int         i;

      for ( i = o->optind; i < argc; i++ ) {
         printf( "Hello world %s\n", argv[i] );
      }
   }

   options_free( o );

   return 0;
}

#undef _IS_NULL
#undef _FREE
