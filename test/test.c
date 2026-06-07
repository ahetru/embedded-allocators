#include "../embedded_allocators.h"
#include "unity.h"
#define BUFFER_SIZE 4 * 1024

static uint8_t buffer[BUFFER_SIZE];

void setUp(void) {
}

void tearDown(void) {
}

internal void fill_buffer_with_value(bump_allocator_t *a,size_t len, uint8_t value)
{
  for (size_t i = 0; i < len; ++i)
    a->buffer[i] = value;
}

internal void test_too_much_memory_required_return_null(void)
{
  bump_allocator_t a;
  init_bump_alloc(&a, buffer, BUFFER_SIZE);
  void *ptr = bump_alloc(&a, BUFFER_SIZE + 1);
  TEST_ASSERT_NULL(ptr);
}

internal void test_reset_bump_alloc(void)
{
  bump_allocator_t a;
  init_bump_alloc(&a, buffer, BUFFER_SIZE);
  uint8_t *ptr = (uint8_t*)bump_alloc(&a, 42);
  fill_buffer_with_value(&a, a.size, 42);
  reset_bump_alloc(&a);
  TEST_ASSERT_EQUAL_UINT(BUFFER_SIZE, a.size);
  TEST_ASSERT_EQUAL_UINT(0, a.offset);
  TEST_ASSERT_EQUAL_UINT(0, a.prev_offset);
  for (size_t i = 0; i < BUFFER_SIZE; ++i)
    TEST_ASSERT_EQUAL_UINT8(0, ptr[i]);
}

internal void test_value_is_written_in_buffer(void)
{
  bump_allocator_t a;
  init_bump_alloc(&a, buffer, BUFFER_SIZE);
  uint8_t *ptr = (uint8_t*)bump_alloc(&a, a.size);
  fill_buffer_with_value(&a, a.size, 0xFF);
  TEST_ASSERT_EACH_EQUAL_UINT8(0xFF, ptr, a.size);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_too_much_memory_required_return_null);
  RUN_TEST(test_reset_bump_alloc);
  RUN_TEST(test_value_is_written_in_buffer);
  return UNITY_END();
}
