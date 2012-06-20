#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "varstr.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

static const char   version[] = "20111030";

struct varstr {
   unsigned            size;
   char               *x;
   unsigned            extend;
};

/*** varstr_new() ***/

struct varstr      *
varstr_new( void )
{
   struct varstr      *tp;

   tp = ( struct varstr * ) malloc( sizeof ( struct varstr ) );
   if ( _IS_NULL( tp ) )
      return NULL;

   tp->x = ( char * ) calloc( 1, sizeof ( char ) );
   tp->size = 0;
   tp->extend = 0;

   return tp;
}


/*** varstr_free() ***/

int
varstr_free( struct varstr *p )
{
   _FREE( p->x );
   _FREE( p );

   return 0;
}


/*** varstr_version() ***/

const char         *
varstr_version( void )
{
   return version;
}


/*** varstr_cat() ***/

void
varstr_cat( struct varstr *p, char *x )
{
   unsigned            need = 1 + strlen( p->x ) + strlen( x );

   if ( need >= p->size ) {
      p->x = ( char * ) realloc( p->x, ( need + p->extend ) * sizeof ( char ) );
      if ( _IS_NULL( p->x ) ) {
         fprintf( stderr, "[ERROR] Cannot allocate memory\n" );
         exit( 1 );
      }

      p->size = need + p->extend;
   }

   strcat( p->x, x );
}


/*** varstr_catc() ***/

void
varstr_catc( struct varstr *p, char x )
{
   unsigned            len = strlen( p->x );
   unsigned            need = 2 + len;

   if ( need >= p->size ) {
      p->x = ( char * ) realloc( p->x, ( need + p->extend ) * sizeof ( char ) );
      if ( _IS_NULL( p->x ) ) {
         fprintf( stderr, "[ERROR] Cannot allocate memory\n" );
         exit( 1 );
      }
      p->size = need + p->extend;
   }

   ( p->x )[len] = x;
   ( p->x )[len + 1] = '\0';
}


/*** varstr_chomp() ***/

void
varstr_chomp( struct varstr *p )
{
   char               *cp = varstr_str( p );
   int                 i = strlen( cp );

   while ( i > 0 ) {
      i -= 1;
      if ( !isspace( cp[i] ) )
         break;
   }

   cp[i + 1] = '\0';
}


/*** varstr_compact() ***/

void
varstr_compact( struct varstr *p )
{
   int                 i, j;
   int                 len = strlen( p->x );

   for ( i = 0, j = 0; i < len; i++ ) {

      if ( isspace( ( p->x )[i] ) )
         continue;

      ( p->x )[j] = ( p->x )[i];

      j += 1;
   }

   ( p->x )[j] = '\0';
}


/*** varstr_empty() ***/

void
varstr_empty( struct varstr *p )
{
   ( p->x )[0] = '\0';
}


/*** varstr_extend() ***/

unsigned
varstr_extend( struct varstr *p, unsigned extend )
{
   if ( extend > 0 )
      p->extend = extend;

   return p->extend;
}


/*** varstr_init() ***/

unsigned
varstr_init( struct varstr *p, unsigned extend )
{
   return varstr_extend( p, extend );
}


/*** varstr_lrtrim() ***/

void
varstr_lrtrim( struct varstr *g )
{
   char               *cp = g->x;
   unsigned            i = 0, j = 0;
   unsigned            len = strlen( cp );

   while ( i < len ) {
      if ( !isspace( cp[i] ) )
         break;
      i += 1;
   }

   while ( i < len ) {
      cp[j] = cp[i];
      i += 1;
      j += 1;
   }

   cp[j] = '\0';

   varstr_chomp( g );
}


/*** varstr_str() ***/

char               *
varstr_str( struct varstr *p )
{
   return p->x;
}


/*** varstr_to_s() ***/

char               *
varstr_to_s( struct varstr *p )
{
   char               *str = ( char * ) malloc( ( 1 + strlen( p->x ) ) * sizeof ( char ) );
   return strcpy( str, p->x );
}


#undef _IS_NULL
#undef _FREE
