#include <stdio.h>
#include "SayHelloWorld.h"

int main(int argc, char **argv)
{   
    char argument[] = argv[1];
    printf("%s", argument);
    return 0;
}