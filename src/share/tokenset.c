#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "uthash.h"
#include "tokenset.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

static const char version[] = "20120905";

struct _token {
   char       *text;
   unsigned    id;
   UT_hash_handle hh;
};

struct tokenset {
   unsigned    count;
   struct _token *tokens;
};

static int
_text_sort( struct _token *a, struct _token *b )
{
   return strcmp( a->text, b->text );
}

/*** tokenset_new() ***/

struct tokenset *
tokenset_new( void )
{
   struct tokenset *tp;

   tp = ( struct tokenset * ) malloc( sizeof ( struct tokenset ) );
   if ( _IS_NULL( tp ) )
      return NULL;

   tp->count = 0;
   tp->tokens = NULL;                            /* required by uthash */

   return tp;
}

/*** tokenset_free() ***/

void
tokenset_free( struct tokenset *p )
{

   struct _token *s;
   struct _token *t;

   if ( _IS_NULL( p ) )
      return;

   t = p->tokens;

   while ( t != NULL ) {
      s = t;
      t = s->hh.next;
      _FREE( s->text );
      HASH_DEL( p->tokens, s );
      _FREE( s );
   }

   _FREE( p );
}

/*** tokenset_version() ***/

const char *
tokenset_version( void )
{
   return version;
}

/*** tokenset_add() ***/

int
tokenset_add( struct tokenset *p, char *n )
{
   struct _token *s;

   HASH_FIND_STR( p->tokens, n, s );

   if ( !_IS_NULL( s ) )
      return s->id;

   s = ( struct _token * ) malloc( sizeof ( struct _token ) );
   s->text = malloc( ( 1 + strlen( n ) ) * sizeof ( char ) );
   strcpy( s->text, n );

   s->id = p->count;

#if 0
   HASH_ADD_STR( p->tokens, text, s );
#else
   HASH_ADD_KEYPTR( hh, p->tokens, s->text, strlen( s->text ), s );
#endif

   p->count += 1;                                /* ready to map next entry */

   return s->id;
}

/*** tokenset_count() ***/

int
tokenset_count( struct tokenset *p )
{
   return HASH_COUNT( p->tokens );
}

/*** tokenset_exists() ***/

int
tokenset_exists( struct tokenset *p, char *n )
{
   struct _token *s;

   HASH_FIND_STR( p->tokens, n, s );

   return _IS_NULL( s ) ? 0 : 1;
}

/*** tokenset_get() ***/

char      **
tokenset_get( struct tokenset *p )
{
   struct _token *s = p->tokens;
   int         last = tokenset_count( p );
   char      **list = ( char ** ) calloc( 1 + last, sizeof ( char * ) );
   int         i;

   for ( i = 0; i < last; i++ ) {
      list[i] = ( char * ) calloc( 1 + strlen( s->text ), sizeof ( char ) );
      strcpy( list[i], s->text );
      /* printf("REPORT: %s\n", list[i]); */
      s = s->hh.next;
   }

   list[last] = NULL;

   return list;
}

/*** tokenset_get_by_id() ***/

const char *
tokenset_get_by_id( struct tokenset *p, unsigned id )
{

   struct _token *s;
   struct _token *t = p->tokens;

   while ( t != NULL ) {

      s = t;
      t = s->hh.next;

      if ( s->id == id )
         return ( const char * ) s->text;
   }

   return NULL;
}

 /*** tokenset_remove() ***/

void
tokenset_remove( struct tokenset *p, char *n )
{
   struct _token *s;

   HASH_FIND_STR( p->tokens, n, s );

   if ( _IS_NULL( s ) )
      return;

   _FREE( s->text );
   HASH_DEL( p->tokens, s );

   _FREE( s );
}

/*** tokenset_reset() ***/

void
tokenset_reset( struct tokenset *p )
{

   struct _token *s;

   struct _token *t = p->tokens;

   while ( t != NULL ) {
      s = t;
      t = s->hh.next;
      _FREE( s->text );
      HASH_DEL( p->tokens, s );
      _FREE( s );
   }

   p->count = 0;
}

/*** tokenset_sort() ***/

void
tokenset_sort( struct tokenset *p )
{
   HASH_SORT( p->tokens, _text_sort );
}


#undef _IS_NULL
#undef _FREE
