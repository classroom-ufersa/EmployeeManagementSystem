#include <stdio.h>
#include <string.h>
#include "empresa.h" 
//#include "../TAD_cargo/cargo.c"
#include "../TAD_funcionario/funcionario.c"
#define TAM_LINHA 200
#define TAM_NOME 50

struct empresa {
    char CNPJ[15];
    char nome[TAM_NOME];
    char localizacao[100];
    float receita;
    float valor_de_mercado;
    CargosList *c_list;
    FuncionariosList *f_list;
    int num_funcionarios;
};

Empresa *empresa_cria(char *CNPJ, char *nome, char *localizacao, float receita, float valor_de_mercado) {
    Empresa* e = (Empresa*) malloc(sizeof(Empresa));
    // inserindo as informações passadas por parametro
    strcpy(e->CNPJ, CNPJ);
    strcpy(e->nome, nome);
    strcpy(e->localizacao, localizacao);
    e->receita = receita;
    e->valor_de_mercado = valor_de_mercado;

    return e;
}

Empresa *empresa_obter() {
    Empresa *empresa_arquivo;
    FILE *arquivo_origem;
    char linha[TAM_LINHA], CNPJ[15], nome[TAM_NOME], localizacao[100];
    float receita, valor_de_mercado;

    // lendo arquivo com as informacoes da empresa
    arquivo_origem = fopen("TAD_empresa/dados_empresa.txt", "r");
    if (arquivo_origem == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    while (fgets(linha, TAM_LINHA, arquivo_origem) != NULL) {
        sscanf(linha, " %[^;];%[^;];%[^;];%f;%f", CNPJ, nome, localizacao, &receita, &valor_de_mercado);
    } 

    empresa_arquivo = empresa_cria(CNPJ, nome, localizacao, receita, valor_de_mercado);
    fclose(arquivo_origem); // fecha o arquivo 

    return empresa_arquivo;
}

void empresa_imprime(Empresa *empresa) {
    printf("\n-------------INFORMAÇÕES DA EMPRESA-------------\n");
    printf("Nome da empresa: %s\n", empresa->nome);
    printf("CNPJ: %s\n", empresa->CNPJ);
    printf("Localização: %s\n", empresa->localizacao);
    printf("Receita: R$%.2f\n", empresa->receita);
    printf("Valor de mercado: R$%.2f\n", empresa->valor_de_mercado);
}

// void consulta_funcionarios_por_cargo (Empresa *empresa);