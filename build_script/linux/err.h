#ifndef _LINUX_ERR_H
#define _LINUX_ERR_H

#include <errno.h>
#include <stdbool.h>

#define MAX_ERRNO 4095

#define IS_ERR_VALUE(x) ((x) >= (unsigned long)-MAX_ERRNO)

static inline void *ERR_PTR(long error)
{
    return (void *) error;
}

static inline long PTR_ERR(const void *ptr)
{
    return (long) ptr;
}

static inline bool IS_ERR(const void *ptr)
{
    return IS_ERR_VALUE((unsigned long)ptr);
}

static inline bool IS_ERR_OR_NULL(const void *ptr)
{
    return !ptr || IS_ERR_VALUE((unsigned long)ptr);
}

#endif /* _LINUX_ERR_H */