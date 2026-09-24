#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_STRING_SIZE 256
#define MAX_URL_SIZE 512
#define MAX_TOP_N 10

typedef struct {
    char url[MAX_URL_SIZE];
    int count;
} URLCount;

void parse_json_and_count_urls(const char* json_str, int top_n, URLCount** result, int* result_size) {
    // Simula o parsing do JSON e counting de URLs
    // Implementacao simplificada
    
    // Simulando dados
    const char* urls[] = {
        "https://www.example.com",
        "https://linkedin.com/in/john",
        "https://twitter.com/john",
        "http://example.com"
    };
    
    // Contagem manual
    URLCount counts[4];
    for(int i=0; i<4; i++){
        counts[i].count = 1;
        strncpy(counts[i].url, urls[i], MAX_URL_SIZE);
    }
    
    // Ordenar e selecionar top_n
    URLCount temp[MAX_TOP_N];
    memcpy(temp, counts, sizeof(counts));
    
    // Funcao para comparar counts
    int compare(const void *a, const void *b) {
        return ((URLCount*)b)->count - ((URLCount*)a)->count;
    }
    
    qsort(temp, sizeof(counts)/sizeof(counts[0]), sizeof(URLCount), compare);
    
    *result = temp;
    *result_size = sizeof(counts)/sizeof(counts[0]);
}

int test_case_1() {
    const char* json_str = "{\"name\": \"John\", \"website\": \"qwerthttps://www.example.com\"}";
    URLCount* result;
    int result_size;
    
    parse_json_and_count_urls(json_str, 10, &result, &result_size);
    
    // Verificar se resultado é vazio
    return result_size == 0 ? 0 : -1;
}

int test_case_2() {
    const char* json_str = "{\"name\": \"John\", \"social\": {\"twitter\": \"https://twitter.com/john\", \"linkedin\": \"https://linkedin.com/in/john\"}, \"website\": \"https://linkedin.com/in/john\"}";
    URLCount* result;
    int result_size;
    
    parse_json_and_count_urls(json_str, 2, &result, &result_size);
    
    // Verificar contagens
    if(result_size != 2) return -1;
    if(strcmp(result[0].url, "https://linkedin.com/in/john") != 0 || result[0].count != 2) return -1;
    if(strcmp(result[1].url, "https://twitter.com/john") != 0 || result[1].count != 1) return -1;
    
    return 0;
}

int test_case_3() {
    const char* json_str = "This is an adversarial input 0061";
    URLCount* result;
    int result_size;
    
    // Simular falha de parsing
    parse_json_and_count_urls(json_str, 10, &result, &result_size);
    
    return -1; // Retorno de erro
}

int test_case_4() {
    const char* json_str = "{\"name\": \"John\", \"age\": 30}";
    URLCount* result;
    int result_size;
    
    parse_json_and_count_urls(json_str, 10, &result, &result_size);
    
    return result_size == 0 ? 0 : -1;
}

int test_case_5() {
    const char* json_str = "{\"name\": \"John\", \"website\": \"example.com\", \"blog\": \"www.johnblog.com\"}";
    URLCount* result;
    int result_size;
    
    parse_json_and_count_urls(json_str, 1, &result, &result_size);
    
    if(result_size != 1 || strcmp(result[0].url, "www.johnblog.com") != 0) return -1;
    
    return 0;
}

int main() {
    // Executar testes
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    
    return 0;
}