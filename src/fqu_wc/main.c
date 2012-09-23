#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "options.h"
#include "fqreader.h"
#include "tokenset.h"
#include "strutils.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)              ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)                 ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

struct _wc_count {
   unsigned    id;
   unsigned    count;
};

static unsigned countlist_size = 0;
static unsigned countlist_extend = 4 * 1024;
static struct _wc_count *countlist = NULL;
static struct tokenset *words;
static char *word = NULL;

static void
_resize( unsigned min )
{
   unsigned    i;
   unsigned    need = min + countlist_extend;

   /* printf("DEBUG: %d\t%d\t%d\n", min, need, sizeof ( struct _wc_count ) * need); */

   countlist = realloc( countlist, sizeof ( struct _wc_count ) * need );

   if ( _IS_NULL( countlist ) ) {
      fprintf( stderr, "[ERROR] %s: Cannot allocate sufficient memory for count table.\n", _I_AM );
      exit( 1 );
   }

   for ( i = countlist_size; i < need; i++ ) {
      /* printf("DEBUG2: %d\n", i); */
      countlist[i].id = i;
      countlist[i].count = 0;
   }

   countlist_size = need;
}

static void
_update_table( unsigned word_size, char *str )
{
   unsigned    i;

   if ( _IS_NULL( str ) )
      return;

   for ( i = 0; i < 1 + strlen( str ) - word_size; i++ ) {
      unsigned    id;
      strncpy( word, str + i, word_size );       /* word <- substring */
      word[word_size] = '\0';
      if ( strspn( word, "ACGRSTUWY" ) < word_size )
         continue;
      id = tokenset_add( words, word );

      if ( id >= countlist_size )
         _resize( id );                          /* increases countlist_size */

      countlist[id].id = id;
      countlist[id].count += 1;
   }
}

/*** main() ***/

int
main( int argc, char *argv[] )
{
   char       *h1, *h2, *s, *q;
   unsigned    i;
   unsigned    n;
   struct options *o = options_new(  );
   struct fqreader *z;
   /* printf("HERE3\n"); */

   /* Get the command line options */
   options_cmdline( o, argc, argv );
   /*printf("HERE4\n"); */

   words = tokenset_new(  );
   /* printf("HERE5\n"); */
   word = realloc( word, sizeof ( char ) * ( 1 + o->word_size ) );
   /* printf("HERE6\n"); */

   if ( o->optind == argc ) {                    /* read from stdin */

      z = fqreader_new( NULL );

      while ( fqreader_next( z, &h1, &h2, &s, &q ) ) {
         stru_toupper( s );
         _update_table( o->word_size, s );
      }

      fqreader_free( z );
   }

   else {                                        /* read from input files */
      int         k;

      /* printf("HERE2\n"); */
      for ( k = o->optind; k < argc; k++ ) {

         z = fqreader_new( argv[k] );

         if ( _IS_NULL( z ) ) {
            fprintf( stderr, "[ERROR] %s: Cannot open input file \"%s\"\n", _I_AM, argv[k] );
            exit( 1 );
         }

         while ( fqreader_next( z, &h1, &h2, &s, &q ) ) {
            stru_toupper( s );
            _update_table( o->word_size, s );
         }

         fqreader_free( z );
      }
   }

   /* Sort the countlist */

   n = tokenset_count( words );
   for ( i = 0; i < n; i++ ) {
      if ( countlist[i].count < o->min_count )
         continue;
      printf( "%s\t%d\n", tokenset_get_by_id( words, countlist[i].id ), countlist[i].count );
   }

   options_free( o );
   tokenset_free( words );
   _FREE( word );
   _FREE( countlist );

   return 0;
}

#undef _IS_NULL
#undef _FREE
