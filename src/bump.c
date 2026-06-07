#include "../embedded_allocators.h"

void init_bump_alloc(bump_allocator_t *a, uint8_t *buffer, size_t size)
{
  a->buffer = buffer;
  a->size = size;
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
  return (void *)a->buffer + a->prev_offset;
}

void *reset_bump_alloc(bump_allocator_t *a)
{
  for (size_t i = 0; i < a->size; ++i)
    a->buffer[i] = 0;
  a->offset = 0;
  a->prev_offset = 0;
  return (void *)a->buffer;
}
