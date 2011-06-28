#include "ral_lzo.h"
#include "lzo/lzoconf.h"
#include "lzo/lzo1x.h"
#include <stdlib.h>

// LZO file implement
/*
fd_t *f_lzo_open(const char *fname, int mode, void *params){
    LzoCompressor::open_mode loc_mode;
    LzoCompressor *loc_fd = NULL;

    if( mode & FD_READ ){
        loc_mode = LzoCompressor::MODE_READ;
    } else if ( mode & FD_WRITE ){
        loc_mode = LzoCompressor::MODE_WRITE;
    }

    loc_fd = new LzoCompressor;
    if( loc_fd->Init() == false ){
        ERROR_LOG(L_WARN, "Cant init Lzo compressor\n");
        delete loc_fd;
        return NULL;
    }
    if( loc_fd->open(fname, loc_mode) != 1 ){
        ERROR_LOG(L_WARN, "Cant open file '%s'\n", fname);
        delete loc_fd;
        return NULL;
    }
    return loc_fd;
}

int f_lzo_close(fd_t *fd_){
    LzoCompressor *fd = (LzoCompressor *)fd_;
    fd->close();
    delete fd;
    return 0;
}

off_t f_lzo_seek(fd_t *fd, size_t offset, int whence){
    ERROR_LOG(L_ERROR, "seek for lzo Not implemented\n");
    exit(1);
}
off_t  f_lzo_tell(fd_t *fd_){
    LzoCompressor *fd = (LzoCompressor *)fd_;
    LzoCompressor::Offset offset;
    offset = fd->tell();
    return offset.file_offset;
}

size_t f_lzo_read(fd_t *fd_, char *buf, size_t size){
    LzoCompressor *fd = (LzoCompressor *)fd_;
    return fd->read(buf, size);
}

size_t f_lzo_write(fd_t *fd_, char *buf, size_t size){
    LzoCompressor *fd = (LzoCompressor *)fd_;
    return fd->write(buf ,size);
}
*/

enum ral_status f_lzo_compress(char *dest, size_t *destLen, const char *source, size_t sourceLen){
    enum ral_status ret;
    if (lzo_init() != LZO_E_OK){
        return RAL_ERROR;
    }
    unsigned char *workingMemory = (unsigned char*)malloc(LZO1X_1_11_MEM_COMPRESS);

    if( lzo1x_1_11_compress((const unsigned char *)source, sourceLen, (unsigned char *)dest, destLen, workingMemory) == LZO_E_OK ){
        ret = RAL_OK;
    } else {
        ret = RAL_ERROR;
    }
    free(workingMemory);

    return ret;
}

enum ral_status f_lzo_uncompress(char *dest, size_t *destLen, const char *source, size_t sourceLen){
    if( lzo1x_decompress( (const unsigned char *)source, sourceLen, (unsigned char *)dest, destLen, NULL) == LZO_E_OK ){
        return RAL_OK;
    } else {
        return RAL_ERROR;
    }
}

