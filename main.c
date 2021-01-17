#include <stdio.h>
#include "beautifier.h"

int main()
{
    FILE* in = fopen("input.txt", "r");
    DATA *data;
    *data=create_data();
    parse(in, data);
    print_data(data);
}
