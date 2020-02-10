#include <stdio.h>
#include "ucrono.h"
#include "utlist.h"

void record_init_default ( ucrono_cb_record_t *record );
uint8_t record_insert ( ucrono_t *ucrono, ucrono_cb_t cb, uint32_t period, void *args);
uint8_t record_register_available ( ucrono_t *ucrono );
uint8_t record_unregister_index ( ucrono_t *ucrono, uint8_t index );

void ucrono_sinit ( ucrono_t *ucrono, uint32_t ticks_per_ms )
{
    ucrono->ticks_per_ms = ticks_per_ms;
    ucrono->list = NULL;
}

uint32_t ucrono_tick ( ucrono_t *ucrono )
{
    ucrono_cb_record_t *rec, *temp;
    LL_FOREACH_SAFE(ucrono->list, rec, temp)
    {
        rec->tick++;
        if ( rec->tick >= ucrono->ticks_per_ms)
        {
            rec->tick = 0;
            rec->timer_ms++;
            if ( rec->timer_ms >= rec->match_ms )
            {
                rec->timer_ms = 0;

                // TODO: move tick cb to a fifo in a process loop
                rec->cb(rec->args);

                if ( rec->style == UCRONO_CB_ONCE )
                {
                    rec->active = 0;
                    LL_DELETE(ucrono->list, rec);
                }
            }
        }
    }

    return 0;
}

uint8_t ucrono_once_ms ( ucrono_t *ucrono, ucrono_cb_t cb, uint32_t period, void *args )
{
    uint8_t index = record_insert(ucrono, cb, period, args);
    if ( index )
    {
        ucrono->records[index].style = UCRONO_CB_ONCE;
    }

    return 0;
}

uint8_t ucrono_attach_ms ( ucrono_t *ucrono, ucrono_cb_t cb, uint32_t period, void *args )
{
    uint8_t index = record_insert(ucrono, cb, period, args);
    if ( index )
    {
        ucrono->records[index].style = UCRONO_CB_PERIODIC;
    }

    return 0;
}

uint8_t record_insert ( ucrono_t *ucrono, ucrono_cb_t cb, uint32_t period, void *args )
{
    uint8_t retval = 0;

    uint8_t index = record_register_available(ucrono);
    if ( index != NUM_RECORDS )
    {
        record_init_default(&ucrono->records[index]);
        ucrono->records[index].match_ms = period;
        ucrono->records[index].cb = cb;
        ucrono->records[index].args = args;
        LL_APPEND(ucrono->list, &ucrono->records[index]);
        retval = index;
    }

    return retval;
}

void record_init_default ( ucrono_cb_record_t *record )
{
    record->match_ms = 0;
    record->timer_ms = 0;
    record->tick = 0;
    record->cb = NULL;
    record->args = NULL;
    record->style = UCRONO_CB_PERIODIC;
    record->next = NULL;
}

uint8_t record_register_available ( ucrono_t *ucrono )
{
    uint8_t index = 0;
    for ( index = 0; index < NUM_RECORDS; index++ )
    {
        if ( ucrono->records[index].active == 0 )
        {
            ucrono->records[index].active = 1;
            return index;
        }
    }

    // Array full
    return NUM_RECORDS;
}

uint8_t record_unregister_index ( ucrono_t *ucrono, uint8_t index )
{
    return 0;
}
