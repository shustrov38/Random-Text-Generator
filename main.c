#include <locale.h>
#include "db_utils/database.h"

int main() {
    unsigned seed = time(0);
    srand(seed);

    setlocale(LC_ALL, "Russian");

    TemplateDictionary *dict = createTemplateDictionary();
    loadTemplateDictionary("../db_utils/database.txt", dict, 0);

    char *s = "шкаф";
    printf("%s -> %s\n", s, getRandomValueFromTemplateDictionary(dict, s, PREFIX));

    return EXIT_SUCCESS;
}
