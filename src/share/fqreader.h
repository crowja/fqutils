/**
 *  @file fqreader.h
 *  @brief FIXME
 *  @details FIXME
 */

#ifndef _FQREADER_H_
#define _FQREADER_H_

#ifdef  _PACKAGE_NAME
#undef  _PACKAGE_NAME
#endif
#define _PACKAGE_NAME "fqreader"

struct fqreader;

/**
 *
 *  @brief Create and return a new fqreader object.
 *  @details FIXME longer description here ...
 */

struct fqreader *fqreader_new( char *fname );

/**
 *
 *  @brief Clean up and free a fqreader structure.
 *  @details FIXME longer description here ...
 */

void        fqreader_free( struct fqreader *p );

/**
 *
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */

const char *fqreader_version( void );

/**
 *
 *  @brief Initialize a fqreader object.
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a fqreader object
 *
 *  @param x FIXME
 */

int         fqreader_init( struct fqreader *p, unsigned extend );

/**
 *  @brief Reads the next fastq record
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a fqreader object
 *
 *  @param x FIXME
 */

int         fqreader_next( struct fqreader *p, char **h1, char **h2, char **s, char **q );

#endif
