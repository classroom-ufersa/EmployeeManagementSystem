#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> //necessário para usar localtime() e struct tm
#include "funcionario.h"
#define TAM_LINHA 100

/* estrutura do tipo Funcionario */
struct data {
   int dia;
   int mes;
   int ano;
};

/* estrutura do tipo Funcionario */
struct funcionario {
    Data *data_de_contratacao;
    char name[50];
    int id;
    char cargo[50];
};

/* Struct que representa o nó da lista */
struct funcionarioslist {
    Funcionario info;
    struct funcionarioslist *next;
};

/* função de criação: retorna uma lista vazia */ 
FuncionariosList* lst_cria(void) {
    return NULL;
}

/* inserção no início: retorna a lista atualizada */
FuncionariosList* lst_insere(FuncionariosList* f_list, char *nome, int id, Data *data) {
    FuncionariosList* novo = (FuncionariosList*) malloc(sizeof(FuncionariosList));   
    strcpy(novo->info.name, nome);
    novo->info.id = id;
    novo->info.data_de_contratacao = data;

    /* Adiciona o novo nó da lista */
    novo->next = f_list;
    return novo;
}

/* Função que resgata os funcionários arquivados +++++ */
FuncionariosList*  obter_funcionarios(FuncionariosList *f_list){
    FILE *arquivo_origem;
    FuncionariosList *new_list = f_list;
    char linha[TAM_LINHA], nome[50];
    int id, dia, mes , ano ;

    // lendo arquivo com as informacoes dos funcionarios
    arquivo_origem = fopen("TAD_funcionario/dados_funcionarios.txt", "r"); // abre o arquivo_origem para leitura
    if (arquivo_origem == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    while (fgets(linha, TAM_LINHA, arquivo_origem) != NULL) { 
        sscanf(linha, " %[^;];%d;%d/%d/%d", nome, &id, &dia, &mes, &ano); // resgata as informações do arquivo
        Data *data_contratacao = get_data(); 
        data_contratacao->dia = dia;
        data_contratacao->mes = mes;
        data_contratacao->ano = ano;

        //printf("DATA: %d/%d/%d\n", data_contratacao.tm_mday, data_contratacao.tm_mon,  data_contratacao.tm_year );
        
        new_list = lst_insere(new_list, nome, id, data_contratacao);
    }
    fclose(arquivo_origem); // fecha o arquivo

    return new_list;
}

/* função imprime:  imprime valores dos elementos */
void lst_imprime(FuncionariosList* f_list) {
    FuncionariosList* p; /* variável auxiliar para percorrer a lista */
    for (p = f_list; p != NULL; p = p->next) {
        printf("ID: %d | Nome: %s ", p->info.id, p->info.name);    
        printf("| Data da contratacao: %d/", p->info.data_de_contratacao->dia); // imprime dia
        printf("%d/", p->info.data_de_contratacao->mes); // imprime mês
        printf("%d\n", p->info.data_de_contratacao->ano); // imprime ano
    }
}

/* função vazia: retorna 1 se vazia ou 0 se não vazia */
int lst_vazia(FuncionariosList* f_list) {
    if (f_list == NULL)
        return 1;
    else 
        return 0;
}

/* funcão busca: busca um elemento na lista */
FuncionariosList* lst_busca(FuncionariosList* f_list, int id) {
    FuncionariosList* p;
    for (p = f_list; p != NULL; p = p->next) {
        if(p->info.id == id)
            return p;
    }
    return NULL; /* não achou o elemento buscado */     
}

/* função retira: retira elemento da lista */
FuncionariosList* lst_retira(FuncionariosList* f_list, int id) {
    FuncionariosList* ant = NULL;
    FuncionariosList* p = f_list;

    /* procura elemento na lista, guardando anterior */
    while (p != NULL && p->info.id != id) {
        ant = p;
        p = p->next;
    }

    /* verifica se achou elemento */
    if (p == NULL) {
        return f_list; /* não achou: retorna a lista original */
    }

    /* retira elemento */
    if (ant == NULL) {
        /* retira elemento do início */
        f_list = p->next;
    } else {
        /* retira elemento do meio */
        ant->next = p->next;
    }

    free(p);
    atualiza_arquivo(f_list);
    return f_list;
}

/* função libera: libera elementos alocados */
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
        fprintf(arquivo, "%s;%d;", p->info.name, p->info.id);    
        fprintf(arquivo, "%d/", p->info.data_de_contratacao->dia); // imprime dia
        fprintf(arquivo, "%d/", p->info.data_de_contratacao->mes); // imprime mês
        fprintf(arquivo, "%d\n", p->info.data_de_contratacao->ano); // imprime ano
    }
    
    fclose(arquivo); // Fecha o arquivo
    printf("Arquivo atualizado!\n");
}

