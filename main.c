#include <stdio.h>
#include "database.h"
#include "Parse.h"

int main() {
    Dict *dict = createDict();

    char **a;
    a = (char**) malloc (sizeof(char*) * 10);
    for (int i = 0; i < 10; ++i) {
        a[i] = (char *) malloc(sizeof(char) * 10);
        strcpy(a[i], "kebab");
    }

    Templates t = {a, 10, a, 10, a, 10};
    Entry e = {"Key1", &t};

    int res = rawPut(dict, &e);
    printf("%d\n", res);

    printCollectedData(dict, "Key1");

    return EXIT_SUCCESS;
}
