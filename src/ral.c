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
    &f_reg_feof,
    &f_reg_ferror,
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
    &f_gz_feof,
    &f_gz_ferror,
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
    NULL,
    NULL,
    &f_lzo_compress,
    &f_lzo_uncompress
};
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
    NULL,
    NULL,
    &f_snappy_compress,
    &f_snappy_uncompress
};
#endif

#ifdef HAVE_BZIP
#include "ral_bzip.h"
static struct file_driver_t ral_driver_bzip = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &f_bzip_compress,
    &f_bzip_uncompress    
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
#ifdef HAVE_BZIP
        case RAL_BZIP:
            ret = &ral_driver_bzip;
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
