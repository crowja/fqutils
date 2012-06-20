/**
 *  @file varstr.h
 *  @brief FIXME
 *  @details FIXME
 */

#ifndef _VARSTR_H_
#define _VARSTR_H_

struct varstr;

/**
 *
 *  @brief Create and return a new varstr object
 *  @details FIXME longer description here ...
 */

struct varstr      *varstr_new( void );


/**
 *
 *  @brief Clean up and free a varstr structure
 *  @details FIXME longer description here ...
 */

int                 varstr_free( struct varstr *p );

/**
 *
 *  @brief Return the version of this package
 *  @details FIXME longer description here ...
 */

const char         *varstr_version( void );

/**
 *
 *  @brief Concatenate a string to the end of a varstr object.
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a varstr object
 *
 *  @param x FIXME
 */

void                varstr_cat( struct varstr *p, char *x );

/**
 *
 *  @brief Concatenate a character to the end of a varstr object.
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a varstr object
 *
 *  @param x FIXME
 */

void                varstr_catc( struct varstr *p, char x );

/**
 *
 *  @brief Remove whitespace from the end of a varstr object.
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a varstr object
 *
 *  @param x FIXME
 */

void                varstr_chomp( struct varstr *p );

/**
 *
 *  @brief Initialize a varstr object
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a varstr object
 *
 *  @param x FIXME
 */

void                varstr_compact( struct varstr *p );

/**
 *
 *  @brief Initialize a varstr object
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a varstr object
 *
 *  @param x FIXME
 */

void                varstr_empty( struct varstr *p );

/**
 *
 *  @brief Initialize a varstr object
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a varstr object
 *
 *  @param x FIXME
 */

void                varstr_lrtrim( struct varstr *g );

/**
 *
 *  @brief Set the extension size for a varstr object
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a varstr object
 *
 *  @param x FIXME
 */

unsigned            varstr_extend( struct varstr *p, unsigned extend );

/**
 *
 *  @brief Initialize a varstr object
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a varstr object
 *
 *  @param x FIXME
 */

unsigned            varstr_init( struct varstr *p, unsigned extend );

/**
 *
 *  @brief Initialize a varstr object
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a varstr object
 *
 *  @param x FIXME
 */

char               *varstr_str( struct varstr *p );


/**
 *
 *  @brief Initialize a varstr object
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a varstr object
 *
 *  @param x FIXME
 */

char               *varstr_to_s( struct varstr *p );


#endif
