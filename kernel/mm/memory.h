#ifndef MEMORY_H
#define MEMORY_H


#include <stdint.h>
#include <stddef.h>

void mem_init(uint32_t mem_low, uint32_t mem_high);
void* malloc(size_t size);
void free(void* ptr);

void mem_debug();


#endif
