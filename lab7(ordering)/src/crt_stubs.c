/* crt_stubs.c */

#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

/* C 运行时钩子 */
void _init(void)  { }
void _fini(void)  { }

/* 最小 syscalls 存根 */
int _close(int fd) {
    (void)fd;
    errno = EBADF;
    return -1;
}

int _lseek(int fd, int ptr, int dir) {
    (void)fd; (void)ptr; (void)dir;
    return 0;
}

int _read(int fd, void *buf, size_t nbytes) {
    (void)fd; (void)buf; (void)nbytes;
    return 0;
}

int _write(int fd, const void *buf, size_t nbytes) {
    (void)fd; (void)buf; (void)nbytes;
    return (int)nbytes;
}

void* _sbrk(int incr) {
    (void)incr;
    return (void*)-1;  
}