#include "ral_gz.h"
#include <zlib.h>

// GZ file implement

fd_t *f_gz_open(const char *fname, int mode, void *params){
    gzFile loc_fd;
    const char *loc_mode = NULL;

    if( fname == NULL ){
        return NULL;
    }
    if( mode & RAL_READ ){
        loc_mode = "r";
    } else if ( mode & RAL_WRITE ){
        loc_mode = "w+";
    }

    loc_fd = gzopen(fname, loc_mode);
    if( loc_fd == Z_NULL ){
        return NULL;
    } 
    return loc_fd;
}

int f_gz_close(fd_t *fd){
    return gzclose(fd);
}

off_t  f_gz_seek(fd_t *fd, size_t offset, enum file_driver_seek_modes whence){
    int loc_whence;

    switch (whence){
        case RAL_SEEK_SET:
            loc_whence = SEEK_SET;
            break;
        case RAL_SEEK_CUR:
            loc_whence = SEEK_CUR;
            break;
        default:
            return -1;
            break;
    }
    return gzseek(fd, offset, loc_whence);
}

off_t  f_gz_tell(fd_t *fd){
    return gztell(fd);
}

size_t f_gz_read(fd_t *fd, char *buf, size_t size){
    return gzread(fd, buf, size);
}

size_t f_gz_write(fd_t *fd, char *buf, size_t size){
    return gzwrite(fd, buf, size);
}

int f_fz_ferror(fd_t *fd){
    int res;
    gzerror(fd, &res);
    if( res == Z_ERRNO )
        return 0;
    else
        return 1;
}

int f_gz_feof(fd_t *fd){
    return gzeof(fd);
}

enum ral_status f_gz_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param){
    enum ral_status ret;
    int res = compress((Bytef *) dest, (uLongf *)destLen, (const Bytef *) source, sourceLen);
    switch (res){
        case Z_OK:
            ret = RAL_OK;
            break;
        case Z_BUF_ERROR:
            ret = RAL_EBUFFER_TOO_SMALL;
            break;
        case Z_MEM_ERROR:
            ret = RAL_ENOT_ENOUGH_MEM;
            break;
        default:
            ret = RAL_EUNKNOWN;
            break;
    }
    return ret;
}

enum ral_status f_gz_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen, void *param){
    enum ral_status ret;
    int res = uncompress((Bytef *) dest, (uLongf *)destLen, (const Bytef *) source, sourceLen);
    switch (res){
        case Z_OK:
            ret = RAL_OK;
            break;
        case Z_BUF_ERROR:
            ret = RAL_EBUFFER_TOO_SMALL;
            break;
        case Z_MEM_ERROR:
            ret = RAL_ENOT_ENOUGH_MEM;
            break;
        case Z_DATA_ERROR:
            ret = RAL_EINVALID_INPUT;
            break;
        default:
            ret = RAL_EUNKNOWN;
            break;
    }
    return ret;
}

