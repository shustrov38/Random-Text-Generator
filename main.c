#include <stdio.h>
#include <locale.h>
#include "db_utils/database.h"
#include "db_utils/parse.h"

int main() {
    Dict *dict = createDict();
    parse("../db_utils/DataBase.txt", dict);
    return EXIT_SUCCESS;
}
