#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "options.h"
#include "fgetopt.h"

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

   if ( NULL != o->fname )
      printf( "FNAME: %s\n", o->fname );

   /* Do the magic */
   printf( "Hello, world!\n" );

   options_free( o );

   return 0;
}

#undef _IS_NULL
#undef _FREE
