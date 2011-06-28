#ifndef RAL_GZ_H
#define RAL_GZ_H

#include "ral.h"
fd_t *f_gz_open(const char *fname, int mode, void *params);
int    f_gz_close(fd_t *fd);
off_t  f_gz_seek(fd_t *fd, size_t offset, int whence);
off_t  f_gz_tell(fd_t *fd);
size_t f_gz_read(fd_t *fd, char *buf, size_t size);
size_t f_gz_write(fd_t *fd, char *buf, size_t size);
enum ral_status f_gz_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen);
enum ral_status f_gz_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen);

#endif

