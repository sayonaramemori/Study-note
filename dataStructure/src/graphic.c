#include "myhead.h"
#include<stdbool.h>

typedef struct record{
    char *point;
    int index;
    bool used;
}record;

typedef struct graphic{
    bool **edge;
    int number;
    record *msg;
}graphic;



