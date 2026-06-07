#ifndef EMBEDDED_ALLOCATORS_H
# define EMBEDDED_ALLOCATORS_H
#include <stdint.h>
#include <stddef.h>

#ifndef internal
# define internal static
#endif

typedef struct bump_allocator_s
{
  uint8_t *buffer;
  size_t  size;
  size_t  offset;
  size_t  prev_offset;

} bump_allocator_t;

void init_bump_alloc(bump_allocator_t *a, uint8_t *buffer, size_t size);
 
void *bump_alloc(bump_allocator_t *a, size_t n);

void *reset_bump_alloc(bump_allocator_t *a);

#endif
