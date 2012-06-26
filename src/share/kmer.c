#include <stdlib.h>
#include <string.h>
#include "kmer.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)              ((NULL == (p)) ? (1) : (0))

int
kmer_hash( unsigned k, char *s, unsigned *hash )
{
   unsigned    i;
   unsigned    sum = 0;

   for ( i = 0; i < k; i++ ) {

      unsigned    offset;

      switch ( s[i] ) {

         case 'A':
         case 'a':
            offset = 0;
            break;

         case 'C':
         case 'c':
            offset = 1;
            break;

         case 'G':
         case 'g':
            offset = 2;
            break;

         case 'T':
         case 't':
         case 'U':
         case 'u':
            offset = 3;
            break;

         default:
            return 1;                            /* fail */
      }

      sum += offset + 4 * sum;
   }

   *hash = sum;

   return 0;
}

int
kmer_unhash( void )
{
   return 0;
}

#undef _IS_NULL
