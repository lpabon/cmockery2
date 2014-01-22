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
#ifndef CMOCKERY_OVERRIDE_H_
#define CMOCKERY_OVERRIDE_H_

#if UNIT_TESTING

/* Prototypes */
extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void* _test_calloc(const size_t number_of_elements, const size_t size,
                          const char* file, const int line);
extern void _test_free(void* const ptr, const char* file, const int line);
extern void mock_assert(const int result, const char* const expression,
                        const char * const file, const int line);
extern int example_test_printf(const char *format, ...);
extern int example_test_fprintf(FILE * const file, const char *format, ...);
extern void print_message(const char *format, ...);
int example_main(int argc, char *argv[]);


/* Reset any previous definitions */
#undef assert
#undef malloc
#undef calloc
#undef free
#undef printf
#undef fprintf

/* Redirect to use test functions */
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define calloc(num, size) _test_calloc(num, size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
#define printf example_test_printf
#define main example_main


#endif /* UNIT_TESTING */
#endif /* CMOCKERY_OVERRIDE_H_ */
