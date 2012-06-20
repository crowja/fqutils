#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "options.h"
#include "fgetopt.h"
#include "tdfreader.h"

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
   char      **list;
   struct options *o = options_new(  );
   struct tdfreader *z;

   /* Get the command line options */
   options_cmdline( o, argc, argv );

   z = tdfreader_new(  );
   tdfreader_init( z, NULL );

   while ( tdfreader_next( z, list ) ) {

#if 1
      if ( _IS_NULL( list[0] ) )
         continue;

      else if ( _IS_NULL( list[1] ) )
         printf( "@%s\n%s\n+%s\n%s\n", list[0], "", "", "" );

      else if ( _IS_NULL( list[2] ) )
         printf( "@%s\n%s\n+%s\n%s\n", list[0], list[1], "", "" );

      else if ( _IS_NULL( list[3] ) )
         printf( "@%s\n%s\n+%s\n%s\n", list[0], list[1], list[2], "" );

      else
         printf( "@%s\n%s\n+%s\n%s\n", list[0], list[1], list[2], list[3] );
#endif

   }

   fqreader_free( z );
   options_free( o );

   return 0;
}

#undef _IS_NULL
#undef _FREE
