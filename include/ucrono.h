#ifndef __UCRONO_H__
#define __UCRONO_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdint.h>

#define NUM_RECORDS 16

typedef void (*ucrono_cb_t)(void *);

typedef enum ucrono_cb_style_e
{
    UCRONO_CB_ONCE,
    UCRONO_CB_PERIODIC,
} ucrono_cb_style_t;

typedef struct ucrono_cb_record_s
{
    uint32_t match_ms;
    uint32_t timer_ms;
    uint32_t tick;
    ucrono_cb_t cb;
    void *args;
    ucrono_cb_style_t style;
    uint8_t active;
    void *next;
} ucrono_cb_record_t;

typedef struct ucrono_s
{
    ucrono_cb_record_t *list;
    ucrono_cb_record_t records[NUM_RECORDS];
    uint32_t ticks_per_ms;
} ucrono_t;

void ucrono_sinit ( ucrono_t *ucrono, uint32_t ticks_per_ms );
uint32_t ucrono_tick ( ucrono_t *ucrono );
uint8_t ucrono_once_ms ( ucrono_t *ucrono, ucrono_cb_t cb, uint32_t period, void *args );
uint8_t ucrono_attach_ms ( ucrono_t *ucrono, ucrono_cb_t cb, uint32_t period, void *args );

#if defined(__cplusplus)
}
#endif

#endif
