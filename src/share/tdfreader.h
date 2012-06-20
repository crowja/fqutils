/**
 *  @file tdfreader.h
 *  @brief FIXME
 *  @details FIXME
 */

#ifndef _TDFREADER_H_
#define _TDFREADER_H_

struct tdfreader;

/**
 *
 *  @brief Create and return a new tdfreader object
 *  @details FIXME longer description here ...
 */

struct tdfreader *tdfreader_new( void );

/**
 *
 *  @brief Clean up and free a tdfreader structure
 *  @details FIXME longer description here ...
 */

void        tdfreader_free( struct tdfreader *p );

/**
 *
 *  @brief Return the version of this package
 *  @details FIXME longer description here ...
 */

const char *tdfreader_version( void );

/**
 *
 *  @brief Initialize a tdfreader object
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a tdfreader object
 *
 *  @param x FIXME
 */

int         tdfreader_init( struct tdfreader *p, void *x );


/**
 *
 *  @brief Read the next record.
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a tdfreader object
 *
 *  @param x FIXME
 */

int         tdfreader_next( struct tdfreader *p, char **list );

#endif
