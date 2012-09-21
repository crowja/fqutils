#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
   char       *h11, *h12, *h21, *h22;
   char       *s1, *s2, *q1, *q2;
   unsigned    i;
   int         len;
   int         rc1, rc2;
   struct options *o = options_new(  );
   struct fqreader *z1, *z2;

   /* Get the command line options */
   options_cmdline( o, argc, argv );

   if ( o->optind + 2 > argc )
      exit( 1 );


   z1 = fqreader_new( argv[o->optind] );
   z2 = fqreader_new( argv[o->optind + 1] );

   for ( ;; ) {

      rc1 = fqreader_next( z1, &h11, &h12, &s1, &q1 );
      rc2 = fqreader_next( z2, &h21, &h22, &s2, &q2 );

      if ( rc1 != rc2 ) {
         printf( "not_paired\t%s\t%s\n", argv[o->optind], argv[o->optind + 1] );
         exit( 1 );
      }

      /* Both return codes are the same, see if we need to quit */
      if ( rc1 == 0 )
         break;

      /* Check the ids -- exit if they don't match exactly */
      len = strcspn( h11, "\n\t " );
      h11[len] = '\0';
      len = strcspn( h21, "\n\t " );
      h21[len] = '\0';
      if ( strcmp( h11, h21 ) ) {
         printf( "not_paired\t%s\t%s\n", argv[o->optind], argv[o->optind + 1] );
         exit( 1 );
      }
   }

   fqreader_free( z1 );
   fqreader_free( z2 );

   if ( o->verbosity > 0 )
      printf( "paired\t%s\t%s\n", argv[o->optind], argv[o->optind + 1] );

   options_free( o );

   return 0;
}

#undef _IS_NULL
#undef _FREE
