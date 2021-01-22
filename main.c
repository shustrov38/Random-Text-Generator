#include <stdio.h>
#include "btfUtils/beautifier.h"
#include "locale.h"
int main() {
    srand(time(0));
    setlocale(LC_ALL,"Rus");

    FILE *in = fopen("../btfUtils/input.txt", "r");
    BTF_DATA *data;
    data = btfCreateDict();
    btfParseDict(in, data);
}
