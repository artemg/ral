#ifndef RAL_BZIP_H
#define RAL_BZIP_H

#include "ral.h"
enum ral_status f_bzip_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param);
enum ral_status f_bzip_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param);

#endif

