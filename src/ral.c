#include "ral.h"
#include <stddef.h>

#ifdef HAVE_STDC
#include "ral_stdc.h"
static struct file_driver_t ral_driver_stdc = {
    &f_reg_open,
    &f_reg_close,
    &f_reg_seek,
    &f_reg_tell,
    &f_reg_read,
    &f_reg_write,
    &f_reg_compress,
    &f_reg_uncompress
};
#endif

#ifdef HAVE_GZ
#include "ral_gz.h"
static struct file_driver_t ral_driver_gz = {
    &f_gz_open,
    &f_gz_close,
    &f_gz_seek,
    &f_gz_tell,
    &f_gz_read,
    &f_gz_write,
    &f_gz_compress,
    &f_gz_uncompress
};
#endif

#ifdef HAVE_LZO
#include "ral_lzo.h"
static struct file_driver_t ral_driver_lzo = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &f_lzo_compress,
    &f_lzo_uncompress
};
/*
static struct file_driver_t ral_driver_lzo = {
    &f_lzo_open,
    &f_lzo_close,
    &f_lzo_seek,
    &f_lzo_tell,
    &f_lzo_read,
    &f_lzo_write,
    &f_lzo_compress,
    &f_lzo_uncompress
};
*/
#endif

#ifdef HAVE_SNAPPY
#include "ral_snappy.h"
// there is no default snappy file format
static struct file_driver_t ral_driver_snappy = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &f_snappy_compress,
    &f_snappy_uncompress
};
#endif

#ifdef HAVE_BZIP2
#include "ral_bzip2.h"
static struct file_driver_t ral_driver_bzip2 = {
    &f_bzip2_open,
    &f_bzip2_close,
    &f_bzop2_seek,
    &f_bzip2_tell,
    &f_bzip2_read,
    &f_bzip2_write,
    &f_bzip2_compress,
    &f_bzip2_uncompress    
};
#endif

struct file_driver_t *get_driver(enum drivers_t d){
    struct file_driver_t *ret;
    switch(d){
#ifdef HAVE_STDC
        case RAL_STDC:
            ret = &ral_driver_stdc;
            break;
#endif
#ifdef HAVE_GZ
        case RAL_GZ:
            ret = &ral_driver_gz;
            break;
#endif
#ifdef HAVE_LZO
        case RAL_LZO:
            ret = &ral_driver_lzo;
            break;
#endif
#ifdef HAVE_SNAPPY
        case RAL_SNAPPY:
            ret = &ral_driver_snappy;
            break;
#endif
#ifdef HAVE_BZIP2
        case RAL_BZIP2:
            ret = &ral_driver_bzip2;
            break;
#endif
        default:
            ret = NULL;
            break;
    }
    return ret;
}

const char *get_driver_name(enum drivers_t id){
    if( id >= RAL_END ){
        return driver_names[RAL_END];
    } else {
        return driver_names[id];
    }
}
