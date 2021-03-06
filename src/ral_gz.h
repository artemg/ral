#ifndef RAL_GZ_H
#define RAL_GZ_H

#include "ral.h"
fd_t *f_gz_open(const char *fname, int mode, void *params);
int    f_gz_close(fd_t *fd);
off_t  f_gz_seek(fd_t *fd, size_t offset, enum file_driver_seek_modes whence);
off_t  f_gz_tell(fd_t *fd);
size_t f_gz_read(fd_t *fd, char *buf, size_t size);
size_t f_gz_write(fd_t *fd, char *buf, size_t size);
int    f_gz_feof(fd_t *fd);
int    f_gz_ferror(fd_t *fd);
enum ral_status f_gz_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param);
enum ral_status f_gz_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param);

#endif

