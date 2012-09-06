#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "varstr.h"
#include "linereader.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

#ifdef  _BUFSIZE
#undef  _BUFSIZE
#endif
#define _BUFSIZE      1024                       /* _BUFSIZE > 1 */

static const char version[] = "20111128";

struct linereader {
   FILE       *in;
   char        buf[_BUFSIZE];
   struct varstr *text;
};


/*** linereader_new() ***/

struct linereader *
linereader_new( void )
{
   struct linereader *tp;

   tp = ( struct linereader * ) malloc( sizeof ( struct linereader ) );
   if ( _IS_NULL( tp ) )
      return NULL;

   tp->in = stdin;                               /* default */
   tp->text = varstr_new(  );

   return tp;
}


/*** linereader_free() ***/

void
linereader_free( struct linereader *p )
{
   if ( _IS_NULL( p ) )
      return;

   varstr_free( p->text );

   if ( p->in != stdin && !_IS_NULL( p->in ) )
      fclose( p->in );

   _FREE( p );
}


/*** linereader_version() ***/

const char *
linereader_version( void )
{
   return version;
}


/*** linereader_init() ***/

int
linereader_init( struct linereader *p, char *fname )
{

   if ( p->in != stdin )
      fclose( p->in );

   p->in = fopen( fname, "r" );
   if ( _IS_NULL( p->in ) )
      return 1;

   return 0;
}

/*** linereader_next() ***/

const char *
linereader_next( struct linereader *p )
{
   varstr_empty( p->text );

   for ( ;; ) {                                  /* loop to consume a single line */

      if ( NULL == fgets( p->buf, _BUFSIZE, p->in ) ) {

         if ( strlen( varstr_str( p->text ) ) == 0 )    /* eof and no text accumulated -- done! */
            return NULL;

         else
            break;
      }

      varstr_cat( p->text, p->buf );

      if ( NULL != strchr( p->buf, '\n' ) )
         break;
   }

   return ( const char * ) varstr_str( p->text );
}

#undef _IS_NULL
#undef _FREE
