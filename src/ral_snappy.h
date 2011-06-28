#ifndef RAL_SNAPPY_H
#define RAL_SNAPPY_H

#include "ral.h"
enum ral_status f_snappy_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen);
enum ral_status f_snappy_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen);

#endif

