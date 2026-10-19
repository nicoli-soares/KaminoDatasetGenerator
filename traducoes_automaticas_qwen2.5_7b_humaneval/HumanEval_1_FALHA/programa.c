#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char chave[257];
    int valor;
} ParGrupoParenteses;

typedef struct {
    char* grupo;
    int tamanho;
} GrupoParenteses;

int compare(char* a, char* b) {
    return strcmp(a, b);
}

int separate_paren_groups_c(const char* paren_string, GrupoParenteses** result) {
    int result_size = 0;
    char* current_string = (char*)malloc(256 * sizeof(char));
    int current_depth = 0;

    if (current_string == NULL) {
        return -1; // Falha na alocação de memória
    }

    for (int i = 0; i < strlen(paren_string); i++) {
        if (paren_string[i] == '(') {
            current_depth += 1;
            current_string[current_depth - 1] = paren_string[i];
        } else if (paren_string[i] == ')') {
            current_depth -= 1;
            current_string[current_depth] = paren_string[i];

            if (current_depth == 0) {
                current_string[current_depth] = '\0';
                result[result_size] = (GrupoParenteses*)malloc(sizeof(GrupoParenteses));
                if (result[result_size] == NULL) {
                    free(current_string);
                    return -1; // Falha na alocação de memória
                }
                result[result_size]->grupo = (char*)malloc((current_depth + 1) * sizeof(char));
                if (result[result_size]->grupo == NULL) {
                    free(current_string);
                    return -1; // Falha na alocação de memória
                }
                strcpy(result[result_size]->grupo, current_string);
                result[result_size]->tamanho = current_depth;
                result_size++;
                current_depth = 0;
            }
        }
    }

    free(current_string);
    return result_size;
}

void test_separate_paren_groups_c() {
    GrupoParenteses* result1[3];
    int size1 = separate_paren_groups_c("( ) (( )) (( )( ))", &result1[0]);
    assert(size1 == 3);
    assert(strcmp(result1[0]->grupo, "()") == 0);
    assert(strcmp(result1[1]->grupo, "(())") == 0);
    assert(strcmp(result1[2]->grupo, "(()())") == 0);

    GrupoParenteses* result2[4];
    int size2 = separate_paren_groups_c("(()()) ((())) () ((())()())", &result2[0]);
    assert(size2 == 4);
    assert(strcmp(result2[0]->grupo, "(()())") == 0);
    assert(strcmp(result2[1]->grupo, "((()))") == 0);
    assert(strcmp(result2[2]->grupo, "()") == 0);
    assert(strcmp(result2[3]->grupo, "((())()())") == 0);

    GrupoParenteses* result3[1];
    int size3 = separate_paren_groups_c("(()(())((())))", &result3[0]);
    assert(size3 == 1);
    assert(strcmp(result3[0]->grupo, "(()(())((())))") == 0);

    GrupoParenteses* result4[3];
    int size4 = separate_paren_groups_c("( ) (( )) (( )( ))", &result4[0]);
    assert(size4 == 3);
    assert(strcmp(result4[0]->grupo, "()") == 0);
    assert(strcmp(result4[1]->grupo, "(())") == 0);
    assert(strcmp(result4[2]->grupo, "(()())") == 0);
}

int main() {
    test_separate_paren_groups_c();
    return 0;
}