#include <stdint.h>
#include <stdio.h>
#include "logs.h"

void foo(int whatever);

int main(void)
{
    printf("Hello world!\n");
    LOG_INFO("We are starting!");
    LOG_EVENT("This is an event!");
    LOG_ERROR("This is an error!");

    foo(10);

    return 0;
}

void foo(int whatever)
{
    LOG_INFO("This is some info: %d", whatever);
    LOG_EVENT("This is an event: %d", whatever *2);
    LOG_ERROR("This is an error: %.3f", (whatever / 1.73));
}