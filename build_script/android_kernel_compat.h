#ifndef ANDROID_KERNEL_COMPAT_H
#define ANDROID_KERNEL_COMPAT_H

/* Prevent problematic kernel header includes */
#ifndef _LINUX_COMPILER_H_
#define _LINUX_COMPILER_H_
#endif

/* Prevent kernel signal conflicts with bionic */
#ifndef _LINUX_SIGNAL_H
#define _LINUX_SIGNAL_H
#endif
#ifndef _ASM_GENERIC_SIGNAL_DEFS_H
#define _ASM_GENERIC_SIGNAL_DEFS_H
#endif

/* Android NDK compatibility definitions for kernel macros */

/* Compiler attributes */
#ifndef __user
#define __user
#endif
#ifndef __force
#define __force
#endif
#ifndef __poll_t
#define __poll_t int
#endif
#ifndef __weak
#define __weak __attribute__((weak))
#endif
#ifndef __maybe_unused
#define __maybe_unused __attribute__((unused))
#endif
#ifndef __printf
#define __printf(a, b) __attribute__((format(printf, a, b)))
#endif
#ifndef __noreturn
#define __noreturn __attribute__((noreturn))
#endif
#ifndef fallthrough
#define fallthrough __attribute__((fallthrough))
#endif

/* Type checking macros */
#ifndef __same_type
#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#endif
#ifndef __must_be_array
#define __must_be_array(a) 0
#endif

/* ELF constants */
#ifndef SHT_GNU_versym
#define SHT_GNU_versym 0x6fffffff
#endif
#ifndef SHT_GNU_verdef
#define SHT_GNU_verdef 0x6ffffffd
#endif

/* Missing functions for Android */
#include <stdlib.h>
#if !defined(__GLIBC__) && !defined(qsort_r)
static inline void qsort_r(void *base, size_t nmemb, size_t size,
                           int (*compar)(const void *, const void *, void *),
                           void *arg) {
    /* Simple fallback - not thread-safe but works for basic sorting */
    static void *qsort_r_arg __attribute__((unused));
    qsort_r_arg = arg;
    qsort(base, nmemb, size, (int (*)(const void *, const void *))compar);
}
#endif

/* Missing compile-time assertions */
#ifndef compiletime_assert
#define compiletime_assert(condition, msg) \
    typedef char __compiletime_assert_##__COUNTER__[(condition) ? 1 : -1]
#endif

/* Include ftw.h first to get system definitions */
#include <ftw.h>

/* Missing POSIX file tree walk definitions if not available */
#ifndef FTW_PHYS
#define FTW_PHYS 1
#endif
#ifndef FTW_MOUNT
#define FTW_MOUNT 2
#endif
#ifndef FTW_CHDIR
#define FTW_CHDIR 4
#endif
#ifndef FTW_DEPTH
#define FTW_DEPTH 8
#endif

#endif /* ANDROID_KERNEL_COMPAT_H */