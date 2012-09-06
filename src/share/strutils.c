#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "strutils.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))


static const char version[] = "20120118";


/*** _catc() ***/

static int
_catc( char c, unsigned *size, unsigned extend, char **str )
{
   unsigned    pos = strlen( *str );
   char       *tmp;

   if ( pos + 1 > *size ) {                      /* extend if necessary */
      tmp = realloc( *str, ( *size + extend ) * sizeof ( char ) );

      if ( _IS_NULL( tmp ) )
         return 1;

      *size += 1 + extend;
      *str = tmp;
   }

   ( *str )[pos] = c;
   ( *str )[pos + 1] = '\0';

   return 0;
}


/*** stru_chomp() ***/

char       *
stru_chomp( char *str )
{
   unsigned    i = strlen( str );

   while ( i > 0 ) {
      i -= 1;
      if ( str[i] == '\n' )
         str[i] = '\0';
      else
         break;
   }

   return str;
}


/*** stru_crush() ***/

char       *
stru_crush( char *str )
{
   unsigned    i = 0;
   unsigned    j = 0;
   unsigned    len = strlen( str );

   while ( i < len ) {
      if ( !isspace( str[i] ) ) {
         str[j] = str[i];
         j += 1;
      }
      i += 1;
   }

   str[j] = '\0';

   return str;
}


/*** stru_is_ws() ***/

unsigned
stru_is_ws( char *str )
{
   unsigned    i;

   for ( i = 0; i < strlen( str ); i++ )
      if ( !isspace( str[i] ) )
         return 0;

   return 1;
}


/*** stru_lcat() ***/

char       *
stru_lcat( char **str1, char **str2 )
{
   unsigned    need;

   if ( NULL == *str1 ) {
      if ( NULL != *str2 ) {
         need = 1 + strlen( *str2 );
         *str1 = realloc( *str1, need * sizeof ( char ) );
         ( *str1 )[0] = '\0';
         strcpy( *str1, *str2 );
      }
   }

   else {
      if ( NULL != *str2 ) {
         need = 1 + strlen( *str1 ) + strlen( *str2 );
         *str1 = realloc( *str1, need * sizeof ( char ) );
         strcat( *str1, *str2 );
      }
   }

   return *str1;
}


/*** stru_split() ***/

char      **
stru_split( char delim, char *str )
{
   unsigned    count = 0;
   unsigned    i;
   unsigned    extend = 64;
   unsigned    size = 0;
   char       *work = NULL;
   char       *cp = str;
   char      **list = NULL;
   enum states { dquote, squote, uquote };  /* double-quoted, single-quoted, unquoted states */
   enum states state = uquote;

   work = realloc( work, extend * sizeof ( char ) );
   size = extend;
   work[0] = '\0';

   for ( ;; ) {

      switch ( state ) {

         case uquote:

            if ( *cp == '\0' ) {

               if ( strlen( work ) > 0 ) {
                  count += 2;
                  list = realloc( list, count * sizeof ( char * ) );
                  list[count - 2] = malloc( ( 1 + strlen( work ) ) * sizeof ( char ) );
                  strcpy( list[count - 2], work );
                  list[count - 1] = NULL;
               }

               else {
                  count += 1;
                  list = realloc( list, count * sizeof ( char * ) );
                  list[count - 1] = NULL;
               }

               _FREE( work );
               return list;
            }

            else if ( *cp == '\"' ) {
               if ( *( cp + 1 ) == '\"' ) {
                  _catc( *cp, &size, extend, &work );
                  cp += 2;
               }

               else {
                  state = dquote;
                  cp += 1;
               }
            }

            else if ( *cp == '\'' ) {
               if ( *( cp + 1 ) == '\'' ) {
                  _catc( *cp, &size, extend, &work );
                  cp += 2;
               }

               else {
                  state = squote;
                  cp += 1;
               }
            }

            else if ( *cp == delim ) {           /* emit */
               count += 1;
               list = realloc( list, count * sizeof ( char * ) );
               list[count - 1] = malloc( ( 1 + strlen( work ) ) * sizeof ( char ) );
               strcpy( list[count - 1], work );
               ( work )[0] = '\0';
               cp += 1;
            }

            else {
               _catc( *cp, &size, extend, &work );
               cp += 1;
            }

            break;

         case dquote:

            if ( *cp == '\0' )
               goto FAIL;

            else if ( *cp == '\"' ) {
               if ( *( cp + 1 ) == '\"' ) {
                  _catc( *cp, &size, extend, &work );
                  cp += 2;
               }

               else {
                  state = uquote;
                  cp += 1;
               }
            }

            else {
               _catc( *cp, &size, extend, &work );
               cp += 1;
            }

            break;

         case squote:

            if ( *cp == '\0' )
               goto FAIL;

            else if ( *cp == '\'' ) {
               if ( *( cp + 1 ) == '\'' ) {
                  _catc( *cp, &size, extend, &work );
                  cp += 2;
               }

               else {
                  state = uquote;
                  cp += 1;
               }
            }

            else {
               _catc( *cp, &size, extend, &work );
               cp += 1;
            }

            break;

         default:
            break;
      }
   }

 FAIL:

   _FREE( work );

   for ( i = 0; i < count; i++ )
      _FREE( list[i] );

   _FREE( list );

   return NULL;
}

