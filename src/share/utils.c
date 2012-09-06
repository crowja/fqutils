#include <stdlib.h>
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
