/*
 * Copyright 2008 Google Inc.
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
#ifndef CMOCKERY_H_
#define CMOCKERY_H_

#include <cmockery/cmockery_override.h>

// Windows
#ifdef _WIN32
#if _MSC_VER < 1500
#ifdef __cplusplus
extern "C" {
#endif   // __cplusplus
int __stdcall IsDebuggerPresent();
#ifdef __cplusplus
} /* extern "C" */
#endif   // __cplusplus
#endif  // _MSC_VER < 1500
#endif  // _WIN32

/*
 * These headers or their equivalents should be included prior to including
 * this header file.
 *
 * #include <stdarg.h>
 * #include <stddef.h>
 * #include <setjmp.h>
 * #include <inttypes.h>
 *
 * This allows test applications to use custom definitions of C standard
 * library functions and types.
 */

// For those who are used to __func__ from gcc.
#ifndef __func__
#define __func__ __FUNCTION__
#endif

/* Printf formats used to display uintmax_t. */
#ifdef _WIN32

#ifndef PRIdMAX
#define PRIdMAX "I64d"
#endif /* PRIdMAX */
#ifndef PRIiMAX
#define PRIiMAX "I64i"
#endif /* PRIiMAX */
#ifndef PRIoMAX
#define PRIoMAX "I64o"
#endif /* PRIoMAX */
#ifndef PRIuMAX
#define PRIuMAX "I64u"
#endif /* PRIuMAX */
#ifndef PRIxMAX
#define PRIxMAX "I64x"
#endif /* PRIxMAX */
#ifndef PRIXMAX
#define PRIXMAX "I64X"
#endif /* PRIXMAX */

#else /* _WIN32 */

#ifndef PRIdMAX
#define PRIdMAX "lld"
#endif /* PRIdMAX */
#ifndef PRIiMAX
#define PRIiMAX "lli"
#endif /* PRIiMAX */
#ifndef PRIoMAX
#define PRIoMAX "llo"
#endif /* PRIoMAX */
#ifndef PRIuMAX
#define PRIuMAX "llu"
#endif /* PRIuMAX */
#ifndef PRIxMAX
#define PRIxMAX "llx"
#endif /* PRIxMAX */
#ifndef PRIXMAX
#define PRIXMAX "llX"
#endif /* PRIXMAX */

#endif /* _WIN32 */

// Perform an unsigned cast to uintmax_t.
#define cast_to_largest_integral_type(value) \
    ((uintmax_t)((size_t)(value)))

/* Smallest integral type capable of holding a pointer. */
#ifndef _UINTPTR_T
#define _UINTPTR_T
#ifdef _WIN32

/* WIN32 is an ILP32 platform */
typedef unsigned long uintptr_t;
#endif /* _WIN32 */
#endif /* _UINTPTR_T */

/* Perform an unsigned cast to uintptr_t. */
#define cast_to_pointer_integral_type(value) \
	((uintptr_t)(value))

/* Perform a cast of a pointer to uintmax_t */
#define cast_ptr_to_largest_integral_type(value) \
cast_to_largest_integral_type(cast_to_pointer_integral_type(value))

// Retrieves a return value for the current function.
#define mock() _mock(__func__, __FILE__, __LINE__)

/* Stores a value to be returned by the specified function later.
 * The count parameter returns the number of times the value should be returned
 * by mock().  If count is set to -1 the value will always be returned.
 */
#define will_return(function, value) \
    _will_return(#function, __FILE__, __LINE__, \
                 cast_to_largest_integral_type(value), 1)
#define will_always_return(function, value) \
    _will_return(#function, __FILE__, __LINE__, \
                 cast_to_largest_integral_type(value), -1)
#define will_return_count(function, value, count) \
    _will_return(#function, __FILE__, __LINE__, \
                 cast_to_largest_integral_type(value), count)

/* Add a custom parameter checking function.  If the event parameter is NULL
 * the event structure is allocated internally by this function.  If event
 * parameter is provided it must be allocated on the heap and doesn't need to
 * be deallocated by the caller.
 */
#define expect_check(function, parameter, check_function, check_data) \
    _expect_check(#function, #parameter, __FILE__, __LINE__, check_function, \
                  cast_to_largest_integral_type(check_data), NULL, 1)

/* Add an event to check a parameter, using check_expected(), against a set of
 * values. See will_return() for a description of the count parameter.
 */
#define expect_in_set(function, parameter, value_array) \
    expect_in_set_count(function, parameter, value_array, 1)
