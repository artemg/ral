#include "ral_snappy.h"
#include <snappy-c.h>

#include <stdio.h>

enum ral_status f_snappy_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param){
    enum ral_status ret;
    snappy_status res = snappy_compress(source, sourceLen, dest, destLen);
    switch (res){
        case SNAPPY_OK:
            ret = RAL_OK;
            break;
        case SNAPPY_BUFFER_TOO_SMALL:
            ret = RAL_EBUFFER_TOO_SMALL;
            break;
        default:
            ret = RAL_EUNKNOWN;
            break;
    }
    return ret;
}

enum ral_status f_snappy_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param){
    enum ral_status ret;
    snappy_status res = snappy_uncompress(source, sourceLen, dest, destLen);
    switch (res){
        case SNAPPY_OK:
            ret = RAL_OK;
            break;
        case SNAPPY_BUFFER_TOO_SMALL:
            ret = RAL_EBUFFER_TOO_SMALL;
            break;
        case SNAPPY_INVALID_INPUT:
            ret = RAL_EINVALID_INPUT;
            break;
        default:
            ret = RAL_EUNKNOWN;
            break;
    }
    return ret;
}

