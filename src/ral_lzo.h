#ifndef RAL_LZO_H
#define RAL_LZO_H

#include "ral.h"
fd_t *f_lzo_open(const char *fname, int mode, void *params);
int    f_lzo_close(fd_t *fd);
off_t  f_lzo_seek(fd_t *fd, size_t offset, int whence);
off_t  f_lzo_tell(fd_t *fd);
size_t f_lzo_read(fd_t *fd, char *buf, size_t size);
size_t f_lzo_write(fd_t *fd, char *buf, size_t size);
enum ral_status f_lzo_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen);
enum ral_status f_lzo_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen);

#endif

