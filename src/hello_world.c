#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hello_world.h"
#include "foo.h"

char* hello_world()
{
    return "Hello, world!";
}

char* hello_world_foo()
{
    char* foo_str = foo();
    char* hello_world_str = hello_world();
    char* hello_world_foo_str = malloc(strlen(hello_world_str) + strlen(foo_str) + 2);
    strcpy(hello_world_foo_str, hello_world_str);
    strcat(hello_world_foo_str, " ");
    strcat(hello_world_foo_str, foo_str);
    return hello_world_foo_str;
}