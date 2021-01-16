#ifndef RANDOM_TEXT_GENERATOR_PARSE_H
#define RANDOM_TEXT_GENERATOR_PARSE_H


#include <string.h>
#include <stdio.h>
#include "database.h"

#define MAX_STR_LEN 100
#define MAX_ARR_LEN 100

/* WordDataBase
 *
 * #action
 * ##prefix
 * word (xN раз)
 * --
 * ##suffix
 * word (xN раз)
 * --
 * ##postfix
 * word (xN раз)
 *--
 */

int parse(char *filename, Dict *dict);


#endif //RANDOM_TEXT_GENERATOR_PARSE_H