#define expect_in_set_count(function, parameter, value_array, count) \
    _expect_in_set(#function, #parameter, __FILE__, __LINE__, value_array, \
                   sizeof(value_array) / sizeof((value_array)[0]), count)
#define expect_not_in_set(function, parameter, value_array) \
    expect_not_in_set_count(function, parameter, value_array, 1)
#define expect_not_in_set_count(function, parameter, value_array, count) \
    _expect_not_in_set( \
        #function, #parameter, __FILE__, __LINE__, value_array, \
        sizeof(value_array) / sizeof((value_array)[0]), count)


/* Add an event to check a parameter, using check_expected(), against a
 * signed range.  Where range is minimum <= value <= maximum.
 * See will_return() for a description of the count parameter.
 */
#define expect_in_range(function, parameter, minimum, maximum) \
    expect_in_range_count(function, parameter, minimum, maximum, 1)
#define expect_in_range_count(function, parameter, minimum, maximum, count) \
    _expect_in_range(#function, #parameter, __FILE__, __LINE__, minimum, \
                     maximum, count)

/* Add an event to check a parameter, using check_expected(), against a
 * signed range.  Where range is value < minimum or value > maximum.
 * See will_return() for a description of the count parameter.
 */
#define expect_not_in_range(function, parameter, minimum, maximum) \
    expect_not_in_range_count(function, parameter, minimum, maximum, 1)
#define expect_not_in_range_count(function, parameter, minimum, maximum, \
                                  count) \
    _expect_not_in_range(#function, #parameter, __FILE__, __LINE__, \
                         minimum, maximum, count)

/* Add an event to check whether a parameter, using check_expected(), is or
 * isn't a value.  See will_return() for a description of the count parameter.
 */
#define expect_value(function, parameter, value) \
    expect_value_count(function, parameter, value, 1)
#define expect_value_count(function, parameter, value, count) \
    _expect_value(#function, #parameter, __FILE__, __LINE__, \
                  cast_to_largest_integral_type(value), count)
#define expect_not_value(function, parameter, value) \
    expect_not_value_count(function, parameter, value, 1)
#define expect_not_value_count(function, parameter, value, count) \
    _expect_not_value(#function, #parameter, __FILE__, __LINE__, \
                      cast_to_largest_integral_type(value), count)

/* Add an event to check whether a parameter, using check_expected(),
 * is or isn't a string.  See will_return() for a description of the count
 * parameter.
 */
#define expect_string(function, parameter, string) \
    expect_string_count(function, parameter, string, 1)
#define expect_string_count(function, parameter, string, count) \
    _expect_string(#function, #parameter, __FILE__, __LINE__, \
                   (const char*)(string), count)
#define expect_not_string(function, parameter, string) \
    expect_not_string_count(function, parameter, string, 1)
#define expect_not_string_count(function, parameter, string, count) \
    _expect_not_string(#function, #parameter, __FILE__, __LINE__, \
                       (const char*)(string), count)

/* Add an event to check whether a parameter, using check_expected() does or
 * doesn't match an area of memory.  See will_return() for a description of
 * the count parameter.
 */
#define expect_memory(function, parameter, memory, size) \
    expect_memory_count(function, parameter, memory, size, 1)
#define expect_memory_count(function, parameter, memory, size, count) \
    _expect_memory(#function, #parameter, __FILE__, __LINE__, \
                   (const void*)(memory), size, count)
#define expect_not_memory(function, parameter, memory, size) \
    expect_not_memory_count(function, parameter, memory, size, 1)
#define expect_not_memory_count(function, parameter, memory, size, count) \
    _expect_not_memory(#function, #parameter, __FILE__, __LINE__, \
                       (const void*)(memory), size, count)


/* Add an event to allow any value for a parameter checked using
 * check_expected().  See will_return() for a description of the count
 * parameter.
 */
#define expect_any(function, parameter) \
    expect_any_count(function, parameter, 1)
