#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tdfreader.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

static const char version[] = "20111206";

struct tdfreader {
   char       *readbuf;
   unsigned    readbuf_size;
   char       *line;
   unsigned    line_extend;
   unsigned    line_size;
   char      **vals;
   unsigned    vals_extend;
   unsigned    vals_size;
};

static int
_textbuf2str( size_t m, char *textbuf, char *str )
{
   unsigned    i;

   for ( i = 0; i < m; i++ ) {

      str[i] = textbuf[i];

      if ( str[i] == '\0' )
         break;

      else
         str[i + 1] = '\0';
   }

   return 0;
}


/*** tdfreader_new() ***/

struct tdfreader *
tdfreader_new( void )
{
   struct tdfreader *tp;

   tp = ( struct tdfreader * ) malloc( sizeof ( struct tdfreader ) );
   if ( _IS_NULL( tp ) )
      return NULL;

   tp->readbuf = NULL;
   tp->readbuf_size = 4;
   tp->line = NULL;
   tp->line_size = 2;
   tp->line_extend = 3;
   tp->vals = NULL;
   tp->vals_size = 0;
   tp->vals_extend = 64;

   return tp;
}


/*** tdfreader_free() ***/

void
tdfreader_free( struct tdfreader *p )
{
   unsigned    i;

   _FREE( p->readbuf );
   _FREE( p->line );

   for ( i = 0; i < p->vals_size; i++ )
      _FREE( ( p->vals )[i] );

   _FREE( p->vals );
   _FREE( p );
}


/*** tdfreader_version() ***/

const char *
tdfreader_version( void )
{
   return version;
}


/*** tdfreader_init() ***/

int
tdfreader_init( struct tdfreader *p, void *x )
{
   p->readbuf = realloc( p->readbuf, p->readbuf_size * sizeof ( char ) );
   p->line = realloc( p->line, p->line_size * sizeof ( char ) );

   return 0;
}


/*** tdfreader_next() ***/

int
tdfreader_next( struct tdfreader *p, char **list )
{
   char       *cp1, *cp2;

   /*** Read the next line of text ***/

   ( p->line )[0] = '\0';

   for ( ;; ) {
      unsigned    need = 1 + strlen( p->line ) + p->readbuf_size;

      if ( need >= p->line_size ) {
         p->line = realloc( p->line, ( need + p->line_extend ) * sizeof ( char ) );
         p->line_size = need + p->line_extend;
      }


      fgets( p->readbuf, p->readbuf_size, stdin );

      if ( feof( stdin ) )
         return 0;

      strcat( p->line, p->readbuf );

      if ( !_IS_NULL( strchr( p->readbuf, '\n' ) ) )
         break;
   }

   /* printf( "%s\n", p->line ); */


   /*** Split the line ***/

   cp1 = p->line;

   for ( ;; ) {
      cp2 = strpbrk( cp1, " \t" );

      if ( _IS_NULL( cp2 ) )
         break;

      cp1 = cp2 + 1;
   }


   return 1;
}


#undef _IS_NULL
#undef _FREE
