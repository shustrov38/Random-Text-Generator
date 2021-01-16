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

    Templates t = {a, a, a};
    Entry e = {"Key1", &t};

    int res = raw_put(dict, &e);
    printf("%d\n", res);

    printf("%s", dict->data[0]->key);

    return EXIT_SUCCESS;
}
