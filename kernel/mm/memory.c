#include "memory.h"
#include "../libs/kprintf.h"

typedef struct mem_block {
    size_t size;
    int free;
    struct mem_block* next;
} mem_block_t;

static uint32_t mem_start;
static uint32_t mem_end;
static mem_block_t* head = NULL;

#define ALIGN4(x) (((x) + 3) & ~3)

void mem_init(uint32_t mem_low, uint32_t mem_high) 
{
    mem_start = 0x100000;  // 1MB
    mem_end = mem_start + (mem_high * 1024);
    head = (mem_block_t*)mem_start;
    head->size = mem_end - mem_start - sizeof(mem_block_t);
    head->free = 1;
    head->next = NULL;
}

void split_block(mem_block_t* block, size_t size) 
{
    if (block->size >= size + sizeof(mem_block_t) + 4) 
    {
        mem_block_t* new_block = (mem_block_t*)((char*)block + sizeof(mem_block_t) + size);
        new_block->size = block->size - size - sizeof(mem_block_t);
        new_block->free = 1;
        new_block->next = block->next;
        
        block->size = size;
        block->next = new_block;
    }
}

void* malloc(size_t size) 
{
    if (size == 0) return NULL;
    
    size = ALIGN4(size);
    
    mem_block_t* current = head;
    
    while (current != NULL) {
        if (current->free && current->size >= size) {
            split_block(current, size);  
            current->free = 0;
            return (void*)((char*)current + sizeof(mem_block_t));
        }
        current = current->next;
    }
    
    return NULL;  
}

void merge_blocks() {
    mem_block_t* current = head;
    
    while (current && current->next)
    {
        if (current->free && current->next->free) {
            current->size += sizeof(mem_block_t) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void free(void* ptr) {
    if (!ptr) return;
    
    mem_block_t* block = (mem_block_t*)((char*)ptr - sizeof(mem_block_t));
    block->free = 1;
    
    merge_blocks();  
}

void* calloc(size_t count, size_t size)
{
    size_t total = count * size;
    void* ptr = malloc(total);
    if (!ptr) return NULL;
    
    char* p = (char*)ptr;
    for (size_t i = 0; i < total; i++)
        p[i] = 0;
    
    return ptr;
}

void* realloc(void* ptr, size_t size)
{
    if (!ptr) return malloc(size);
    if (size == 0) { free(ptr); return NULL; }
    
    mem_block_t* block = (mem_block_t*)((char*)ptr - sizeof(mem_block_t));
    
    if (block->size >= size) return ptr;
    
    void* new_ptr = malloc(size);
    if (!new_ptr) return NULL;
    
    char* src = (char*)ptr;
    char* dst = (char*)new_ptr;
    for (size_t i = 0; i < block->size; i++)
        dst[i] = src[i];
    
    free(ptr);
    return new_ptr;
}

void mem_debug() 
{
    mem_block_t* current = head;
    int i = 0;
    
    kprintf("\nMemory blocks:\n");
    while (current) 
    {
        kprintf("Block %d: %u bytes, %s\n", i++, current->size, current->free ? "FREE" : "USED");
        current = current->next;
    }
}

