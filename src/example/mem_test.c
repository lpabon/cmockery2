/*
 * Copyright 2014 Luis Pabon, Jr.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <setjmp.h>
#include <inttypes.h>
#include <cmockery.h>

typedef struct {
    uintmax_t max;
    char c;
    void *v;
} test_struct_t;

static void
test_struct_expect_memory_check( test_struct_t *some_struct )
{
    check_expected(some_struct);
}

static void
test_expect_memory_check( void *some_pointer )
{
    check_expected(some_pointer);
}

static void test_expect_memory(void **state) {
    unsigned char some_data[32];

    memset(some_data, 0xA5, sizeof(some_data));

    // Check the memory is the same
    expect_memory(test_expect_memory_check,
            some_pointer,
            some_data, sizeof(some_data));

    test_expect_memory_check(some_data);
}

static void test_expect_not_memory(void **state) {
    unsigned char some_data[32];
    unsigned char zero_data[32];

    memset(some_data, 0xA5, sizeof(some_data));
    memset(zero_data, 0, sizeof(zero_data));

    // Check the memory is not the same
    expect_not_memory(test_expect_memory_check,
            some_pointer,
            some_data, sizeof(some_data));
    test_expect_memory_check(zero_data);
}

static void test_expect_memory_fail(void **state) {
    unsigned char some_data[32];
    unsigned char zero_data[32];

    memset(some_data, 0xA5, sizeof(some_data));
    memset(zero_data, 0, sizeof(zero_data));

    // Check the memory is the same
    expect_memory(test_expect_memory_check,
            some_pointer,
            some_data, sizeof(some_data));

    test_expect_memory_check(zero_data);
}

static void test_expect_not_memory_fail(void **state) {
    unsigned char some_data[32];

    memset(some_data, 0xA5, sizeof(some_data));

    // Check the memory is not the same
    expect_not_memory(test_expect_memory_check,
            some_pointer,
            some_data, sizeof(some_data));
    test_expect_memory_check(some_data);
}

static void test_struct_expect_memory(void **state) {
    test_struct_t *some_data;
    unsigned char *c;


    some_data = (test_struct_t *)calloc(1, sizeof(test_struct_t));
    c = (unsigned char *)&(some_data->max);
    *c = 1;
    some_data->c = 2;
    some_data->v = test_malloc(10);

    // Check the memory is the same
    expect_memory(test_struct_expect_memory_check,
            some_struct,
            some_data, sizeof(test_struct_t));

    test_struct_expect_memory_check(some_data);

    test_free(some_data->v);
    test_free(some_data);
}

int main(void) {
    const UnitTest tests[] = {
        unit_test(test_expect_memory),
        unit_test(test_expect_not_memory),
        unit_test_expect_failure(test_expect_memory_fail),
        unit_test_expect_failure(test_expect_not_memory_fail),
        unit_test(test_struct_expect_memory),
    };

    return run_tests(tests, "mem_tests");
}
