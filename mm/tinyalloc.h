#ifndef TINYALLOC_H
#define TINYALLOC_H

#include "../inc/core/common.h"

bool ta_init(const void *base, const void *limit, const size_t heap_blocks, const size_t split_thresh, const size_t alignment);
void *malloc(size_t num);
void *calloc(size_t num, size_t size);
bool free(void *ptr);
void* memcpy(void* dst, const void* src, unsigned int cnt);
void* realloc(void* Block, size_t size);
void *memset(void *source, unsigned char val, size_t count);
void *memsetw(void *source, unsigned short word, size_t count);

size_t ta_num_free();
size_t ta_num_used();
size_t ta_num_fresh();
bool ta_check();

#endif