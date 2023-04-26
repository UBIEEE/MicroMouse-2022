#include "test.h"

// Stores the testing flags for reference in the functions
extern flags *flag;

void callTestHelpers();

int main(int argc, char *argv[]) {

    /****************************
    * Flag setter initialization
    * ***************************/
    flag = (flags*)malloc(sizeof(flags));

    ++argv, --argc;
    if (argc < 2 && !strcmp(argv[0],"--help")){
        fprintf(stderr, "not enough arguments, please invoke the compiler with -help");
        return 1;
    }
    char *fileName;
    
    for (int i = 0; i <argc; i++){
        char* arg = argv[i];
        fileName = argv[argc-1];
        if (strcmp(arg, "-test1") == 0){ // Generate tokens based on char stream
            flag -> helpers = true;
            continue;

        // EXAMPLE of how to add program flags
        // }if (strcmp(arg, "-st") == 0){ // Symbol table description
        //     flag -> st =true;
        //     continue;
        // }
    }
    if (flag->helpers){ callTestHelpers();}
    
}

void callTestHelpers(){

    return; 
}