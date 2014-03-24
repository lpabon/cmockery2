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

// A test case that does nothing and succeeds.
static void realloc_tests(void **state) {

    typedef struct {
        int a;
        int b;
        char str[128];
    } some_data_t;

    void *q;
    some_data_t *some_data;

    // Like a malloc
    q = test_realloc(NULL, 256);
    assert_non_null(q);

    // Like a free
    q = test_realloc(q, 0);
    assert_null(q);

    // Write some data
    some_data = (some_data_t *)test_malloc(sizeof(some_data_t));
    assert_non_null(some_data);
    some_data->a = 1;
    some_data->b = 2;
    strcpy(some_data->str, "Hello World");

    // Now realloc
    some_data = (some_data_t *)test_realloc(some_data, sizeof(some_data_t)*2);
    assert_int_equal(some_data->a, 1);
    assert_int_equal(some_data->a, 1);
    assert_string_equal(some_data->str, "Hello World");

    // Now write some data to the next allocated chunk
    some_data[1].a = 3;
    some_data[1].b = 4;
    strcpy(some_data[1].str, "Hello Again");

    // This call should not complain that we overwrote data
    test_free(some_data);
}

int main(void) {
    const UnitTest tests[] = {
        unit_test(realloc_tests),
    };

    return run_tests(tests, "realloc");
}
