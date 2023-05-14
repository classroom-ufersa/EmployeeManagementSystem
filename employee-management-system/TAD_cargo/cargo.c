#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cargo.h"
#define TAM_LINHA 200
#define TAM_NOME 50

struct cargo {
    int ID;
    int qtd_funcionarios;
    char nome_cargo[TAM_NOME];
    char setor[TAM_NOME];
};

struct cargoslist {
    Cargo *info;
    int ultimo_id_cargo_adicionado;
    int qtd_cargos;
    struct cargoslist *next;
    struct cargoslist *prev;
};

CargosList* cargo_cria(void) {
    return NULL;
}

CargosList* cargo_insere(CargosList* c_list, int ID, int qtd_funcionarios, char *nome_cargo, char *setor, int *qtd_cargos) {
    Cargo *cargo = (Cargo*) malloc(sizeof(Cargo));
    CargosList *novo = (CargosList*) malloc(sizeof(CargosList));   

    // inserindo as informações passadas pelo usuário
    cargo->ID = ID;
    cargo->qtd_funcionarios = qtd_funcionarios;
    strcpy(cargo->nome_cargo , nome_cargo);
    strcpy(cargo->setor, setor);

    novo->info = cargo;
    novo->qtd_cargos = ++(*qtd_cargos);
    // adicionando de fato o nó na lista
    novo->next = c_list;
    novo->prev = NULL;
    // verifica se a lista não está vazia
    if (c_list != NULL)
        c_list->prev = novo;
    
    // atualiza_arquivo(novo);
    return novo;
}

CargosList* obter_cargos(CargosList *c_list) {
    FILE *arquivo_origem;
    CargosList *new_list = c_list;
    char linha[TAM_LINHA], nome_cargo[TAM_NOME], setor[TAM_NOME];
    int ID, qtd_funcionarios, qtd_cargos = 0,  maior_id = 0;

    // lendo arquivo com as informacoes dos funcionarios
    arquivo_origem = fopen("TAD_cargo/dados_cargos.txt", "r"); // abre o arquivo_origem para leitura
    if (arquivo_origem == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    while (fgets(linha, TAM_LINHA, arquivo_origem) != NULL) { 
        sscanf(linha, "%d;%[^;];%[^;];%d", &ID, nome_cargo, setor, &qtd_funcionarios); 
        new_list = cargo_insere(new_list, ID, qtd_funcionarios, nome_cargo, setor, &qtd_cargos);
    
        if (ID > maior_id)
            maior_id = ID;
            
        new_list->ultimo_id_cargo_adicionado = maior_id;
    }

    fclose(arquivo_origem); // fecha o arquivo
    return new_list;
}

int cargo_lst_vazia(CargosList* c_list) {
    if (c_list == NULL)
        return 1;
    else 
        return 0;
}

void cargo_imprime(CargosList *c_list) {
    if (cargo_lst_vazia(c_list)) {
        printf("Nenhum cargo encontrado no Sistema!\n");
    } else{
        CargosList* c;
        printf("\n------------LISTA DE CARGOS------------\n");
        for (c = c_list; c != NULL; c = c->next) {
            printf("Cargo: %s\n", c->info->nome_cargo);    
            printf("ID: %d\n", c->info->ID);
            printf("Setor: %s\n", c->info->setor); 
            printf("Quantidade de funcionarios: %d\n\n", c->info->qtd_funcionarios); 
        }
    }
}

CargosList* cargo_busca(CargosList* c_list, int ID) {
    CargosList* c;
    if (cargo_lst_vazia(c_list)) {
        printf("ERRO: lista vazia!\n");
        return NULL;
    } else {
        for (c = c_list; c != NULL; c = c->next) {
            if(c->info->ID == ID) {
                return c;
            }
        }
    }
    return NULL; // não achou o elemento buscado     
}

CargosList* cargo_retira(CargosList* c_list, int ID, int *qtd_cargos) {
    CargosList* p = cargo_busca(c_list, ID);

    // verifica se achou elemento
    if (p == NULL) {
        printf("Cargo com ID %d não encontrado no sistema. Por favor, tente novamente.\n", ID);
        return c_list; 
    }

    // retira elemento do encadeamento
    if (c_list == p) // testa se é o primeiro elemento
        c_list = p->next;
    else 
        p->prev->next = p->next;
    
    if (p->next != NULL) // testa se é o último elemento
        p->next->prev = p->prev; 
    
    (*qtd_cargos)--; // atualiza a quantidade de cargos
    free(p->info);
    free(p);

    printf("O cargo de ID %d foi excluído do sistema.\n", ID);
    printf("Quantidade de cargos atualizado para %d.\n", *qtd_cargos);
    return c_list;
}

void cargo_libera(CargosList* f_list) {
    CargosList* p = f_list;
    while (p != NULL) {
        /* guarda referência p/ próx. elemento */
        CargosList* t = p->next;
        /* libera memória apontada por p */
        free(p->info); // libera memória alocada pelo ponteiro de cargo
        free(p);
        /* faz p apontar para o próximo */
        p = t;
    }
}

void cargo_atualiza_arquivo(CargosList* c_list) {
    CargosList* c; /* variável auxiliar para percorrer a lista */
    FILE *arquivo;
    arquivo = fopen("TAD_cargo/dados_cargos.txt", "w"); // Abre o arquivo para escrita

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }   
    for (c= c_list; c != NULL; c = c->next) {
        fprintf(arquivo, "%d;%s;", c->info->ID, c->info->nome_cargo); 
        fprintf(arquivo, "%s;%d\n", c->info->setor, c->info->qtd_funcionarios); 
    }
    
    fclose(arquivo); // Fecha o arquivo
    printf("Arquivo atualizado!\n");
}

void consulta_funcionarios_por_cargo(CargosList *c_list){
    CargosList *cargos;
    if (cargo_lst_vazia(c_list)) {
        printf("Nenhum cargo encontrado no Sistema!\n");
    } else{
        printf("------------QUANTIDADE DE FUNCIONARIOS POR CARGO------------\n");
        for (cargos = c_list; cargos != NULL; cargos = cargos->next) {
            printf("Cargo: %s\n", cargos->info->nome_cargo);    
            printf("Quantidade de funcionarios: %d\n\n", cargos->info->qtd_funcionarios); 
        }
    }
}