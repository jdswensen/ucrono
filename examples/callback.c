#include <stdio.h>
#include <time.h>
#include "ucrono.h"

uint8_t counter = 0;

void cb (void *args)
{
    counter++;
    printf("cb: %d\n", counter);
}

void once (void *args)
{
    printf("once\n");
}

void main ( void )
{
    ucrono_t ucrono;
    ucrono_sinit(&ucrono, 1);
    ucrono_attach_ms(&ucrono, cb, 5, NULL);
    ucrono_once_ms(&ucrono, once, 10, NULL);

    struct timespec delay = { 0, 500000 };

    uint32_t index = 0;
    for ( index = 0; index < 30; index++)
    {
        ucrono_tick(&ucrono);
        nanosleep(&delay, &delay);
    }
}
