#include <stdio.h>
#include <locale.h>
#include "DataParse.h"


int main() {
    setlocale(LC_ALL, "Rus");
    InfoParse("../RaceInfo.txt");
    return 0;
}
