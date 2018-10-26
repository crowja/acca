#ifndef _TOKENSET_H_
#define _TOKENSET_H_

/**
 *  @brief Tokenset.
 *  @details A tokenset is a collection of unique strings (tokens).
 *  As a token is added it is assigned an integer identifier.
 *  The motivation is a situation in which text is being lexed
 *  into words and we want to keep track of the unique words,
 *  assigning unsigned integer identifiers to each. A tokenset
 *  can have tokens added to or removed from it.
 */

struct tokenset;

/**
 *  @brief Constructor. Create and return a new tokenset object.
 *  @details Constructor for tokenset objects.
 *  @returns On success a pointer to the new tokenset object, the
 *  NULL pointer otherwise. 
 */

struct tokenset *tokenset_new(void);

/**
 *  @brief Destructor.
 *  @details Clean up a tokenset structure, freeing allocated
 *  memory.
 *  @param[in] p Pointer to a tokenset object
 */

void        tokenset_free(struct tokenset *p);

/**
 *  @brief Adds a string to the tokenset.
 *  @details Adds the string if it isn't already in the tokenset,
 *  otherwise does nothing.
 *  @param[in] p Pointer to a tokenset object
 *  @param[in] n Pointer to a string to add.
 *  @returns Whether added or not the unsigned integer id associated
 *  with the token is returned.
 */

int         tokenset_add(struct tokenset *p, char *n);

/**
 *  @brief Number of tokens added to the tokenset.
 *  @details This provides the count of the FIXME
 *  @param p Pointer to a tokenset object
 *  @returns TODO
 */

int         tokenset_count(struct tokenset *p);

/** 
 *  @brief Brief info on what this does to a tokenset object
 *  @details TODO
 *  @param p Pointer to a tokenset object
 *  @param x Magic info
 *  @returns TODO
 */

int         tokenset_exists(struct tokenset *p, char *n);

/**
 *  @brief Clean up and free a tokenset structure
 *  @details TODO
 *  @param p Pointer to a tokenset object
 *  @returns TODO
 */

char      **tokenset_get(struct tokenset *p);

/**
 *  @brief Clean up and free a tokenset structure
 *  @details TODO
 *  @param p Pointer to a tokenset object
 *  @returns TODO
 */

const char *tokenset_get_by_id(struct tokenset *p, unsigned id);

/**
 *  @brief Brief info on what this does to a tokenset object
 *  @details TODO
 *  @param p Pointer to a tokenset object
 *  @param x Magic info
 *  @returns TODO
 */

void        tokenset_remove(struct tokenset *p, char *n);

/**
 *  @brief Brief info on what this does to a tokenset object
 *  @details TODO
 *  @param p Pointer to a tokenset object
 *  @param x Magic info
 *  @returns TODO
 */

int         tokenset_id(struct tokenset *p, char *n);


/**
 *  @brief Clean up and free a tokenset structure
 *  @details TODO
 *  @param p Pointer to a tokenset object
 *  @returns TODO
 */

void        tokenset_reset(struct tokenset *p);

/**
 *  @brief Clean up and free a tokenset structure
 *  @details TODO
 *  @param p Pointer to a tokenset object
 *  @returns TODO
 */

void        tokenset_sort(struct tokenset *p);


/**
 *  @brief Return the version of this package
 *  @details TODO
 *  @returns TODO
 */

const char *tokenset_version(void);

#endif
