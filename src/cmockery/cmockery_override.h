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

/*
 * Override common functions to use test functions.
 *
 * Add the following as the last include to your code:
 * 
 * #ifdef UNIT_TESTING
 * #include <cmockery_override.h>
 * #endif
 *
 */
#ifdef UNIT_TESTING

#ifndef CMOCKERY_OVERRIDE_H_
#define CMOCKERY_OVERRIDE_H_
/* Prototypes */
extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void* _test_calloc(const size_t number_of_elements, const size_t size,
                          const char* file, const int line);
extern void* _test_realloc(void* ptr, const size_t size, const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);

extern void print_message(const char *format, ...);

// Can be used to replace assert in tested code so that in conjunction with
// check_assert() it's possible to determine whether an assert condition has
// failed without stopping a test.
extern void mock_assert(const int result, const char* const expression,
                        const char * const file, const int line);

#endif /* CMOCKERY_OVERRIDE_H_ */

/* Reset any previous definitions */
#ifdef assert
#undef assert
#endif // assert

#ifdef malloc
#undef malloc
#endif // malloc

#ifdef calloc
#undef calloc
#endif // calloc

#ifdef free
#undef free
#endif // free

/* Redirect to use test functions */
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__)

// Redirect malloc, calloc and free to the unit test allocators.
#define test_malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define test_calloc(num, size) _test_calloc(num, size, __FILE__, __LINE__)
#define test_realloc(ptr, size) _test_realloc(ptr, size, __FILE__, __LINE__)
#define test_free(ptr) _test_free(ptr, __FILE__, __LINE__)
#define malloc test_malloc
#define calloc test_calloc
#define realloc test_realloc
#define free test_free


#endif /* UNIT_TESTING */
