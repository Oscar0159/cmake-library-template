#include<stdio.h>
#include<stdlib.h>

#include "hello_world.h"

int main(int argc, char **argv)
{
    char* str = hello_world();
    printf("%s\n", str);
    return EXIT_SUCCESS;
}