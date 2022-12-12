#ifndef DEEPALLOC_INTERNAL_H
#define DEEPALLOC_INTERNAL_H
#include <sys/param.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/uio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <x86intrin.h>
#include <unistd.h>
#include <libpmem.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <semaphore.h>

#define _malloc malloc
#define _free free
#define DEEPALLOC_BESTFIT
#define SLAB_MORPHING
#define NBANKS 6

#include "deepalloc/internal/dl.h"
#define RB_COMPACT
#include "deepalloc/internal/rb.h"

#include "deepalloc/internal/ql.h"
#include "deepalloc/internal/ph.h"

#include "deepalloc/deepalloc.h"

#include "deepalloc/internal/atomic.h"
#include "deepalloc/internal/deepalloc_internal_types.h"
#include "deepalloc/internal/prng.h"
#include "deepalloc/internal/hash.h"
#include "deepalloc/internal/mutex_pool.h"
#include "deepalloc/internal/nstime.h"
#include "deepalloc/internal/ticker.h"
#include "deepalloc/internal/smoothstep.h"

#include "deepalloc/internal/simple_list.h"
#include "deepalloc/internal/persistent.h"

#include "deepalloc/internal/minilog.h"

/*
 * There are circular dependencies that cannot be broken without
 * substantial performance degradation.  In order to reduce the effect on
 * visual code flow, read the header files in multiple passes, with one of the
 * following cpp variables defined during each pass:
 *
 *   DEEPALLOC_H_TYPES   : Preprocessor-defined constants and psuedo-opaque data
 *                        types.
 *   DEEPALLOC_H_STRUCTS : Data structures.
 *   DEEPALLOC_H_EXTERNS : Extern data declarations and function prototypes.
 *   DEEPALLOC_H_INLINES : Inline functions.
 */
/******************************************************************************/
#define DEEPALLOC_H_TYPES

#include "deepalloc/internal/template.h"
#include "deepalloc/internal/sizeclass.h"
#include "deepalloc/internal/tsd.h"
#include "deepalloc/internal/extent.h"
#include "deepalloc/internal/numa_log.h"
#include "deepalloc/internal/tcache.h"
#include "deepalloc/internal/bitmap.h"
#include "deepalloc/internal/slab.h"
#include "deepalloc/internal/log.h"
#include "deepalloc/internal/arena.h"

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#define CACHELINE_SIZE 64
#define PAGE_SIZE 4096

#define CHUNK_BIT_SIZE_LG 12
#define CHUNK_BIT_SIZE (1ULL << CHUNK_BIT_SIZE_LG)

#define CHUNK_SIZE_LG 21
#define CHUNK_SIZE (1ULL << CHUNK_SIZE_LG)

#define LG_VADDR 48
#define LG_SIZEOF_PTR 3
#define LG_PAGE 12

#define LG_FLOOR_1(x) 0
#define LG_FLOOR_2(x) (x < (1ULL << 1) ? LG_FLOOR_1(x) : 1 + LG_FLOOR_1(x >> 1))
#define LG_FLOOR_4(x) (x < (1ULL << 2) ? LG_FLOOR_2(x) : 2 + LG_FLOOR_2(x >> 2))
#define LG_FLOOR_8(x) (x < (1ULL << 4) ? LG_FLOOR_4(x) : 4 + LG_FLOOR_4(x >> 4))
#define LG_FLOOR_16(x) (x < (1ULL << 8) ? LG_FLOOR_8(x) : 8 + LG_FLOOR_8(x >> 8))
#define LG_FLOOR_32(x) (x < (1ULL << 16) ? LG_FLOOR_16(x) : 16 + LG_FLOOR_16(x >> 16))
#define LG_FLOOR_64(x) (x < (1ULL << 32) ? LG_FLOOR_32(x) : 32 + LG_FLOOR_32(x >> 32))

#define LG_FLOOR(x) LG_FLOOR_64((x))
#define LG_CEIL(x) (LG_FLOOR(x) + (((x) & ((x)-1)) == 0 ? 0 : 1))

typedef unsigned szind_t;
typedef unsigned pszind_t;

#undef DEEPALLOC_H_TYPES
/******************************************************************************/
#define DEEPALLOC_H_STRUCTS

#include "deepalloc/internal/template.h"
#include "deepalloc/internal/sizeclass.h"
#include "deepalloc/internal/tsd.h"
#include "deepalloc/internal/extent.h"
#include "deepalloc/internal/numa_log.h"
#include "deepalloc/internal/tcache.h"
#include "deepalloc/internal/bitmap.h"
#include "deepalloc/internal/slab.h"
#include "deepalloc/internal/log.h"
#include "deepalloc/internal/arena.h"

#undef DEEPALLOC_H_STRUCTS
/******************************************************************************/
#define DEEPALLOC_H_EXTERNS

#include "deepalloc/internal/template.h"
#include "deepalloc/internal/sizeclass.h"
#include "deepalloc/internal/tsd.h"
#include "deepalloc/internal/extent.h"
#include "deepalloc/internal/numa_log.h"
#include "deepalloc/internal/tcache.h"
#include "deepalloc/internal/bitmap.h"
#include "deepalloc/internal/slab.h"
#include "deepalloc/internal/arena.h"
#include "deepalloc/internal/log.h"

extern uint32_t meta_size;

extern size_t opt_narenas;
extern const char PMEMPATH[2][50];

arena_t *choose_arena_hard(void);

#undef DEEPALLOC_H_EXTERNS
/******************************************************************************/
#define DEEPALLOC_H_INLINES

#include "deepalloc/internal/template.h"
#include "deepalloc/internal/sizeclass.h"
#include "deepalloc/internal/tsd.h"
#include "deepalloc/internal/extent.h"
#include "deepalloc/internal/bitmap.h"
#include "deepalloc/internal/slab.h"
#include "deepalloc/internal/numa_log.h"
#include "deepalloc/internal/arena.h"
#include "deepalloc/internal/rtree.h"
#include "deepalloc/internal/log.h"

static inline arena_t *choose_arena(arena_t *arena)
{
	arena_t *ret;

	if (arena != NULL)
		return (arena);

	if (unlikely((ret = *arenas_tsd_get()) == NULL))
	{
		ret = choose_arena_hard();
		assert(ret != NULL);
	}

	return (ret);
}

static inline int getcpu(unsigned *cpu, unsigned *node,struct getcpu_cache *tcache)
{
	return syscall(SYS_getcpu, cpu, node, tcache);
}

#include "deepalloc/internal/tcache.h"

#undef DEEPALLOC_H_INLINES
/******************************************************************************/
#endif /* DEEPALLOC_INTERNAL_H */
