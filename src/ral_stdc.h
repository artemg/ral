#ifndef RAL_STDC_H
#define RAL_STDC_H

#include "ral.h"
fd_t *f_reg_open(const char *fname, int mode, void *params);
int    f_reg_close(fd_t *fd);
off_t  f_reg_seek(fd_t *fd, size_t offset, enum file_driver_seek_modes whence);
off_t  f_reg_tell(fd_t *fd);
size_t f_reg_read(fd_t *fd, char *buf, size_t size);
size_t f_reg_write(fd_t *fd, char *buf, size_t size);
int    f_reg_feof(fd_t *fd);
int    f_reg_ferror(fd_t *fd);
enum ral_status f_reg_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param);
#define f_reg_uncompress f_reg_compress

#endif

