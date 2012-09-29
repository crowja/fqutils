#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "options.h"
#include "fqreader.h"
#include "linereader.h"
#include "strutils.h"
#include "tokenset.h"
#include "utils.h"

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
   char       *id = NULL;
   int         i;
   struct options *o = options_new(  );
   struct tokenset *t = tokenset_new(  );
   struct fqreader *fq = fqreader_new( NULL );

   /* Get the command line options */
   options_cmdline( o, argc, argv );

   /* Read the id files */
   for ( i = o->optind; i < argc; i++ ) {

      char       *line;
      struct linereader *z = linereader_new(  );

      linereader_init( z, argv[i] );

      if ( _IS_NULL( z ) ) {
         fprintf( stderr, "[ERROR] %s: Cannot open input file \"%s\"\n", _I_AM, argv[i] );
         exit( 1 );
      }

      while ( ( line = ( char * ) linereader_next( z ) ) ) {
         unsigned    len;

         stru_trim( line );

         if ( line[0] == '#' || stru_is_ws( line ) )
            continue;

         len = strcspn( line, "\f\n\r\t\v " );
         line[len] = '\0';

         tokenset_add( t, line );
      }

      linereader_free( z );
   }

   while ( fqreader_next( fq, &h1, &h2, &s, &q ) ) {

      utils_extract_id( &id, h1 );               /* get the identifier from header 1 */

      if ( tokenset_exists( t, id ) ) {
         if ( !o->reverse_flag )
            printf( "@%s\n%s\n+%s\n%s\n", h1, s, h2, q );
      }

      else {
         if ( o->reverse_flag )
            printf( "@%s\n%s\n+%s\n%s\n", h1, s, h2, q );
      }
   }

   _FREE( id );
   fqreader_free( fq );
   options_free( o );
   tokenset_free( t );

   return 0;
}

#undef _IS_NULL
#undef _FREE
