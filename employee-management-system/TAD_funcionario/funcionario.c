#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> //necessário para usar localtime() e struct tm
#include "funcionario.h"
#define TAM_LINHA 100

union documento {
  char CPF[20];
  char RG[20];
};

struct data {
   int dia;
   int mes;
   int ano;
};

struct funcionario {
    Documento cpf_rg;
    Data *data_de_contratacao;
    char name[50];
    int id;
    char cargo[50]; // OBS: susbtituir pelo tipo estruturado Cargo
};

struct funcionarioslist {
    Funcionario info;
    struct funcionarioslist *next;
    struct funcionarioslist *prev;
};

FuncionariosList* lst_cria(void) {
    return NULL;
}

// Inserção no início: retorna a lista atualizada
FuncionariosList* lst_insere(FuncionariosList* f_list, char *nome, int id, Data *data, char *documento) {
    FuncionariosList* novo = (FuncionariosList*) malloc(sizeof(FuncionariosList));   
    
    // inserindo as informações passadas pelo usuário
    strcpy(novo->info.name, nome);
    novo->info.id = id;
    novo->info.data_de_contratacao = data;
    strcpy(novo->info.cpf_rg.CPF, documento);

    // adicionando de fato o nó na lista
    novo->next = f_list;
    novo->prev = NULL;
    // verifica se a lista não está vazia
    if (f_list != NULL)
        f_list->prev = novo;
    
    // atualiza_arquivo(novo);
    return novo;
}

// Função que resgata os funcionários arquivados e salva na lista
FuncionariosList*  obter_funcionarios(FuncionariosList *f_list){
    FILE *arquivo_origem;
    FuncionariosList *new_list = f_list;
    char linha[TAM_LINHA], nome[50], documento[20];
    int id, dia, mes , ano ;

    // lendo arquivo com as informacoes dos funcionarios
    arquivo_origem = fopen("TAD_funcionario/dados_funcionarios.txt", "r"); // abre o arquivo_origem para leitura
    if (arquivo_origem == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    while (fgets(linha, TAM_LINHA, arquivo_origem) != NULL) { 
        sscanf(linha, " %[^;];%d;%d/%d/%d;%[^\n]", nome, &id, &dia, &mes, &ano, documento); // resgata as informações do arquivo
        Data *data_contratacao = get_data(); 
        data_contratacao->dia = dia;
        data_contratacao->mes = mes;
        data_contratacao->ano = ano;
                     
        new_list = lst_insere(new_list, nome, id, data_contratacao, documento);
    }

    fclose(arquivo_origem); // fecha o arquivo
    return new_list;
}

// Função imprime:  imprime valores dos elementos
void lst_imprime(FuncionariosList* f_list) {
    if (lst_vazia(f_list)) {
        printf("Nenhum funcionário encontrado no Sistema!\n");
        printf("Por favor, tente adicionar algum funcionário antes de exibi-los.\n");
    } else{
        FuncionariosList* p;
        for (p = f_list; p != NULL; p = p->next) {
            printf("ID: %d | Nome: %s ", p->info.id, p->info.name);    
            printf("| Data da contratacao: %d/", p->info.data_de_contratacao->dia); // imprime dia
            printf("%d/", p->info.data_de_contratacao->mes); // imprime mês
            printf("%d", p->info.data_de_contratacao->ano); // imprime ano
            printf(" | RG/CPF: %s\n", p->info.cpf_rg.CPF); // imprime Documento
        }
    }
}

// Função vazia: retorna 1 se vazia ou 0 se não vazia
int lst_vazia(FuncionariosList* f_list) {
    if (f_list == NULL)
        return 1;
    else 
        return 0;
}

// Funcão busca: busca um elemento na lista 
FuncionariosList* lst_busca(FuncionariosList* f_list, int id) {
    FuncionariosList* p;
    if (lst_vazia(f_list)) {
        printf("ERRO: lista vazia!\n");
        return NULL;
    } else {
        for (p = f_list; p != NULL; p = p->next) {
            if(p->info.id == id) {
                return p;
            }
        }
    }
    return NULL; // não achou o elemento buscado     
}

// Função retira: retira elemento da lista
FuncionariosList* lst_retira(FuncionariosList* f_list, int id) {
    FuncionariosList* p = lst_busca(f_list, id);

    // verifica se achou elemento
    if (p == NULL) {
        printf("Funcionário com ID %d não encontrado no sistema. Por favor, tente novamente.\n", id);
        return f_list; 
    }

    // retira elemento do encadeamento
    if (f_list == p) // testa se é o primeiro elemento
        f_list = p->next;
    else 
        p->prev->next = p->next;
    
    if (p->next != NULL) // testa se é o último elemento
        p->next->prev = p->prev; 
    
    free(p);
    // atualiza_arquivo(f_list);
    return f_list;
}

void lst_libera(FuncionariosList* f_list) {
    FuncionariosList* p = f_list;
    while (p != NULL) {
        /* guarda referência p/ próx. elemento */
        FuncionariosList* t = p->next;
        /* libera memória apontada por p */
        free(p->info.data_de_contratacao); // libera memória alocada para data
        free(p);
        /* faz p apontar para o próximo */
        p = t;
    }
}

Data *get_data(void) { 
    Data* data = (Data*) malloc(sizeof(Data)); 
    //ponteiro para struct que armazena data e hora  
    struct tm *data_hora_atual;     
    
    //variável do tipo time_t para armazenar o tempo em segundos  
    time_t segundos;
    
    //obtendo o tempo em segundos (funcao vinda da time.h) 
    time(&segundos);   
    
    //para converter de segundos para o tempo local  
    //utilizamos a função localtime  
    data_hora_atual = localtime(&segundos);
    
    data->dia = data_hora_atual->tm_mday;
    data->mes = data_hora_atual->tm_mon+1;
    data->ano = data_hora_atual->tm_year+1900;

    return data;
}

void atualiza_arquivo(FuncionariosList* f_list) {
    FuncionariosList* p; /* variável auxiliar para percorrer a lista */
    FILE *arquivo;
    arquivo = fopen("TAD_funcionario/dados_funcionarios.txt", "w"); // Abre o arquivo para escrita

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }   
    for (p = f_list; p != NULL; p = p->next) {
        fprintf(arquivo, "%s;%d;", p->info.name, p->info.id); // imprime o nome e o id do funcionario no banco de dados
        fprintf(arquivo, "%d/", p->info.data_de_contratacao->dia); // imprime a Data no banco de dados
        fprintf(arquivo, "%d/", p->info.data_de_contratacao->mes);
        fprintf(arquivo, "%d;", p->info.data_de_contratacao->ano);
        fprintf(arquivo, "%s\n", p->info.cpf_rg.CPF); // imprime Documento no banco de dados
    }
    
    fclose(arquivo); // Fecha o arquivo
    printf("Arquivo atualizado!\n");
}

