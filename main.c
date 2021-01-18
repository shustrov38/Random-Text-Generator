#include <stdio.h>
#include "beautifier.h"
#include <locale.h>
int main() {

    FILE *in = fopen("../input.txt", "r");
    DATA *data;
    data = createData();
    parse(in, data);
//    printData(data);
    char *q = "#boy\n";
    dictRandGet(data,q,"adj");
    dictRandGet(data,q,"syn");
}
