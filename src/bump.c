#include "../embedded-allocators.h"
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
}

void *bump_alloc(bump_allocator_t *a, size_t n)
{
  size_t alignement = (n + 7) & ~7;
  if (alignement > a->size)
    return NULL;
  a->prev_offset = a->offset;
  a->offset += alignement;
  a->size -= alignement;
  return (void *)a->heap + a->prev_offset;
}

static void  bump_alloc_info(bump_allocator_t *a)
{
  printf("heap: %p\nsize: %lu\noffset: %p\n", a->heap, a->size, a->heap + a->offset);
}

int main(void)
{
  bump_allocator_t a;
  init_bump_alloc(&a, heap);
  bump_alloc_info(&a);

  while (bump_alloc(&a, 660))
    bump_alloc_info(&a);
  return 0;
}



