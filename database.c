#include <malloc.h>
#include "database.h"


Dict *createDict() {
    Dict *dict = (Dict*)malloc(sizeof(Dict));
    dict->capacity = 1;
    dict->size = 0;
    dict->data = (Entry**)malloc(sizeof(Entry*) * dict->capacity);
    return dict;
}