/*** stru_splitpp() ***/

unsigned
stru_splitpp( char delim, char *str, char **list )
{
   unsigned    count = 0;
   unsigned    extend = 64;
   unsigned    size = 0;
   char       *work = NULL;
   char       *cp = str;

   enum states { dquote, squote, uquote };  /* double-quoted, single-quoted, unquoted states */
   enum states state = uquote;

   if ( _IS_NULL( list ) ) {
      list = realloc( list, sizeof ( char * ) );
      list[0] = NULL;
   }

   work = realloc( work, extend * sizeof ( char ) );
   size = extend;
   work[0] = '\0';

   for ( ;; ) {

      switch ( state ) {

         case uquote:

            if ( *cp == '\0' ) {

               if ( strlen( work ) > 0 ) {
                  count += 2;
                  list = realloc( list, count * sizeof ( char * ) );
                  list[count - 2] = realloc( list[count - 2], ( 1 + strlen( work ) ) * sizeof ( char ) );
                  strcpy( list[count - 2], work );
                  list[count - 1] = NULL;
               }

               else {
                  count += 1;
                  list = realloc( list, count * sizeof ( char * ) );
                  list[count - 1] = NULL;
               }

               _FREE( work );
               return count;                     /* FIXME */
            }

            else if ( *cp == '\"' ) {
               if ( *( cp + 1 ) == '\"' ) {
                  _catc( *cp, &size, extend, &work );
                  cp += 2;
               }

               else {
                  state = dquote;
                  cp += 1;
               }
            }

            else if ( *cp == '\'' ) {
               if ( *( cp + 1 ) == '\'' ) {
                  _catc( *cp, &size, extend, &work );
                  cp += 2;
               }

               else {
                  state = squote;
                  cp += 1;
               }
            }

            else if ( *cp == delim ) {           /* emit */
               count += 1;
               list = realloc( list, count * sizeof ( char * ) );
               list[count - 1] = realloc( list[count - 1], ( 1 + strlen( work ) ) * sizeof ( char ) );
               strcpy( list[count - 1], work );
               ( work )[0] = '\0';
               cp += 1;
            }

            else {
               _catc( *cp, &size, extend, &work );
               cp += 1;
            }

            break;

         case dquote:

            if ( *cp == '\0' )
               goto FAIL;

            else if ( *cp == '\"' ) {
               if ( *( cp + 1 ) == '\"' ) {
                  _catc( *cp, &size, extend, &work );
                  cp += 2;
               }

               else {
                  state = uquote;
                  cp += 1;
               }
            }

            else {
               _catc( *cp, &size, extend, &work );
               cp += 1;
            }

            break;

         case squote:

            if ( *cp == '\0' )
               goto FAIL;

            else if ( *cp == '\'' ) {
               if ( *( cp + 1 ) == '\'' ) {
                  _catc( *cp, &size, extend, &work );
                  cp += 2;
               }

               else {
                  state = uquote;
                  cp += 1;
               }
            }

            else {
               _catc( *cp, &size, extend, &work );
               cp += 1;
            }

            break;

         default:
            break;
      }
   }

 FAIL:

   _FREE( work );

   return 0;                                     /* FIXME */
}


/*** stru_tolower() ***/

char       *
stru_tolower( char *str )
{
   unsigned    i;

   for ( i = 0; i < strlen( str ); i++ )
      str[i] = tolower( str[i] );

   return str;
}


/*** stru_toupper() ***/

char       *
stru_toupper( char *str )
{
   unsigned    i;

   for ( i = 0; i < strlen( str ); i++ )
      str[i] = toupper( str[i] );

   return str;
}


/*** stru_trim() ***/

char       *
stru_trim( char *str )
{
   unsigned    i;
   unsigned    j;
   unsigned    len;

   len = strlen( str );
   i = len;

   while ( i > 0 ) {
      i -= 1;
      if ( isspace( str[i] ) )
         str[i] = '\0';
      else
         break;
   }

   len = strlen( str );
   i = strspn( str, "\t\n\v\f\r " );
   j = 0;

   while ( i < len ) {
      str[j] = str[i];
      i += 1;
      j += 1;
   }

   str[j] = '\0';

   return str;
}


/*** stru_version() ***/

const char *
stru_version( void )
{
   return version;
}

#undef _IS_NULL
#undef _FREE
