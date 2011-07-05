#ifndef RAL_H
#define RAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

// Compressed file abstraction layer

enum file_driver_open_modes {
    RAL_READ  = 0x01,
    RAL_WRITE = 0x02
};

enum file_driver_seek_modes {
    RAL_SEEK_SET,
    RAL_SEEK_END,
    RAL_SEEK_CUR
};
typedef void fd_t;

enum ral_status{
    RAL_OK,
    RAL_EINVALID_INPUT,
    RAL_EBUFFER_TOO_SMALL,
    RAL_ENOT_ENOUGH_MEM,
    RAL_EUNKNOWN
};

struct file_driver_t{
    // unstable
    fd_t *(* open)(const char *fname, int mode, void *params);
    int (* close)(fd_t *fd);
    off_t (* seek)(fd_t *fd, size_t offset, int whence);
    off_t (* tell)(fd_t *fd);
    size_t(* read)(fd_t *fd, char *buf, size_t size);
    size_t(* write)(fd_t *fd, char *buf, size_t size);
    int (* feof)(fd_t *fd);
    int (* ferror)(fd_t *fd);

    enum ral_status (* compress)(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param);
    enum ral_status (* uncompress)(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param);
};

static const char *driver_names[] = {"STDC", "GZ", "LZO", "SNAPPY", "BZIP", "UNKNOWN"};
enum drivers_t {RAL_STDC, RAL_GZ, RAL_LZO, RAL_SNAPPY, RAL_BZIP, RAL_END};
struct file_driver_t *get_driver(enum drivers_t d);
const char *get_driver_name(enum drivers_t);
#ifdef __cplusplus
}
#endif 
#endif

