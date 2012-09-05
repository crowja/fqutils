#ifndef _TOKENSET_H_
#define _TOKENSET_H_

struct tokenset;

/** \brief Constructor; create and return a new tokenset object
 */

struct tokenset *tokenset_new( void );

/** \brief Clean up and free a tokenset structure
 *
 *  @param p Pointer to a tokenset object
 */

void        tokenset_free( struct tokenset *p );

/** \brief Brief info on what this does to a tokenset object
 *
 *  @param p Pointer to a tokenset object
 *  @param x Magic info
 */

int         tokenset_add( struct tokenset *p, char *n );

/** \brief Clean up and free a tokenset structure
 *
 *  @param p Pointer to a tokenset object
 */

int         tokenset_count( struct tokenset *p );

/** \brief Clean up and free a tokenset structure
 *
 *  @param p Pointer to a tokenset object
 */

char      **tokenset_get( struct tokenset *p );

/** \brief Brief info on what this does to a tokenset object
 *
 *  @param p Pointer to a tokenset object
 *  @param x Magic info
 */

int         tokenset_exists( struct tokenset *p, char *n );

/** \brief Brief info on what this does to a tokenset object
 *
 *  @param p Pointer to a tokenset object
 *  @param x Magic info
 */

void        tokenset_remove( struct tokenset *p, char *n );

/** \brief Clean up and free a tokenset structure
 *
 *  @param p Pointer to a tokenset object
 */

void        tokenset_reset( struct tokenset *p );

/** \brief Clean up and free a tokenset structure
 *
 *  @param p Pointer to a tokenset object
 */

void        tokenset_sort( struct tokenset *p );


/** \brief Return the version of this package
 */

const char *tokenset_version( void );

const char *tokenset_get_by_id( struct tokenset *p, unsigned id );

#endif
