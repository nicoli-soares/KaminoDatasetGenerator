#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct {
    char group[256];
} ParenGroup;

int separate_paren_groups_c(const char *paren_string, int n, ParenGroup *groups, int *ngroups) {
    int current_depth = 0;
    int current_index = 0;
    int group_count = 0;

    for (int i = 0; i < n; i++) {
        if (paren_string[i] == '(') {
            current_depth++;
        } else if (paren_string[i] == ')') {
            current_depth--;
            if (current_depth == 0) {
                groups[group_count].group[current_index] = '\0';
                current_index = 0;
                group_count++;
            } else {
                groups[group_count].group[current_index++] = paren_string[i];
            }
        } else {
            continue;
        }
    }

    *ngroups = group_count;
    return 0;
}

int main() {
    ParenGroup groups[100];
    int ngroups;

    // Test 1
    separate_paren_groups_c("(()()) ((())) () ((())()())", 25, groups, &ngroups);
    assert(strcmp(groups[0].group, "(()())") == 0);
    assert(strcmp(groups[1].group, "(())") == 0);
    assert(strcmp(groups[2].group, "()") == 0);
    assert(strcmp(groups[3].group, "(()())") == 0);
    assert(ngroups == 4);

    // Test 2
    separate_paren_groups_c("() (()) ((())) (((())))", 26, groups, &ngroups);
    assert(strcmp(groups[0].group, "()") == 0);
    assert(strcmp(groups[1].group, "(())") == 0);
    assert(strcmp(groups[2].group, "((()))") == 0);
    assert(strcmp(groups[3].group, "(((())))") == 0);
    assert(ngroups == 4);

    // Test 3
    separate_paren_groups_c("(()(())((())))", 17, groups, &ngroups);
    assert(strcmp(groups[0].group, "(()(())((())))") == 0);
    assert(ngroups == 1);

    // Test 4
    separate_paren_groups_c("( ) (( )) (( )( ))", 21, groups, &ngroups);
    assert(strcmp(groups[0].group, "()") == 0);
    assert(strcmp(groups[1].group, "(())") == 0);
    assert(strcmp(groups[2].group, "(()())") == 0);
    assert(ngroups == 3);

    printf("All tests passed!\n");
    return 0;
}