#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*** utils_extract_id() ***/

void
utils_extract_id( char **id, char *h )
{
   unsigned    len = strcspn( h, "\f\n\r\t\v " );
   *id = realloc( *id, sizeof ( char ) * ( 1 + len ) );
   strncpy( *id, h, len );
   ( *id )[len] = '\0';
}

/*** utils_print_spinner() ***/
void
utils_print_spinner( unsigned times )
{
   unsigned    i;

   printf( " " );

   for ( i = 0; i < times; i++ ) {
      printf( "\b|" ), sleep( 1 ), fflush( stdout );
      printf( "\b/" ), sleep( 1 ), fflush( stdout );
      printf( "\b-" ), sleep( 1 ), fflush( stdout );
      printf( "\b\\" ), sleep( 1 ), fflush( stdout );
   }

   printf("\b ");
}
