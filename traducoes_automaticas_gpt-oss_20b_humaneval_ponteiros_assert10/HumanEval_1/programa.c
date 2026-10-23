#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Structs and typedefs -----------------------------------------------------*/
#define MAX_GROUPS 100
#define MAX_GROUP_LEN 256

/* Function prototypes -------------------------------------------------------*/
int separate_paren_groups(const char *paren_string,
                          char result[][MAX_GROUP_LEN],
                          int *out_count);

/* Helper function to compare two arrays of strings --------------------------------*/
void assert_groups_equal(const char expected[][MAX_GROUP_LEN],
                         int expected_count,
                         const char actual[][MAX_GROUP_LEN],
                         int actual_count) {
    assert(expected_count == actual_count);
    for (int i = 0; i < expected_count; ++i) {
        assert(strcmp(expected[i], actual[i]) == 0);
    }
}

/* Tests ---------------------------------------------------------------------*/
void run_tests(void) {
    /* Test 1 */
    {
        const char *input = "(()()) ((())) () ((())()())";
        const char expected[][MAX_GROUP_LEN] = {
            "(()())", "((()))", "()", "((())()())"
        };
        char result[MAX_GROUPS][MAX_GROUP_LEN];
        int count;
        int status = separate_paren_groups(input, result, &count);
        assert(status == 0);
        assert_groups_equal(expected, 4, result, count);
    }

    /* Test 2 */
    {
        const char *input = "() (()) ((())) (((())))";
        const char expected[][MAX_GROUP_LEN] = {
            "()", "(())", "((()))", "(((())))"
        };
        char result[MAX_GROUPS][MAX_GROUP_LEN];
        int count;
        int status = separate_paren_groups(input, result, &count);
        assert(status == 0);
        assert_groups_equal(expected, 4, result, count);
    }

    /* Test 3 */
    {
        const char *input = "(()(())((())))";
        const char expected[][MAX_GROUP_LEN] = {
            "(()(())((())))"
        };
        char result[MAX_GROUPS][MAX_GROUP_LEN];
        int count;
        int status = separate_paren_groups(input, result, &count);
        assert(status == 0);
        assert_groups_equal(expected, 1, result, count);
    }

    /* Test 4 */
    {
        const char *input = "( ) (( )) (( )( ))";
        const char expected[][MAX_GROUP_LEN] = {
            "()", "(())", "(()())"
        };
        char result[MAX_GROUPS][MAX_GROUP_LEN];
        int count;
        int status = separate_paren_groups(input, result, &count);
        assert(status == 0);
        assert_groups_equal(expected, 3, result, count);
    }
}

/* Main -----------------------------------------------------------------------*/
int main(void) {
    run_tests();
    return 0;
}

/* Implementation of separate_paren_groups -----------------------------------*/
int separate_paren_groups(const char *paren_string,
                          char result[][MAX_GROUP_LEN],
                          int *out_count) {
    int current_depth = 0;
    char current[MAX_GROUP_LEN];
    int cur_len = 0;
    int groups = 0;

    for (const char *p = paren_string; *p != '\0'; ++p) {
        char c = *p;
        if (c == ' ') {
            continue; /* ignore spaces */
        }
        if (c == '(') {
            if (current_depth == 0 && cur_len == 0) {
                /* start of a new group */
            }
            current_depth++;
            if (cur_len < MAX_GROUP_LEN - 1) {
                current[cur_len++] = c;
            }
        } else if (c == ')') {
            current_depth--;
            if (cur_len < MAX_GROUP_LEN - 1) {
                current[cur_len++] = c;
            }
            if (current_depth == 0) {
                current[cur_len] = '\0';
                if (groups < MAX_GROUPS) {
                    strcpy(result[groups], current);
                    groups++;
                }
                cur_len = 0;
            }
        } else {
            /* ignore any other characters (not expected) */
        }
    }

    *out_count = groups;
    return 0;
}