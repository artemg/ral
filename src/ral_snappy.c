#include "ral_snappy.h"
#include <snappy-c.h>

#include <stdio.h>

enum ral_status f_snappy_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen){
    snappy_status ret = snappy_compress(source, sourceLen, dest, destLen);
    if( ret == SNAPPY_OK ){
        return RAL_OK;
    } else {
        fprintf(stderr, "SNAPPY: %d\n", ret);
        return RAL_ERROR;
    }
}

enum ral_status f_snappy_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen){
    if( snappy_uncompress(source, sourceLen, dest, destLen) == SNAPPY_OK ){
        return RAL_OK;
    } else {
        return RAL_ERROR;
    }
}

