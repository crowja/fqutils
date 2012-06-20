#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fqreader.h"
#include "varstr.h"
#include "zlib.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

#ifdef  _FATAL
#undef  _FATAL
#endif
#define _FATAL(fmt, msg, code) do { fprintf( stderr, (fmt), (msg) ); exit( code ); } while( 0 )

static const char version[] = "20120404";

struct fqreader {
   struct varstr *h1;
   struct varstr *h2;
   struct varstr *s;
   struct varstr *q;
   gzFile      in;
};


/*** fqreader_new() ***/

struct fqreader *fqreader_new( char *fname )
{
   struct fqreader *tp;

   tp = ( struct fqreader * ) malloc( sizeof ( struct fqreader ) );
   if ( _IS_NULL( tp ) )
      return NULL;

   if ( _IS_NULL( fname ) )
      tp->in = gzdopen( fileno( stdin ), "r" );

   else
      tp->in = gzopen( fname, "r" );

   gzbuffer( tp->in, 1024 * 32 );                /* requires at least zlib-1.2.4 */

   tp->h1 = varstr_new(  );
   tp->h2 = varstr_new(  );
   tp->s = varstr_new(  );
   tp->q = varstr_new(  );

   return tp;
}


/*** fqreader_free() ***/

void fqreader_free( struct fqreader *p )
{
   gzclose( p->in );
   varstr_free( p->h1 );
   varstr_free( p->h2 );
   varstr_free( p->s );
   varstr_free( p->q );

   _FREE( p );
}


/*** fqreader_version() ***/

const char *fqreader_version( void )
{
   return version;
}


/*** fqreader_init() ***/

int fqreader_init( struct fqreader *p, unsigned extend )
{
   /* Do some magic here ... */

   return 0;
}


/*** fqreader_next() ***/

int fqreader_next( struct fqreader *p, char **h1, char **h2, char **s, char **q )
{
   unsigned    rc = 1;
   char        c;
   enum states { s_need_h1, s_in_h1, s_in_s, s_in_h2, s_in_q };
   enum states state = s_need_h1;

   varstr_empty( p->h1 );
   varstr_empty( p->h2 );
   varstr_empty( p->s );
   varstr_empty( p->q );

   while ( ( c = gzgetc( p->in ) ) > 0 ) {

      switch ( state ) {

         case s_need_h1:
            if ( isspace( c ) )
               continue;
            else if ( c == '@' )
               state = s_in_h1;
            else
               exit( 1 );
            break;

         case s_in_h1:
            if ( c == '\n' )
               state = s_in_s;
            else
               varstr_catc( p->h1, c );
            break;

         case s_in_s:
            if ( isspace( c ) )
               continue;
            else if ( c == '+' )
               state = s_in_h2;
            else
               varstr_catc( p->s, c );
            break;

         case s_in_h2:
            if ( c == '\n' )
               state = s_in_q;
            else
               varstr_catc( p->h2, c );
            break;

         case s_in_q:
            if ( isspace( c ) )
               continue;
            else if ( strlen( varstr_str( p->s ) ) > 1 + strlen( varstr_str( p->q ) ) )
               varstr_catc( p->q, c );
            else {
               varstr_catc( p->q, c );
               goto DONE;
            }
            break;
      }
   }

   rc = 0;

 DONE:

   *h1 = varstr_str( p->h1 );
   *h2 = varstr_str( p->h2 );
   *s = varstr_str( p->s );
   *q = varstr_str( p->q );

   return rc;
}

#undef _IS_NULL
#undef _FREE
#undef _FATAL
