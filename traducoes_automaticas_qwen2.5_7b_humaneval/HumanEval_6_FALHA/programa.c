#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[128];
    int value;
} NivelNesting;

typedef struct {
    char* group;
    int max_depth;
} NivelNestingGroup;

int parse_paren_group(const char* s, NivelNestingGroup* max_depth) {
    int depth = 0;
    max_depth->max_depth = 0;
    while (*s) {
        if (*s == '(') {
            depth++;
            max_depth->max_depth = depth > max_depth->max_depth ? depth : max_depth->max_depth;
        } else if (*s == ')') {
            depth--;
        }
        s++;
    }
    return max_depth->max_depth;
}

int parse_nested_parens(const char* paren_string, NivelNestingGroup** groups) {
    *groups = (NivelNestingGroup*)malloc(strlen(paren_string) * sizeof(NivelNestingGroup));
    int count = 0;
    const char* start = paren_string;
    while (*paren_string) {
        if (*paren_string == ' ') {
            parse_paren_group(start, &groups[count]);
            count++;
            start = paren_string + 1;
        }
        paren_string++;
    }
    parse_paren_group(start, &groups[count]);
    count++;
    return count;
}

void free_groups(NivelNestingGroup* groups, int count) {
    for (int i = 0; i < count; i++) {
        free(groups[i].group);
    }
    free(groups);
}

int main() {
    NivelNestingGroup* groups;
    int count = parse_nested_parens("(()()) ((())) () ((())()())", &groups);
    int expected[] = {2, 3, 1, 3};
    for (int i = 0; i < count; i++) {
        assert(groups[i].max_depth == expected[i]);
    }
    free_groups(groups, count);

    NivelNestingGroup* groups2;
    count = parse_nested_parens("() (()) ((())) (((())))", &groups2);
    int expected2[] = {1, 2, 3, 4};
    for (int i = 0; i < count; i++) {
        assert(groups2[i].max_depth == expected2[i]);
    }
    free_groups(groups2, count);

    NivelNestingGroup* groups3;
    count = parse_nested_parens("(()(())((())))", &groups3);
    int expected3[] = {4};
    assert(groups3[0].max_depth == expected3[0]);
    free_groups(groups3, 1);

    return 0;
}