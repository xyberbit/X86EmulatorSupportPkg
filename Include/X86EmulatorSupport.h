/** @file
    Root include file to support building X86EmulatorPkg.

    Copyright (c) 2023, xyberbit@gmail.com. All rights reserved.

    SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef __X86_EMULATOR_SUPPORT_H__
#define __X86_EMULATOR_SUPPORT_H__

#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>

//
// Aarch64/machine/int_limits.h
//
#define INT8_MIN	(-0x7f-1)
#define INT16_MIN	(-0x7fff-1)
#define INT32_MIN	(-0x7fffffff-1)
#define INT64_MIN	(-0x7fffffffffffffffLL-1)
#define INT8_MAX	0x7f
#define INT16_MAX	0x7fff
#define INT32_MAX	0x7fffffff
#define INT64_MAX	0x7fffffffffffffffLL

//
// Aarch64/machine/int_types.h
//
typedef INTN		intptr_t;
typedef UINTN		uintptr_t;

//
// Aarch64/machine/signal.h
//
typedef INTN		sig_atomic_t;

//
// X64/machine/int_fmtio.h
//
//   #define PRId64 "ld"
//   #define PRIx64 "lx"
//
#define PRId8		"d"
#define PRId16		"d"
#define PRId32		"d"
#define PRId64		"lld" // avoid format warning
#define PRIx8		"x"
#define PRIx16		"x"
#define PRIx32		"x"
#define PRIx64		"llx" // avoid format warning

//
// stdint.h
//
typedef  INT8		int8_t;
typedef UINT8		uint8_t;
typedef  INT16		int16_t;
typedef UINT16		uint16_t;
typedef  INT32		int32_t;
typedef UINT32		uint32_t;
typedef  INT64		int64_t;
typedef UINT64		uint64_t;

//
// sys/EfiCdefs.h
//
#if __STDC_VERSION__ >= 199901L
  #define __restrict  restrict
#else
  #if defined(_MSC_VER) || !__GNUC_PREREQ__(2, 92)
    #define __restrict
  #endif
#endif
typedef __SIZE_TYPE__	size_t; // follow main.c and Qsort.c in X86EmulatorPkg
typedef  INT32		LONG32;
typedef UINT32		ULONG32;
typedef  INT64		LONG64;
typedef UINT64		ULONG64;

//
// sys/types.h
//
typedef uint32_t	blksize_t;
typedef uint32_t	mode_t;
typedef int64_t	off_t;
typedef int32_t	pid_t;
typedef int64_t	dtime_t;
typedef INTN		ssize_t;
typedef INT32		time_t;

//
// sys/signal.h
//
typedef void	__sighandler_t(int);

//
// sys/stat.h
//
struct stat {
  off_t	st_size;
  off_t	st_physsize;
  off_t	st_curpos;
  dtime_t	st_birthtime;
  dtime_t	st_atime;
  dtime_t	st_mtime;
  mode_t	st_mode;
  blksize_t	st_blksize;
  uint32_t	st_spare[1];
};

//
// sys/fd_set.h
//
#define __NBBY		8
typedef int32_t	__fd_mask;
#define __NFDBITS	((unsigned int)sizeof(__fd_mask) * __NBBY)
#define __howmany(x,y)	(((x) + ((y) - 1)) / (y))
#ifndef FD_SETSIZE
#define FD_SETSIZE	256
#endif
typedef struct fd_set {
  __fd_mask fds_bits[__howmany(FD_SETSIZE, __NFDBITS)];
} fd_set;

//
// stdarg.h
//
#if defined(__GNUC__)
   typedef __builtin_va_list va_list;
#  define va_start	__builtin_va_start
#  define va_arg	__builtin_va_arg
#  define va_end	__builtin_va_end
#  define va_copy	__builtin_va_copy
#else
#  define va_list	VA_LIST
#  define va_start	VA_START
#  define va_arg	VA_ARG
#  define va_end	VA_END
#  define va_copy(s,d)	(s) = (d)
#endif

//
// errno.h
//
#define ENOENT		2
#define ENOSYS		78

//
// stddef.h
//
#define offsetof(StrucName, Member)  OFFSET_OF(StrucName, Member)

//
// time.h
//
struct tm {
  int		tm_year;
  int		tm_mon;
  int		tm_mday;
  int		tm_hour;
  int		tm_min;
  int		tm_sec;
  int		tm_wday;
  int		tm_yday;
  int		tm_isdst;
  int		tm_zoneoff;
  int		tm_daylight;
  UINT32	tm_Nano;
};

//
// string.h
//
void	*memcpy(void * __restrict Dest, const void * __restrict Src, size_t N);
int	memcmp(const void *S1, const void *S2, size_t N);
int	strcmp(const char *S1, const char *S2);
char	*strchr(const char *S, int C);
void	*memset(void *S, int C, size_t N);
size_t	strlen(const char *);
char	*strdup(const char *s);

//
// stdlib.h
//
void	abort(void) __attribute__ ((__noreturn__));
void	*realloc(void *Ptr, size_t NewSize);
void	qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

//
// stdio.h
//
typedef EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *FILE; // FILE only meaningful to stdout and stderr
int	fclose(FILE *);
int	fflush(FILE *fp);
FILE	*fopen(const char * __restrict Path, const char * __restrict Mode);
int	fprintf (FILE * __restrict stream, const char * __restrict format, ...);
int	printf(const char * __restrict, ...);
int	vfprintf(FILE * __restrict Stream, const char * __restrict Format, va_list Args);
int	snprintf (char * __restrict, size_t, const char * __restrict, ...) __attribute__((__format__(__printf__, 3, 4)));
extern	FILE *stdout;
extern	FILE *stderr;

//
// stdbool.h
//
#define bool	BOOLEAN
#define true	1
#define false	0
#define __bool_true_false_are_defined	1

//
// setjmp.h
//
typedef BASE_LIBRARY_JUMP_BUFFER jmp_buf[1];
#define setjmp(env) (INTN)SetJump((env))
extern void longjmp(jmp_buf env, int val);

//
// edk2's ASSERT
//
#define assert ASSERT

//
// no threads in UEFI
//
typedef VOID pthread_mutex_t; // dummy usage in main.c

#endif // __X86_EMULATOR_SUPPORT_H__
