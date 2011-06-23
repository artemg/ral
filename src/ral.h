#ifndef RAL_H
#define RAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

// Compressed file abstraction layer

enum file_driver_open_modes {
    FD_READ  = 0x01,
    FD_WRITE = 0x02
};

enum file_driver_seek_modes {
    FD_SEEK_SET,
    FD_SEEK_END,
    FD_SEEK_CUR
};
typedef void fd_t;

struct file_driver_t{
    fd_t *(* open)(const char *fname, int mode, void *params);
    int (* close)(fd_t *fd);
    off_t (* seek)(fd_t *fd, size_t offset, int whence);
    off_t (* tell)(fd_t *fd);
    size_t(* read)(fd_t *fd, char *buf, size_t size);
    size_t(* write)(fd_t *fd, char *buf, size_t size);
    int (* compress)(char *dest, size_t *destLen, const char *source, size_t sourceLen);
    int (* uncompress)(char *dest, size_t *destLen, const char *source, size_t sourceLen);
};

enum drivers_t {RAL_STDC, RAL_GZ, RAL_LZO};
struct file_driver_t *getDriver(enum drivers_t d);

#ifdef __cplusplus
}
#endif 
#endif
