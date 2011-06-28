#include "ral_gz.h"
#include <zlib.h>

// GZ file implement

fd_t *f_gz_open(const char *fname, int mode, void *params){
    gzFile loc_fd;
    const char *loc_mode = NULL;

    if( fname == NULL ){
        return NULL;
    }
    if( mode & FD_READ ){
        loc_mode = "r";
    } else if ( mode & FD_WRITE ){
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

off_t  f_gz_seek(fd_t *fd, size_t offset, int whence){
    int loc_whence;

    switch (whence){
        case FD_SEEK_SET:
            loc_whence = SEEK_SET;
            break;
        case FD_SEEK_CUR:
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

enum ral_status f_gz_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen){
    if( compress((Bytef *) dest, (uLongf *)destLen, (const Bytef *) source, sourceLen) != Z_OK){
        return RAL_ERROR;
    }
    return RAL_OK;
}
enum ral_status f_gz_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen){
    if( uncompress((Bytef *) dest, (uLongf *)destLen, (const Bytef *) source, sourceLen) != Z_OK){
        return RAL_ERROR;
    }
    return RAL_OK;
}


