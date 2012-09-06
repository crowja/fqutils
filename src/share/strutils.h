/**
 *  @file strutils.h
 *  @brief Provides a number of string handling helpers.
 *  @details FIXME
 */

#ifndef _STRUTILS_H_
#define _STRUTILS_H_

/**
 *  @brief Remove trailing newlines from a string.
 *  @details In-place removal of trailing newlines from a string, mimicking
 *  Perl's chomp().
 */

char       *stru_chomp( char *cp );


/**
 *  @brief Remove whitespace from a string.
 *  @details In-place removal of all whitespace from a string.
 */

char       *stru_crush( char *cp );


/**
 *  @brief Test if a string is completely whitespace.
 *  @details Return 1 or 0, respectively, depending on whether or not a string
    is completely whitespace.
 */

unsigned    stru_is_ws( char *str );


/**
 *  @brief Concatenate two strings.
 *  @details Replace str1 with the concatenation of two strings, str1 and str2.
 */

char       *stru_lcat( char **str1, char **str2 );


/**
 *  @brief Split a string.
 *  @details Return a NULL-terminated list of strings obtained by splitting string
 *  str on the delimiter delim. Single- and double-quoted protection of delimiters
 *  is supported.
 */

char      **stru_split( char delim, char *str );

unsigned    stru_splitpp( char delim, char *str, char **list );


/**
 *  @brief Convert a string to lower-case.
 *  @details In-place conversion of a string to lower-case.
 */

char       *stru_tolower( char *cp );


/**
 *  @brief Convert a string to upper-case.
 *  @details In-place conversion of a string to upper-case.
 */

char       *stru_toupper( char *cp );


/**
 *  @brief Remove leading and trailing whitespace.
 *  @details In-place removal of leading and trailing whitespace
 *  from a string.
 */

char       *stru_trim( char *cp );


/**
 *  @brief Return the version string.
 *  @details Return the version of the strutils package.
 */

const char *stru_version( void );


#endif
