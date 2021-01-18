#include <stdio.h>
#include "beautifier.h"

int main() {
    FILE *in = fopen("../input.txt", "r");
    DATA *data;
    data = createData();
    parse(in, data);
    printData(data);
}
