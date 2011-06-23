#include "ral.h"
#include <stddef.h>

#ifdef RAL_STDC
#include "ral_stdc.h"
static struct file_driver_t ral_driver_stdc = {
    &f_reg_open,
    &f_reg_close,
    &f_reg_seek,
    &f_reg_tell,
    &f_reg_read,
    &f_reg_write,
    NULL,
    NULL
};
#endif


struct file_driver_t *getDriver(enum drivers_t d){
    struct file_driver_t *ret;
    switch(d){
#ifdef RAL_STDC
        case STDZC:
            ret = &ral_driver_stdc;
            break;
#endif
        default:
            ret = NULL;
            break;
    }
    return ret;
}

