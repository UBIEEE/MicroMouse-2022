#include "errors.h"

void panic (char * message){
    fprintf("%s", message);
    free(message);
    exit(1);
    return;
}