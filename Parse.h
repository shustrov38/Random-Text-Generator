#ifndef RANDOM_TEXT_GENERATOR_PARSE_H
#define RANDOM_TEXT_GENERATOR_PARSE_H

#include "database.h"

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

void parse(Dict *dict);

#endif //RANDOM_TEXT_GENERATOR_PARSE_H