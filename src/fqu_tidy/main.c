#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "options.h"
#include "fgetopt.h"
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
   struct options *o = options_new(  );
   struct fqreader *z;

   /* Get the command line options */
   options_cmdline( o, argc, argv );

   z = fqreader_new( o->fname );

   while ( fqreader_next( z, &h1, &h2, &s, &q ) ) {

      if ( o->squash_flag )
         h2[0] = '\0';

      if ( o->tabs_flag )
         printf( "%s\t%s\t%s\t%s\n", h1, s, h2, q );
      else
         printf( "@%s\n%s\n+%s\n%s\n", h1, s, h2, q );
   }

   fqreader_free( z );
   options_free( o );

   return 0;
}

#undef _IS_NULL
#undef _FREE
