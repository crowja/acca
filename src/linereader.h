/**
 *  @file linereader.h
 *  @version 0.2.0-dev0
 *  @date Fri Dec  6 09:54:07 CST 2019
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#ifndef _LINEREADER_H_
#define _LINEREADER_H_

struct linereader;

/**
 *
 *  @brief Create and return a new linereader object
 *  @details FIXME longer description here ...
 */

struct linereader *linereader_new(void);

/**
 *
 *  @brief Clean up and free a linereader structure
 *  @details FIXME longer description here ...
 */

void        linereader_free(struct linereader **pp);

/**
 *
 *  @brief Return the version of this package
 *  @details FIXME longer description here ...
 */

const char *linereader_version(void);

/**
 *
 *  @brief Initialize a linereader object
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a linereader object
 *
 *  @param x FIXME
 */

int
            linereader_init(struct linereader *p, char *fname);

/**
 *
 *  @brief Return the next line of text pointed at by the linereader object.
 *  @details FIXME longer description here ...
 *
 *  @param p Pointer to a linereader object
 *
 *  @param x FIXME
 */

const char *linereader_next(struct linereader *p);


#endif
