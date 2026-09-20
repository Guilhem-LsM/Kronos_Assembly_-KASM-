#include <stdio.h>
#include "SayHelloWorld.h"

int main(int argc, char **argv)
{   
    while(--argc > 0)
    {
    printf("%s", argv[argc]);
    }
    return 0;
}