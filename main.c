#include <stdio.h>
#include "beautifier.h"
#include <locale.h>
int main() {

    FILE *in = fopen("../input.txt", "r");
    DATA *data;
    data = createData();
    parse(in, data);
//    printData(data);
    char *q = "boy";
    printf("%s\n", dictRandGet(data,q,"adj"));
    printf("%s", dictRandGet(data,q,"syn"));
}
