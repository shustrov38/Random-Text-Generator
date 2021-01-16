#include <stdio.h>
#include "database.h"
#include "Parse.h"
#include <locale.h>

int main() {
    Dict *dict = createDict();

    parse(dict);
    return EXIT_SUCCESS;
}
