#ifndef DEEPALLOC_H_
#define DEEPALLOC_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"

    void *deepalloc_malloc_to(size_t size, void **ptr);

    void deepalloc_free_from(void **pptr);

    int deepalloc_init();

    int deepalloc_close();

    uint64_t deepget_memory_usage();

#ifdef __cplusplus
};
#endif
#endif /* DEEPALLOC_H_ */