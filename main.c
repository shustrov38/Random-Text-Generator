#include <locale.h>
#include "db_utils/database.h"

int main() {
    setlocale(LC_ALL, "Russian");
    Dict *dict = createDict();
    loadDict("../db_utils/database.txt", dict, 1);
    return EXIT_SUCCESS;
}
