#include "../embedded_allocators.h"
#include <stdio.h>

uint8_t heap[HEAP_SIZE];

typedef struct bump_allocator_s
{
  uint8_t *heap;
  size_t  size;
  size_t  offset;
  size_t  prev_offset;

} bump_allocator_t;

void init_bump_alloc(bump_allocator_t *a, uint8_t *heap_start)
{
  a->heap = heap_start;
  a->size = HEAP_SIZE;
  a->offset = 0;
  a->prev_offset= 0;
}

void *bump_alloc(bump_allocator_t *a, size_t n)
{
  size_t alignement = (n + 7) & ~7;
  if (alignement + a->offset > a->size)
    return NULL;
  a->prev_offset = a->offset;
  a->offset += alignement;
  return (void *)a->heap + a->prev_offset;
}

void *reset_alloc(bump_allocator_t *a)
{
  for (size_t i = 0; i < a->size; ++i)
    heap[i] = 0;
  a->offset = 0;
  a->prev_offset = 0;
  return (void *)a->heap;
}

void  bump_alloc_info(bump_allocator_t *a)
{
  printf("heap addr: %p\noffset: %lu\nprev offset: %lu\nsize: %lu\n", a->heap, a->offset, a->prev_offset, a->size);
}
