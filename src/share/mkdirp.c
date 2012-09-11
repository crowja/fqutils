#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mkdirp.h"

int mkdirp( char *pathname, mode_t mode )
{
   char       *pathname2 = NULL;
   int         i;
   int         rc = 0;
   struct stat st;

   pathname2 = realloc( pathname2, ( 1 + strlen( pathname ) ) * sizeof ( char ) );

   for ( i = 0; i <= strlen( pathname ); i++ )
      if ( pathname[i] == '/' || pathname[i] == '\0' ) {
         strncpy( pathname2, pathname, i );
         pathname2[i] = '\0';
         mkdir( pathname2, mode );

      }

   free( pathname2 );

   return stat( pathname, &st ) ? 1 : 0;         /* return 0 if it exists */
}
