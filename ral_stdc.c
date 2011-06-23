#include "ral_stdc.h"
#include <stdio.h>

fd_t *f_reg_open(const char *fname, int mode, void *params){
    FILE *loc_fd = NULL;
    const char *loc_mode = NULL;

    if( fname == NULL )
        return NULL;
    if( mode & FD_READ ){
        loc_mode = "r";
    } else if ( mode & FD_WRITE ){
        loc_mode = "w+";
    }
    return fopen(fname, loc_mode);
}
int f_reg_close(fd_t *fd_){
    FILE *fd = (FILE *)fd_;
    return fclose(fd);
}

off_t  f_reg_seek(fd_t *fd_, size_t offset, int whence){
    int loc_whence;
    FILE *fd = (FILE *)fd_;

    switch (whence){
        case FD_SEEK_SET:
            loc_whence = SEEK_SET;
            break;
        case FD_SEEK_END:
            loc_whence = SEEK_END;
            break;
        case FD_SEEK_CUR:
            loc_whence = SEEK_CUR;
            break;
        default:
            //ERROR_LOG(L_WARN, "Unknown whence\n");
            return -1;
            break;
    }
    return fseek(fd, offset, loc_whence);
}

off_t  f_reg_tell(fd_t *fd_){
    FILE *fd = (FILE *)fd_;
    return ftell(fd);
}

size_t f_reg_read(fd_t *fd_, char *buf, size_t size){
    FILE *fd = (FILE *)fd_;
    return fread(buf, 1, size, fd);
}

size_t f_reg_write(fd_t *fd_, char *buf, size_t size){
    FILE *fd = (FILE *)fd_;
    return fwrite(buf, 1, size, fd);
}
