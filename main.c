#include <stdio.h>
#include "database.h"
#include "Parse.h"
#include <locale.h>

int main() {
    Dict *dict = createDict();

    parse("../DataBase.txt", dict);
    return EXIT_SUCCESS;
}