#define expect_any_count(function, parameter, count) \
    _expect_any(#function, #parameter, __FILE__, __LINE__, count)

/* Determine whether a function parameter is correct.  This ensures the next
 * value queued by one of the expect_*() macros matches the specified variable.
 */
#define check_expected(parameter) \
    _check_expected(__func__, #parameter, __FILE__, __LINE__, \
                    cast_to_largest_integral_type(parameter))

/*
 * Assert that the given function have been called a specific number of times,
 * otherwise fail.
 */
#define assert_func_call_count_equal(function, callCount) \
	_assert_func_call_count_equal(#function, callCount, __FILE__, __LINE__)

/*
 * Assert that the given function have been called at least a number of times,
 * otherwise fail.
 */
#define assert_func_call_count_at_least(function, callCount) \
	_assert_func_call_count_at_least(#function, callCount, __FILE__, __LINE__)

/*
 * Assert that the given function have been called at most a number of times,
 * otherwise fail.
 */
#define assert_func_call_count_at_most(function, callCount) \
	_assert_func_call_count_at_most(#function, callCount, __FILE__, __LINE__)

/*
 * Assert that the given function haven't been called, otherwise fail.
 */
#define assert_func_not_call(function) \
	assert_func_call_count_equal(#function, -1L)

/*
 * Increments the function call counter of the function in which this macro
 * is called.
 */
#define inc_func_call_count() \
	_inc_func_call_count(__func__, __FILE__, __LINE__)

/*
 * Returns the function call counter of a function.
 */
#define get_func_call_count(function) \
	_get_func_call_count(#function)

/*
 * Resets the function call counter of a function.
 */
#define reset_func_call_count(function) \
	_reset_func_call_count(#function)

// Assert that the given expression is true.
#define assert_true(c) _assert_true(cast_to_largest_integral_type(c), #c, \
                                    __FILE__, __LINE__)
// Assert that the given expression is false.
#define assert_false(c) _assert_true(!(cast_to_largest_integral_type(c)), #c, \
                                     __FILE__, __LINE__)

// Assert that the given pointer is non-NULL.
#define assert_non_null(c) _assert_true(cast_ptr_to_largest_integral_type(c), #c, \
__FILE__, __LINE__)
// Assert that the given pointer is NULL.
#define assert_null(c) _assert_true(!(cast_ptr_to_largest_integral_type(c)), #c, \
__FILE__, __LINE__)

// Assert two given pointers are equal
#define assert_ptr_equal(a, b) \
    _assert_int_equal(cast_ptr_to_largest_integral_type(a), \
                      cast_ptr_to_largest_integral_type(b), \
                      __FILE__, __LINE__)
// Assert that the two given integers are not equal, otherwise fail.
#define assert_ptr_not_equal(a, b) \
    _assert_int_not_equal(cast_ptr_to_largest_integral_type(a), \
                          cast_ptr_to_largest_integral_type(b), \
                          __FILE__, __LINE__)

// Assert that the two given integers are equal, otherwise fail.
#define assert_int_equal(a, b) \
    _assert_int_equal(cast_to_largest_integral_type(a), \
                      cast_to_largest_integral_type(b), \
                      __FILE__, __LINE__)
// Assert that the two given integers are not equal, otherwise fail.
#define assert_int_not_equal(a, b) \
    _assert_int_not_equal(cast_to_largest_integral_type(a), \
                          cast_to_largest_integral_type(b), \
                          __FILE__, __LINE__)

// Assert that the two given strings are equal, otherwise fail.
#define assert_string_equal(a, b) \
    _assert_string_equal((const char*)(a), (const char*)(b), __FILE__, \
                         __LINE__)
// Assert that the two given strings are not equal, otherwise fail.
#define assert_string_not_equal(a, b) \
    _assert_string_not_equal((const char*)(a), (const char*)(b), __FILE__, \
                             __LINE__)

// Assert that the two given areas of memory are equal, otherwise fail.
#define assert_memory_equal(a, b, size) \
    _assert_memory_equal((const char*)(a), (const char*)(b), size, __FILE__, \
                         __LINE__)
// Assert that the two given areas of memory are not equal, otherwise fail.
#define assert_memory_not_equal(a, b, size) \
    _assert_memory_not_equal((const char*)(a), (const char*)(b), size, \
                             __FILE__, __LINE__)

// Assert that the specified value is >= minimum and <= maximum.
#define assert_in_range(value, minimum, maximum) \
    _assert_in_range( \
        cast_to_largest_integral_type(value), \
        cast_to_largest_integral_type(minimum), \
        cast_to_largest_integral_type(maximum), __FILE__, __LINE__)

// Assert that the specified value is < minimum or > maximum
#define assert_not_in_range(value, minimum, maximum) \
    _assert_not_in_range( \
        cast_to_largest_integral_type(value), \
        cast_to_largest_integral_type(minimum), \
        cast_to_largest_integral_type(maximum), __FILE__, __LINE__)

// Assert that the specified value is within a set.
#define assert_in_set(value, values, number_of_values) \
    _assert_in_set(value, values, number_of_values, __FILE__, __LINE__)
// Assert that the specified value is not within a set.
#define assert_not_in_set(value, values, number_of_values) \
    _assert_not_in_set(value, values, number_of_values, __FILE__, __LINE__)


// Forces the test to fail immediately and quit.
#define fail() _fail(__FILE__, __LINE__)

// Initializes a UnitTest structure.
#define unit_test(f) { #f, f, UNIT_TEST_FUNCTION_TYPE_TEST }
#define unit_test_setup(test, setup) \
    { #test "_" #setup, setup, UNIT_TEST_FUNCTION_TYPE_SETUP }
#define unit_test_teardown(test, teardown) \
    { #test "_" #teardown, teardown, UNIT_TEST_FUNCTION_TYPE_TEARDOWN }

// Used only for cmockery internal tests
#define unit_test_expect_failure(f) \
    { #f, f, UNIT_TEST_FUNCTION_TYPE_TEST_EXPECT_FAILURE}

/* Initialize an array of UnitTest structures with a setup function for a test
 * and a teardown function.  Either setup or teardown can be NULL.
 */
#define unit_test_setup_teardown(test, setup, teardown) \
    unit_test_setup(test, setup), \
    unit_test(test), \
    unit_test_teardown(test, teardown)

/*
 * Run tests specified by an array of UnitTest structures.  The following
 * example illustrates this macro's use with the unit_test macro.
 *
 * void Test0();
 * void Test1();
 *
 * int main(int argc, char* argv[]) {
 *     const UnitTest tests[] = {
 *         unit_test(Test0);
 *         unit_test(Test1);
 *     };
 *     return run_tests(tests);
 * }
 */
#define run_tests(tests, test_suite_name) _run_tests(tests, \
        sizeof(tests) / sizeof(tests)[0], \
        (test_suite_name))

// Dynamic allocators
#define test_malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define test_calloc(num, size) _test_calloc(num, size, __FILE__, __LINE__)
#define test_free(ptr) _test_free(ptr, __FILE__, __LINE__)

/*
 * Ensure mock_assert() is called.  If mock_assert() is called the assert
 * expression string is returned.
 * For example:
 *
 * #define assert mock_assert
 *
 * void showmessage(const char *message) {
 *   assert(message);
 * }
 *
 * int main(int argc, const char* argv[]) {
 *   expect_assert_failure(show_message(NULL));
 *   printf("succeeded\n");
 *   return 0;
 * }
 */
#define expect_assert_failure(function_call) \
  { \
    const int result = setjmp(global_expect_assert_env); \
    global_expecting_assert = 1; \
    if (result) { \
      print_message("Expected assertion %s occurred\n", \
                    global_last_failed_assert); \
      global_expecting_assert = 0; \
    } else { \
      function_call ; \
      global_expecting_assert = 0; \
      print_error("Expected assert in %s\n", #function_call); \
      _fail(__FILE__, __LINE__); \
    } \
  }

// Function prototype for setup, test and teardown functions.
typedef void (*UnitTestFunction)(void **state);

// Function that determines whether a function parameter value is correct.
typedef int (*CheckParameterValue)(const uintmax_t value,
                                   const uintmax_t check_value_data);

// Type of the unit test function.
typedef enum UnitTestFunctionType {
        /** Normal unit test */
    UNIT_TEST_FUNCTION_TYPE_TEST = 0,
        /** Setup state for a unit test */
    UNIT_TEST_FUNCTION_TYPE_SETUP,
        /** Teardown state used by a unit test */
    UNIT_TEST_FUNCTION_TYPE_TEARDOWN,
        /** Used only for cmockery internal tests */
    UNIT_TEST_FUNCTION_TYPE_TEST_EXPECT_FAILURE,
} UnitTestFunctionType;

/* Stores a unit test function with its name and type.
 * NOTE: Every setup function must be paired with a teardown function.  It's
 * possible to specify NULL function pointers.
 */
typedef struct UnitTest {
    const char* name;
    UnitTestFunction function;
    UnitTestFunctionType function_type;
} UnitTest;


// Location within some source code.
typedef struct SourceLocation {
    const char* file;
    int line;
} SourceLocation;

// Event that's called to check a parameter value.
typedef struct CheckParameterEvent {
    SourceLocation location;
    const char *parameter_name;
    CheckParameterValue check_value;
    uintmax_t check_value_data;
} CheckParameterEvent;


typedef struct FunctionCallEvent {
    SourceLocation location;
    uintmax_t func_call_count;
} FunctionCallEvent;

// Used by expect_assert_failure() and mock_assert().
extern volatile int global_expecting_assert;
extern jmp_buf global_expect_assert_env;
extern const char * global_last_failed_assert;

// Retrieves a value for the given function, as set by "will_return".
uintmax_t _mock(const char * const function, const char* const file,
                          const int line);

void _expect_check(
    const char* const function, const char* const parameter,
    const char* const file, const int line,
    const CheckParameterValue check_function,
    const uintmax_t check_data, CheckParameterEvent * const event,
    const int count);

void _expect_in_set(
    const char* const function, const char* const parameter,
    const char* const file, const int line, const uintmax_t values[],
    const size_t number_of_values, const int count);
void _expect_not_in_set(
    const char* const function, const char* const parameter,
    const char* const file, const int line, const uintmax_t values[],
    const size_t number_of_values, const int count);

void _expect_in_range(
    const char* const function, const char* const parameter,
    const char* const file, const int line,
    const uintmax_t minimum,
    const uintmax_t maximum, const int count);
void _expect_not_in_range(
    const char* const function, const char* const parameter,
    const char* const file, const int line,
    const uintmax_t minimum,
    const uintmax_t maximum, const int count);

void _expect_value(
    const char* const function, const char* const parameter,
    const char* const file, const int line, const uintmax_t value,
    const int count);
void _expect_not_value(
    const char* const function, const char* const parameter,
    const char* const file, const int line, const uintmax_t value,
    const int count);

void _expect_string(
    const char* const function, const char* const parameter,
    const char* const file, const int line, const char* string,
    const int count);
void _expect_not_string(
    const char* const function, const char* const parameter,
    const char* const file, const int line, const char* string,
    const int count);

void _expect_memory(
    const char* const function, const char* const parameter,
    const char* const file, const int line, const void* const memory,
    const size_t size, const int count);
void _expect_not_memory(
    const char* const function, const char* const parameter,
    const char* const file, const int line, const void* const memory,
    const size_t size, const int count);

void _expect_any(
    const char* const function, const char* const parameter,
    const char* const file, const int line, const int count);

void _check_expected(
    const char * const function_name, const char * const parameter_name,
    const char* file, const int line, const uintmax_t value);

void _will_return(const char * const function_name, const char * const file,
                  const int line, const uintmax_t value,
                  const int count);
void _assert_true(const uintmax_t result,
                  const char* const expression,
                  const char * const file, const int line);
void _assert_int_equal(
    const uintmax_t a, const uintmax_t b,
    const char * const file, const int line);
void _assert_int_not_equal(
    const uintmax_t a, const uintmax_t b,
    const char * const file, const int line);
void _assert_string_equal(const char * const a, const char * const b,
                          const char * const file, const int line);
void _assert_string_not_equal(const char * const a, const char * const b,
                              const char *file, const int line);
void _assert_memory_equal(const void * const a, const void * const b,
                          const size_t size, const char* const file,
                          const int line);
void _assert_memory_not_equal(const void * const a, const void * const b,
                              const size_t size, const char* const file,
                              const int line);
void _assert_in_range(
    const uintmax_t value, const uintmax_t minimum,
    const uintmax_t maximum, const char* const file, const int line);
void _assert_not_in_range(
    const uintmax_t value, const uintmax_t minimum,
    const uintmax_t maximum, const char* const file, const int line);
void _assert_in_set(
    const uintmax_t value, const uintmax_t values[],
    const size_t number_of_values, const char* const file, const int line);
void _assert_not_in_set(
    const uintmax_t value, const uintmax_t values[],
    const size_t number_of_values, const char* const file, const int line);

void _inc_func_call_count(
        const char * const function_name, const char* file, const int line);
int _get_func_call_count(const char * const function_name);
void _reset_func_call_count(const char * const function_name);
void _assert_func_call_count_equal(const char* const function, const int callCount,
		const char* file, const int line);
void _assert_func_call_count_at_least(const char* const function, const int callCount,
		const char* file, const int line);
void _assert_func_call_count_at_most(const char* const function, const int callCount,
		const char* file, const int line);

void _fail(const char * const file, const int line);

// test_suite_name is the prefix to the %s_xunit.xml report
int _run_tests(const UnitTest * const tests,
        const size_t number_of_tests,
        const char *test_suite_name);

// Standard output and error print methods.
void print_error(const char* const format, ...);
void vprint_message(const char* const format, va_list args);
void vprint_error(const char* const format, va_list args);

#endif // CMOCKERY_H_
