#include <stdio.h>
#include "beautifier.h"
#include "locale.h"
int main() {
    srand(time(0));
    setlocale(LC_ALL,"Rus");

    FILE *in = fopen("../input.txt", "r");
    DATA *data;
    data = createBtfDict();
    parseBtfDict(in, data);
//    printBtfDict(data);
    char *q = "#boy";
    getRandBtfDictValue(data,q,SYNONYM);
    getRandBtfDictValue(data,q,ADJECTIVE);
}
