#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* Estruturas e funções auxiliares */

/* Função que calcula a profundidade máxima de parênteses em uma
   string que contém somente '(' e ')' */
int parse_paren_group(const char *s)
{
    int depth = 0;
    int max_depth = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '(')
        {
            depth += 1;
            if (depth > max_depth)
                max_depth = depth;
        }
        else /* assume ')' */
        {
            depth -= 1;
        }
    }
    return max_depth;
}

/* Função principal: recebe uma string contendo vários grupos de
   parênteses separados por espaços e devolve, em 'out',
   a profundidade máxima de cada grupo.  O número de grupos é
   escrito em '*out_len'.
   Retorno: 0 em caso de sucesso.  */
int parse_nested_parens(const char *paren_string, int *out, int *out_len)
{
    /* Limites máximos usados pelos testes */
    const int MAX_GROUPS = 100;
    const int MAX_GROUP_LEN = 256;

    int groups = 0;
    char group[MAX_GROUP_LEN];
    int group_len = 0;

    for (int i = 0; paren_string[i] != '\0'; i++)
    {
        char c = paren_string[i];
        if (c == ' ')
        {
            if (group_len > 0)
            {
                group[group_len] = '\0';
                if (groups < MAX_GROUPS)
                {
                    out[groups++] = parse_paren_group(group);
                }
                group_len = 0;
            }
        }
        else
        {
            if (group_len < MAX_GROUP_LEN - 1)
            {
                group[group_len++] = c;
            }
        }
    }
    /* último grupo (se houver) */
    if (group_len > 0)
    {
        group[group_len] = '\0';
        if (groups < MAX_GROUPS)
        {
            out[groups++] = parse_paren_group(group);
        }
    }

    *out_len = groups;
    return 0;
}

/* Funções de teste */

/* Compara dois arrays de inteiros de tamanho 'len'.
   Asserta que são iguais. */
void test_compare_array(const int *expected, const int *actual, int len)
{
    for (int i = 0; i < len; i++)
    {
        assert(expected[i] == actual[i]);
    }
}

/* Testes baseados nos exemplos fornecidos */
void run_tests()
{
    int out[100];
    int out_len;
    int ret;

    /* Teste 1 */
    ret = parse_nested_parens("(()()) ((())) () ((())()())", out, &out_len);
    assert(ret == 0);
    assert(out_len == 4);
    int expected1[4] = {2, 3, 1, 3};
    test_compare_array(expected1, out, out_len);

    /* Teste 2 */
    ret = parse_nested_parens("() (()) ((())) (((())))", out, &out_len);
    assert(ret == 0);
    assert(out_len == 4);
    int expected2[4] = {1, 2, 3, 4};
    test_compare_array(expected2, out, out_len);

    /* Teste 3 */
    ret = parse_nested_parens("(()(())((())))", out, &out_len);
    assert(ret == 0);
    assert(out_len == 1);
    int expected3[1] = {4};
    test_compare_array(expected3, out, out_len);
}

/* Função principal que executa os testes */
int main()
{
    run_tests();
    return 0;
}