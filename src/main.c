#include "ral.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FAIL printf("%s failed\n", test_name)
void buf_rnd(char *buf, const size_t size){
    return;
}

int buf_cmp(const void *b1, const void *b2, const size_t size){
    return memcmp(b1, b2, size);
}

int check_cmp(struct file_driver_t *d, const size_t size){
    int ret = 0;
    const char *test_name = "check cmp buf";
    char *in = (char *)malloc(size);
    char *tmp = (char *)malloc(size * 2);
    char *out = (char *)malloc(size);

    size_t tmp_len = size * 2;
    size_t out_len = size;

    buf_rnd(in, size);
    if( d->compress(tmp, &tmp_len, in, size, NULL) != RAL_OK ){
        test_name = "compress";
        FAIL;
        goto err;
    }
    if( d->uncompress(out, &out_len, tmp, tmp_len, NULL) != RAL_OK ){
        test_name = "uncompress";
        FAIL;
        goto err;
    }
    if( out_len != size ){
        test_name = "len";
        FAIL;
        goto err;
    }
    if( buf_cmp(in, out, size) ){
        test_name = "cmp";
        FAIL;
        goto err;
    }
ret:
    free(in);
    free(tmp);
    free(out);
    return ret;
err:
    ret = -1;
    goto ret;
}

int check_driver(enum drivers_t id){
    int ret = -1;

    printf("---testing driver %s...   ", get_driver_name(id));
    struct file_driver_t *d = get_driver(id);    
    if( d == NULL ){
        printf("get_driver returned NULL\n");
        goto ret;
    }
    if( d->compress == NULL ){
        printf("compress is NULL\n");
        goto ret;
    }
    if( d->uncompress == NULL ){
        printf("uncompress == NULL\n");
        goto ret;
    }
    /*
    {
        const char *test_name = "check empty";
        char buf[0];
        if( d->compress(buf, 0, buf, 0) != RAL_OK ){
            FAIL;
            goto ret;
        }
        if( d->uncompress(buf, 0, buf, 0) != RAL_OK ){
            FAIL;
            goto ret;
        }
    }
    */
    
    // check basic buff
    if( check_cmp(d, 256) ){
        goto ret;
    }
    if( check_cmp(d, 5000) ){
        goto ret;
    }
    if( check_cmp(d, 1024*1024*1024) ){
        goto ret;
    }

    if( d->open == NULL ){
        printf("open is NULL\n");
        goto skip_file_io;
    }
    if( d->close == NULL ){
        printf("close is NULL\n");
        goto skip_file_io;
    }
    if( d->seek == NULL ){
        printf("seek is NULL\n");
        goto skip_file_io;
    }
    if( d->tell == NULL ){
        printf("tell is NULL\n");
        goto skip_file_io;
    }
    if( d->read == NULL ){
        printf("read is NULL\n");
        goto skip_file_io;
    }
    if( d->write == NULL ){
        printf("write is NULL\n");
        goto skip_file_io;
    }
skip_file_io:

    ret = 0;
ret:
    printf("%s\n",
        ret? "BAD" : "OK");
    return ret;
}

int main(int argc, char *argv[]){
    int i;
    setvbuf(stdout, NULL, _IONBF, 0);
    for(i = 0; i != RAL_END; ++i){
        check_driver((enum drivers_t) i);
    }
    return 0;
}
