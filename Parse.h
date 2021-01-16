#ifndef RANDOM_TEXT_GENERATOR_PARSE_H
#define RANDOM_TEXT_GENERATOR_PARSE_H

#include "database.h"

/* WordDataBase
 *
 * #action
 * ##prefix
 * #n (n -кол-во слов)
 * word (xN раз)
 * ##suffix
 * #n (n -кол-во слов)
 * word (xN раз)
 * ##postfix
 * n (n -кол-во слов)
 * word (xN раз)
 *
 */

void parse(Dict *dict);

#endif //RANDOM_TEXT_GENERATOR_PARSE_H