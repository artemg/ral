#ifndef RAL_STDC_H
#define RAL_STDC_H

#include "ral.h"
fd_t *f_reg_open(const char *fname, int mode, void *params);
int    f_reg_close(fd_t *fd);
off_t  f_reg_seek(fd_t *fd, size_t offset, int whence);
off_t  f_reg_tell(fd_t *fd);
size_t f_reg_read(fd_t *fd, char *buf, size_t size);
size_t f_reg_write(fd_t *fd, char *buf, size_t size);
enum ral_status f_reg_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen);
//int f_reg_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen);
#define f_reg_uncompress f_reg_compress
//typedef f_reg_compress f_reg_uncompress

#endif

