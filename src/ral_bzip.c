#include "ral_bzip.h"
#include <bzlib.h>

enum ral_status f_bzip_compress(char *dest, size_t *destLen,
const char *source, size_t sourceLen, void *param){
    enum ral_status ret;
    static const int default_blockSize100k = 5;
    static const int default_verbosity     = 0;
    static const int default_workFactor    = 0;
    int res = BZ2_bzBuffToBuffCompress(dest, (unsigned int *)destLen, (char *)source, sourceLen,
        default_blockSize100k, default_verbosity, default_workFactor);
    switch (res){
        case BZ_OK:
            ret = RAL_OK;
            break;
        case BZ_OUTBUFF_FULL:
            ret = RAL_EBUFFER_TOO_SMALL;
            break;
        case BZ_MEM_ERROR:
            ret = RAL_ENOT_ENOUGH_MEM;
            break;
        case BZ_CONFIG_ERROR:
        case BZ_PARAM_ERROR:
        default:
            ret = RAL_EUNKNOWN;
            break;
    };
    return ret;
}

enum ral_status f_bzip_uncompress(char *dest, size_t *destLen,
    const char *source, size_t sourceLen, void *param)
{
    enum ral_status ret;
    static const int default_verbosity     = 0;
    static const int default_small         = 0;
    int res = BZ2_bzBuffToBuffDecompress(dest, (unsigned int *)destLen, (char *)source, sourceLen,
        default_small, default_verbosity);
    switch (res){
        case BZ_OK:
            ret = RAL_OK;
            break;
        case BZ_OUTBUFF_FULL:
            ret = RAL_EBUFFER_TOO_SMALL;
            break;
        case BZ_MEM_ERROR:
            ret = RAL_ENOT_ENOUGH_MEM;
            break;
        case BZ_DATA_ERROR:
        case BZ_DATA_ERROR_MAGIC:
        case BZ_UNEXPECTED_EOF:
            ret = RAL_EINVALID_INPUT;
            break;
        case BZ_CONFIG_ERROR:
        case BZ_PARAM_ERROR:
        default:
            ret = RAL_EUNKNOWN;
            break;
    };
    return ret;
}


