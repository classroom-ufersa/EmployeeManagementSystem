#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> //necessário para usar localtime() e struct tm
#include "funcionario.h"
#define TAM_LINHA 200
#define TAM_NOME 50

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
    char setor[30];
    float salario;
    int jornada_trabalho;
};

struct funcionarioslist {
    Funcionario info;
    struct funcionarioslist *next;
    struct funcionarioslist *prev;
};

FuncionariosList* lst_cria(void) {
    return NULL;
}

// --------
FuncionariosList* lst_insere(FuncionariosList* f_list, char *nome, int id, Data *data, char *documento, 
char *cargo, char *setor, float salario, int jornada_trabalho) {
    FuncionariosList* novo = (FuncionariosList*) malloc(sizeof(FuncionariosList));   

    // inserindo as informações passadas pelo usuário
    strcpy(novo->info.name, nome);
    novo->info.id = id;
    novo->info.data_de_contratacao = data;
    strcpy(novo->info.cpf_rg.CPF, documento);
    strcpy(novo->info.cargo, cargo);
    strcpy(novo->info.setor, setor);
    novo->info.salario = salario;
    novo->info.jornada_trabalho = jornada_trabalho;

    // adicionando de fato o nó na lista
    novo->next = f_list;
    novo->prev = NULL;
    // verifica se a lista não está vazia
    if (f_list != NULL)
        f_list->prev = novo;
    
    // atualiza_arquivo(novo);
    return novo;
}

// --------
FuncionariosList*  obter_funcionarios(FuncionariosList *f_list){
    FILE *arquivo_origem;
    FuncionariosList *new_list = f_list;
    char linha[TAM_LINHA], nome[50], documento[20], cargo[50], setor[30];
    int id, dia, mes , ano;
    float salario;
    int jornada_trabalho;

    // lendo arquivo com as informacoes dos funcionarios
    arquivo_origem = fopen("TAD_funcionario/dados_funcionarios.txt", "r"); // abre o arquivo_origem para leitura
    if (arquivo_origem == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    while (fgets(linha, TAM_LINHA, arquivo_origem) != NULL) { 
        //sscanf(linha, " %[^;];%d;%d/%d/%d;%[^\n];", nome, &id, &dia, &mes, &ano, documento);
        sscanf(linha, " %[^;];%d;%d/%d/%d;%[^;];%[^;];%[^;];%f;%d", nome, &id, &dia, &mes, &ano, 
        documento, cargo, setor, &salario, &jornada_trabalho); 
        Data *data_contratacao = get_data(); 
        data_contratacao->dia = dia;
        data_contratacao->mes = mes;
        data_contratacao->ano = ano;
                     
        new_list = lst_insere(new_list, nome, id, data_contratacao, documento, cargo, setor, salario, jornada_trabalho);
    }

    fclose(arquivo_origem); // fecha o arquivo
    return new_list;
}

// --------
void lst_imprime(FuncionariosList* f_list) {
    if (lst_vazia(f_list)) {
        printf("Nenhum funcionário encontrado no Sistema!\n");
        printf("Por favor, tente adicionar algum funcionário antes de exibi-los.\n");
    } else{
        FuncionariosList* p;
        printf("------------LISTA DE FUNCIONARIOS------------\n");
        for (p = f_list; p != NULL; p = p->next) {
            printf("Nome do Funcionario: %s\nID: %d\n", p->info.name, p->info.id);    
            printf("Data da contratacao: %d/", p->info.data_de_contratacao->dia); // imprime dia
            printf("%d/", p->info.data_de_contratacao->mes); // imprime mês
            printf("%d", p->info.data_de_contratacao->ano); // imprime ano
            printf("\nRG/CPF: %s", p->info.cpf_rg.CPF); // imprime Documento
            printf("\nCargo: %s \nSetor: %s \nSalario: %.2f \nJornada de Trabalho: %d\n\n", 
            p->info.cargo, p->info.setor, p->info.salario, p->info.jornada_trabalho);
        }
    }
}

int lst_vazia(FuncionariosList* f_list) {
    if (f_list == NULL)
        return 1;
    else 
        return 0;
}

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

void swapNodes(FuncionariosList *f_list_1, FuncionariosList *f_list_2) {
    Funcionario temp = f_list_1->info;
    f_list_1->info = f_list_2->info;
    f_list_2->info = temp;
}

void lst_ordena(FuncionariosList *f_list) {
    FuncionariosList *i;
    FuncionariosList *j;
    if (lst_vazia(f_list)) {
        printf("ERRO: lista vazia!\n");
        exit(1);
    } else {
        // ordena os nomes usando bubble sort
        for (i = f_list; i != NULL; i = i->next) {
            for (j = i->next; j != NULL; j = j->next) {
                if (strcmp(i->info.name, j->info.name) > 0) {
                    swapNodes(i, j);
                }
            }
        }
    }
}

FuncionariosList *lst_edita(FuncionariosList *f_list, int id) {
    FuncionariosList* p = lst_busca(f_list, id);

    // verifica se achou o elemento
    if (p == NULL) {
        printf("Funcionário com ID %d não encontrado no sistema. Por favor, tente novamente.\n", id);
        return f_list; 
    } else {
        char resposta;
            printf("Deseja editar o nome (s/n)? ");
            scanf(" %c", &resposta);
            if (resposta == 's') {
                printf("Digite o novo nome: ");
                scanf(" %[^\n]", p->info.name);
            }
            printf("Deseja editar o CPF (s/n)? ");
            scanf(" %c", &resposta);
            if (resposta == 's') {
                printf("Digite o novo CPF: ");
                scanf(" %[^\n]", p->info.cpf_rg.CPF);
            }
            printf("Deseja editar o cargo (s/n)? ");
            scanf(" %c", &resposta);
            if (resposta == 's') {
                printf("Digite o novo cargo: ");
                scanf(" %[^\n]", p->info.cargo);
            }
            printf("Deseja editar o setor (s/n)? ");
            scanf(" %c", &resposta);
            if (resposta == 's') {
                printf("Digite o novo setor: ");
                scanf(" %[^\n]", p->info.setor);
            }
            printf("Deseja editar o salário (s/n)? ");
            scanf(" %c", &resposta);
            if (resposta == 's') {
                printf("Digite o novo salário: ");
                scanf("%f", &p->info.salario);
            }
            printf("Deseja editar a jornada de trabalho (s/n)? ");
            scanf(" %c", &resposta);
            if (resposta == 's') {
                printf("Digite a nova jornada de trabalho: ");
                scanf("%d", &p->info.jornada_trabalho);
            }
            printf("Funcionário atualizado com sucesso!\n");
    }

    return f_list;
}

int lst_quantidade(FuncionariosList *f_list) {
    int quantidade = 0;
    FuncionariosList* p;
    
    for (p = f_list; p != NULL; p = p->next)
        quantidade++;   

    return quantidade;
}