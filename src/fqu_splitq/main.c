#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "options.h"
#include "fqreader.h"
#include "linereader.h"
#include "strutils.h"
#include "tokenset.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)              ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)                 ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

/*** main() ***/

int main( int argc, char *argv[] )
{
   FILE       *out_a, *out_b;
   char       *h1, *h2, *s, *q;
   char       *id = NULL;
   char       *outname_a = NULL, *outname_b = NULL;
   int         i;
   struct options *o = options_new(  );
   struct tokenset *t = tokenset_new(  );
   struct fqreader *fq = fqreader_new( NULL );

   /* Get the command line options */
   options_cmdline( o, argc, argv );

   if ( _IS_NULL( o->outname ) || strlen( o->outname ) == 0 ) {
      o->outname = realloc(o->outname, 4 * sizeof(char));
      strcpy(o->outname, "FQU");
   }

   /* Read to id files */
   for ( i = o->optind; i < argc; i++ ) {

      char       *line;
      struct linereader *z = linereader_new(  );

      linereader_init( z, argv[i] );

      if ( _IS_NULL( z ) ) {
         fprintf( stderr, "[ERROR] %s: Cannot open input file \"%s\"\n", _I_AM, argv[i] );
         exit( 1 );
      }

      while ( ( line = linereader_next( z ) ) ) {
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


   outname_a = realloc( outname_a, sizeof ( char ) * ( 6 + strlen( o->outname ) ) );
   strcpy( outname_a, o->outname );
   strcat( outname_a, "_a.fq" );
   out_a = fopen( outname_a, "wb" );
   if ( _IS_NULL( out_a ) ) {
      fprintf( stderr, "Could not open first output file \"%s\"\n", outname_a );
      exit( 1 );
   }

   outname_b = realloc( outname_b, sizeof ( char ) * ( 6 + strlen( o->outname ) ) );
   strcpy( outname_b, o->outname );
   strcat( outname_b, "_b.fq" );
   out_b = fopen( outname_b, "wb" );
   if ( _IS_NULL( out_b ) ) {
      fprintf( stderr, "Could not open second output file \"%s\"\n", outname_b );
      exit( 1 );
   }


   while ( fqreader_next( fq, &h1, &h2, &s, &q ) ) {

      utils_extract_id( &id, h1 );               /* get the identifier from header 1 */

      if ( tokenset_exists( t, id ) )
         fprintf( out_a, "@%s\n%s\n+%s\n%s\n", h1, s, h2, q );

      else
         fprintf( out_b, "@%s\n%s\n+%s\n%s\n", h1, s, h2, q );
   }

   fclose( out_a );
   fclose( out_b );

   _FREE( id );
   _FREE( outname_a );
   _FREE( outname_b );
   fqreader_free( fq );
   options_free( o );
   tokenset_free( t );

   return 0;
}

#undef _IS_NULL
#undef _FREE
